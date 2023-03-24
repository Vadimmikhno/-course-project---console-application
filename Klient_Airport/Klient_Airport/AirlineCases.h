#pragma once
#include "Validator.h"
#include "Connection.h"

class AirlineCases {

public:

	static void setType(Connection& connection);

	static void add(Connection& connection);
	static void edit(Connection& connection);
	static void del(Connection& connection);
	static void searchFiltr(Connection& connection);

	static void output(Connection& connection);

};