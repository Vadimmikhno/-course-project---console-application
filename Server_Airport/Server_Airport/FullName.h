#pragma once
#include "Validator.h"
#include "Connection.h"

class FullName {

protected:

	char* surname;
	char* name;
	char* patronymic;
	char* fullName;

public:

	FullName() : surname(0), name(0), patronymic(0), fullName(0) {}
	FullName(const FullName& obj) : surname(0), name(0), patronymic(0), fullName(0) {
		set(surname, name, patronymic);
	}
	~FullName() {
		delete[] surname;
		delete[] name;
		delete[] patronymic;
		delete[] fullName;
	}

	void set(const char* surname, const char* name, const char* patronymic);
	void set(Connection& connection);

	char* getSurname() { return surname; }
	char* getName() { return name; }
	char* getPatronymic() { return patronymic; }

	char* toString();
	void operator=(const FullName& obj) {
		set(obj.surname, obj.name, obj.patronymic);
	}
	friend istream& operator>>(istream& stream, FullName& obj);
	friend ostream& operator<<(ostream& stream, FullName& obj);
};
