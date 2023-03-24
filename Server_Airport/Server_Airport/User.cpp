#include "User.h"

istream& operator>>(istream& stream, User& obj)
{
	char status[20], login[100], password[100], passport[10];
	FullName fio;
	Date birthday;
	int block;
	if (stream >> status >> login >> password
		>> block >> fio >> birthday >> passport) {
		obj.Human::set(fio, birthday, passport);
		obj.User::set(status, login, password, block);
	}
	return stream;
}

ostream& operator<<(ostream& stream, User& obj)
{
	stream << obj.status << " " << obj.login << " " << obj.password << " "
		<< obj.lockStatus << " " << obj.fio << " " << obj.birthday << " " << obj.passport;
	return stream;
}

void User::setLogin(vector<User>& vecUser, Connection& connection)
{
	int controller;
	char* BufForWriting = new char(0);
	char symbols[] = "QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm._-1234567890";
	do {
		controller = 0;
		connection.recvStr(BufForWriting);
		if (strlen(BufForWriting) < 6) { //cout << "Логин должен содержать 6 или более символов: ";
			controller = 1;
		}
		else {
			for (int i = 0; BufForWriting[i] != '\0'; i++) {
				controller = 2;
				for (register int j = 0; symbols[j] != '\0'; j++) {
					if (BufForWriting[i] == symbols[j]) { 
						controller = 0;
						break; 
					}
				}
			    if (controller == 2) { //cout << "Логин может содержать латинские буквы, цифры и специальные символы(-._): ";
					break;
				}
			}
			if (controller == 0) {
				for (auto& element : vecUser) {
					if (strcmp(element.login, BufForWriting) == 0) { //cout << "Данный логин занят другим пользователем: ";
						controller = 3;
						break;
					}
				}
			}
		}
		connection.sendInt(controller);
	} while (controller != 0);
	Validator::copyStr(this->login, BufForWriting);
	delete[] BufForWriting;
}

void User::setPassword(Connection& connection)
{
	char* password1 = new char(0);
	char* password2 = new char(0);
	int controller, num, alpha;
	do {
		controller = 0; alpha = 0; num = 0;
		connection.recvStr(password1);
		if (strlen(password1) < 8) { //cout << "Пароль должен содержать 8 или более символов: ";
			controller = 1;
		}
		else {
			for (register int i = 0; password1[i] != '\0'; i++) {
				if (isspace(password1[i])) { //cout << "Пароль не должен содержать пробелы: ";
					controller = 2;
					break;
				}
				else if (isdigit(password1[i]))
					num++;
				else if (isalpha(password1[i]))
					alpha++;
			}
			if (controller != -1 && (num == 0 || alpha == 0)) { //cout << "Пароль должен содержать буквы и цифры: ";
				controller = 3;
			}
		}
		connection.sendInt(controller);
		if (controller == 0) {
			if (strcmp(password1, connection.recvStr(password2)) != 0) {
				controller = 4;
			}
			connection.sendInt(controller);
		}
	} while (controller != 0);
	Validator::copyStr(this->password, password1);
	delete[] password1;
}

//bool User::operator<(User& obj)
//{
//	int len;
//	if (strlen(this->fio.getSurname()) < strlen(obj.fio.getSurname()))
//		len = strlen(this->fio.getSurname());
//	else len = strlen(obj.fio.getSurname());
//	for (int i = 0; i < len; i++) {
//		if (this->fio.getSurname()[i] < obj.[i])
//			return true;
//		if (this->name[i] > obj.name[i])
//			return false;
//	}
//	if (strlen(this->name) < strlen(obj.name))
//		return true;
//	if (strlen(this->name) > strlen(obj.name))
//		return false;
//	return false;
//}

//bool User::compSurname(User& A, User& B)
//{
//	int len;
//	if (strlen(A.fio.getSurname()) < strlen(B.fio.getSurname()))
//		len = strlen(A.fio.getSurname());
//	else len = strlen(B.fio.getSurname());
//	for (int i = 0; i < len; i++) {
//		if (A.fio.getSurname()[i] < B.fio.getSurname()[i])
//			return true;
//		if (A.fio.getSurname()[i] > B.fio.getSurname()[i])
//			return false;
//	}
//	if (strlen(A.fio.getSurname()) < strlen(B.fio.getSurname()))
//		return true;
//	if (strlen(A.fio.getSurname()) > strlen(B.fio.getSurname()))
//		return false;
//	return false;
//}
