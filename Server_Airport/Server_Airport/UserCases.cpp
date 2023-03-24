#include "UserCases.h"

int UserCases::signIn(Connection& connection)
{
	int controller = 0;
	char* login = new char[0];
	char* password = new char[0];

	do {

		connection.recvStr(login);
		connection.recvStr(password);

		for (auto& element : vecUser) {

			if (strcmp(login, element.getLogin()) == 0
				&& strcmp(password, element.getPassword()) == 0) {

				if (element.getLockStatus() != 0) {
					controller = 3;
					break;
				}
				else if (strcmp(element.getStatus(), "ADMIN") == 0) {
					controller = 1;
					this->active = element;
					break;
				}
				else {
					controller = 2;
					this->active = element;
					break;
				}

			}

		}

		connection.sendInt(controller);

		if (controller == 0) {
			if (Validator::checkInterval(1, 2, connection) == 2)
				controller = 4;
		}

	} while (controller == 0);

	delete[] login;
	delete[] password;

	return controller;

}

void UserCases::encryp()
{
	for (auto& element : vecUser) {
		element.encrypPassword();
	}
}

void UserCases::decryp()
{
	for (auto& element : vecUser) {
		element.decrypPassword();
	}
}

void UserCases::read(Connection& connection)
{
	ifstream fin("User.txt");
	User obj;
	while (fin >> obj) {
		obj.decrypPassword();
		vecUser.push_back(obj);
	}
	fin.close();
	connection.sendInt(vecUser.size());
	if (vecUser.size() == 0)
		UserCases::add("ADMIN", connection);
}

void UserCases::write()
{
	ofstream fout("User.txt", ios_base::trunc);
	for (auto& element : vecUser)
		fout << element << endl;
	fout.close();
}

void UserCases::add(const char* status, Connection& connection)
{
	User user;
	user.setStatus(status);
	connection.sendStr(status);
	user.setFio(connection);
	user.setBirthday(connection);
	user.setPassport(connection);
	user.setLogin(vecUser, connection);
	user.setPassword(connection);
	if (strcmp(status, "ADMIN") != 0) {
		if (Validator::checkInterval(1, 2, connection) == 1)
			vecUser.push_back(user);
	}
	else vecUser.push_back(user);
}

void UserCases::edit(Connection& connection)
{
	connection.sendInt(vecUser.size());
	if (vecUser.size() > 0) {
		int choise = Validator::checkInterval(0, vecUser.size(), connection);
		if (choise != 0) {
			int controller;
			switch (Validator::checkInterval(0, 6, connection)) {
			case 1:
				vecUser[choise - 1].setLogin(vecUser, connection);
				break;
			case 2:
				vecUser[choise - 1].setPassword(connection);
				break;
			case 3:
				controller = strcmp(vecUser[choise - 1].getStatus(), "ADMIN");
				connection.sendInt(controller);
				if (controller != 0)
					vecUser[choise - 1].setLockStatus();
				break;
			case 4:
				vecUser[choise - 1].setFio(connection);
				break;
			case 5:
				vecUser[choise - 1].setBirthday(connection);
				break;
			case 6:
				vecUser[choise - 1].setPassport(connection);
				break;
			default: break;
			}
		}
	}
}

void UserCases::del(Connection& connection)
{
	connection.sendInt(vecUser.size());
	if (vecUser.size() > 0) {
		int choise = Validator::checkInterval(0, vecUser.size(), connection);
		if (choise != 0) {
			int controller = strcmp(vecUser[choise - 1].getStatus(), "ADMIN");
			connection.sendInt(controller);
			if (controller != 0) {
				if (Validator::checkInterval(1, 2, connection) == 1)
					vecUser.erase(vecUser.cbegin() + choise - 1);
			}
		}
	}
}

void UserCases::searchFiltr(Connection& connection)
{
	connection.sendInt(vecUser.size());
	if (vecUser.size() > 0) {
		int choise = Validator::checkInterval(0, 5, connection);
		if (choise != 0) {
			char* str = new char(0);
			vector<User> result;
			if (choise == 4) {
				result = vecUser;
				sort(result.begin(), result.end(), [](User& A, User& B)
					{ return Validator::comparator(A.getFio().getSurname(), B.getFio().getSurname()); });
			}
			else if (choise == 5) {
				result = vecUser;
				sort(result.begin(), result.end(), [](User& A, User& B)
					{ return A.getBirthday() < B.getBirthday(); });
			}
			else {
				Validator::setStr(str, connection);
				int controller = -1;
				for (auto& element : vecUser) {
					switch (choise) {
					case 1:
						controller = strcmp(str, element.getFio().getSurname());
						break;
					case 2:
						controller = strcmp(str, element.getLogin());
						break;
					case 3:
						controller = strcmp(str, element.getPassport());
						break;
					default: break;
					}
					if (controller == 0)
						result.push_back(element);
				}
			}
			UserCases::output(result, connection);
			result.clear();
			delete[] str;
		}
	}
}

void UserCases::output(vector<User>& vecUser, Connection& connection)
{
	connection.sendInt(vecUser.size());
	if (vecUser.size() > 0) {
		for (auto& element : vecUser) {
			connection.sendStr(element.getStatus());
			connection.sendStr(element.getLogin());
			connection.sendInt(element.getLockStatus());
			connection.sendStr(element.getFio().toString());
			connection.sendStr(element.getPassport());
			connection.sendStr(element.getBirthday().toString());
		}
	}
}
