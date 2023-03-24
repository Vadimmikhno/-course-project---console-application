#include "AirlineCases.h" 

void AirlineCases::read()
{
	ifstream fin("Airline.txt");
	Airline obj;
	while (fin >> obj)
		vecAirline.push_back(obj);
	fin.close();
}

void AirlineCases::write()
{
	ofstream fout("Airline.txt", ios_base::trunc);
	for (auto& element : vecAirline) {
		fout << element << endl;
	}
	fout.close();
}

void AirlineCases::add(Connection& connection)
{
	Airline obj;
	obj.setCode(this->vecAirline);
	connection.sendStr(obj.getCode());
	obj.setName(connection);
	obj.setType(connection);
	obj.setAmount(connection);
	if (Validator::checkInterval(1, 2, connection) == 1)
		this->vecAirline.push_back(obj);
}

void AirlineCases::edit(Connection& connection)
{
	int choise = Validator::checkInterval(0, this->vecAirline.size(), connection);
	if (choise != 0) {

		switch (Validator::checkInterval(0, 3, connection)) {
		case 1:
			vecAirline[choise - 1].setName(connection);
			break;
		case 2:
			vecAirline[choise - 1].setType(connection);
			break;
		case 3:
			vecAirline[choise - 1].setAmount(connection);
			break;
		default: break;
		}

	}
}

void AirlineCases::del(Connection& connection)
{
	int choise = Validator::checkInterval(0, vecAirline.size(), connection);
	if (choise != 0) {
		if (Validator::checkInterval(1, 2, connection) == 1)
			vecAirline.erase(vecAirline.cbegin() + choise - 1);
	}

}

void AirlineCases::searchFiltr(Connection& connection)
{
	connection.sendInt(vecAirline.size());
	if (vecAirline.size() > 0) {

		int choise = Validator::checkInterval(0, 5, connection);

		if (choise != 0) {

			vector<Airline> result;

			if (choise == 4 || choise == 5) {

				result = vecAirline;

				switch (choise) {
				case 4:
					sort(result.begin(), result.end(), [](Airline& A, Airline& B) 
						{ return Validator::comparator(A.getType(), B.getType()); });
					break;
				case 5:
					sort(result.begin(), result.end(), [](Airline& A, Airline& B)
						{ return A.getAmount() < B.getAmount(); });
					break;
				default: break;
				}

			}
			else {

				char* str = new char[0];
				int min = 0, max = 0;

				switch (choise) {

				case 1:
					Validator::setStr(str, connection);
					break;
				case 2:
					Validator::setStr(str, connection);
					break;
				case 3:
					min = Validator::checkInterval(0, 99999, connection);
					max = Validator::checkInterval(min, 99999, connection);
					break;
				default: break;

				}

				int controller = 1;

				for (auto& element : vecAirline) {

					switch (choise) {
					case 1:
						controller = strcmp(element.getCode(), str);
						break;
					case 2:
						controller = strcmp(element.getName(), str);
						break;
					case 3:
						if (element.getAmount() >= min && element.getAmount() <= max)
							controller = 0;
						else controller = 1;
						break;
					default: break;
					}

					if (controller == 0)
						result.push_back(element);

				}

				delete[] str;

			}

			AirlineCases::output(result, connection);
			result.clear();

		}

	}
}

void AirlineCases::output(vector<Airline>& vecAirline, Connection& connection)
{
	connection.sendInt(vecAirline.size());
	if (vecAirline.size() > 0) {
		for (auto& element : vecAirline) {
			connection.sendStr(element.getCode());
			connection.sendStr(element.getName());
			connection.sendStr(element.getType());
			connection.sendInt(element.getAmount());
		}
	}
}
