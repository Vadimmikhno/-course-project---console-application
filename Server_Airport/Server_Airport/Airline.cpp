#include "Airline.h"

void Airline::setCode(vector<Airline>& vecAirline)
{
	int controller;
	char* code = new char[20];
	do {
		controller = 0;
		Validator::generCode(code, 4);
		for (auto& element : vecAirline) {
			if (strcmp(code, element.code) == 0) {
				controller = -1;
				break;
			}
		}
	} while (controller == -1);
	Validator::copyStr(this->code, code);
	delete[] code;
}

void Airline::setType(Connection& connection)
{
	char type[3][30]{ "Международные", "Внутренние", "Международные_и_внутренние" };
	for (int i = 0; i < 3; i++)
		connection.sendStr(type[i]);
	int choise = Validator::checkInterval(1, 3, connection);
	Validator::copyStr(this->type, type[choise - 1]);
}

istream& operator>>(istream& stream, Airline& obj)
{
	char code[100], name[100], type[30];
	int amount;
	if (stream >> code >> name >> type >> amount)
		obj.set(code, name, type, amount);
	return stream;
}

ostream& operator<<(ostream& stream, const Airline& obj)
{
	stream << obj.code << " " << obj.name << " " << obj.type << " " << obj.amount;
	return stream;
}
