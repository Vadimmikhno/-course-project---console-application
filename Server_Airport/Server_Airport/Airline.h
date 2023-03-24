#pragma once

#include "Connection.h"
#include "Validator.h"

class Airline {

protected:

	char* code;
	char* name;
	char* type;
	int amount;

public:

	Airline() : code(0), name(0), type(0), amount(0) { }
	Airline(const Airline& obj) : code(0), name(0), type(0), amount(0) {
		set(obj.code, obj.name, obj.type, obj.amount);
	}
	~Airline() { delete[] code; delete[] name; delete[] type; }

	void set(const char* code, const char* name, const char* type, const int amount) {
		Validator::copyStr(this->code, code);
		Validator::copyStr(this->name, name);
		Validator::copyStr(this->type, type);
		this->amount = amount;
	}

	void setCode(vector<Airline>& vecAirline);
	void setName(Connection& connection) { Validator::setStr(name, connection); }
	void setType(Connection& connection);
	void setAmount(Connection& connection) { this->amount = Validator::checkInterval(1, 99999, connection); }

	char* getCode() { return code; }
	char* getName() { return name; }
	char* getType() { return type; }
	int getAmount() { return amount; }

	void operator=(const Airline& obj) {
		set(obj.code, obj.name, obj.type, obj.amount);
	}

	friend istream& operator>>(istream& stream, Airline& obj);
	friend ostream& operator<<(ostream& stream, const Airline& obj);

};