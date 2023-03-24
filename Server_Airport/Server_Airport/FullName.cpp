#include "FullName.h"

void FullName::set(const char* surname, const char* name, const char* patronymic)
{
	Validator::copyStr(this->surname, surname);
	Validator::copyStr(this->name, name);
	Validator::copyStr(this->patronymic, patronymic);
}

void FullName::set(Connection& connection)
{
	Validator::setStr(surname, connection);
	Validator::setStr(name, connection);
	Validator::setStr(patronymic, connection);
}

char* FullName::toString()
{
	int endOfStr = 0;
	char* full = new char[256];
	strcpy(full, this->surname);
	endOfStr = strlen(full);
	full[endOfStr] = ' ';
	full[endOfStr + 1] = this->name[0];
	full[endOfStr + 2] = '.';
	full[endOfStr + 3] = this->patronymic[0];
	full[endOfStr + 4] = '.';
	full[endOfStr + 5] = '\0';
	Validator::copyStr(this->fullName, full);
	delete[] full;
	return this->fullName;
}

istream& operator>>(istream& stream, FullName& obj)
{
	char name[100], surname[100], patronymic[100];
	if (stream >> surname >> name >> patronymic)
		obj.set(surname, name, patronymic);
	return stream;
}

ostream& operator<<(ostream& stream, FullName& obj)
{
	stream << obj.surname << " " << obj.name << " " << obj.patronymic;
	return stream;
}
