#pragma once
#include "UserCases.h"
#include "AirlineCases.h"
#include "OpinionCases.h"

class WorkWithTables {

public:

	static void workWithAirlineForAdmin(Connection& connection);
	static void workWithAirlineForExpert(Connection& connection);
	static void workWithUser(Connection& connection);

};