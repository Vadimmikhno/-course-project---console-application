#pragma once
#include "Validator.h"
#include "Connection.h"
#include "AirlineCases.h"

class OpinionCases {

public:

	static void result(Connection& connection);
	static void getMarks(Connection& connection);
	static void setMarks(Connection& connection);

};