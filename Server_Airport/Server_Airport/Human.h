#pragma once
#include "FullName.h"
#include "Date.h"

class Human {

protected:

	FullName fio;
	Date birthday;
	char* passport;

public:

	Human() : passport(0) {}
	Human(const Human& obj) : passport(0) {
		set(obj.fio, obj.birthday, obj.passport);
	}
	~Human() { delete[] passport; }

	void set(const FullName& fio, const Date& birthday, const char* serNumPass) {
		this->fio = fio;
		this->birthday = birthday;
		Validator::copyStr(this->passport, serNumPass);
	}

	void setFio(Connection& connection) { fio.set(connection); }
	void setBirthday(Connection& connection);
	void setPassport(Connection& connection) { Validator::setPassport(passport, connection); }

	FullName& getFio() { return fio; }
	Date& getBirthday() { return birthday; }
	char* getPassport() { return passport; }

	void operator=(const Human& obj) {
		set(obj.fio, obj.birthday, obj.passport);
	}

};