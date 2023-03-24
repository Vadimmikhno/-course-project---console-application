#pragma once
#include "AirlineCases.h"
#include "UserCases.h"
#include "OpinionCases.h"

class WorkWithTables {

public:

	static void workWithAirlineForAdmin(AirlineCases& airline_cases, OpinionCases& opinion_cases, Connection& connection);
	static void workWithAirlineForExpert(UserCases& user_cases, AirlineCases& airline_cases, OpinionCases& opinion_cases, Connection& connection);
	static void workWithUser(UserCases& user_cases, Connection& connection);

};