#include "WorkWithTables.h"

void WorkWithTables::workWithAirlineForAdmin(AirlineCases& airline_cases, OpinionCases& opinion_cases, Connection& connection)
{
	int choise;
	do {

		AirlineCases::output(airline_cases.getVec(), connection);
		choise = Validator::checkInterval(0, 5, connection);

		switch (choise) {
		case 1:
			connection.sendInt(opinion_cases.getVec().size());
			if (opinion_cases.getVec().size() > 0) {
				if (Validator::checkInterval(1, 2, connection) == 1) {
					airline_cases.add(connection);
					opinion_cases.delAll();
				}
			}
			else airline_cases.add(connection);
			break;
		case 2:
			airline_cases.edit(connection);
			break;
		case 3:
			connection.sendInt(opinion_cases.getVec().size());
			if (opinion_cases.getVec().size() > 0) {
				if (Validator::checkInterval(1, 2, connection) == 1) {
					airline_cases.del(connection);
					opinion_cases.delAll();
				}
			}
			else airline_cases.del(connection);
			break;
		case 4:
			airline_cases.searchFiltr(connection);
			break;
		case 5:
			connection.sendInt(opinion_cases.getVec().size() > 0);
			if (opinion_cases.getVec().size() > 0) {
				opinion_cases.result(connection, airline_cases.getVec().size());
			}
			break;
		default:break;
		}

		if (choise >= 1 && choise <= 3)
			airline_cases.write();

	} while (choise != 0);
}

void WorkWithTables::workWithAirlineForExpert(UserCases& user_cases, AirlineCases& airline_cases, OpinionCases& opinion_cases, Connection& connection)
{
	int choise;
	do {

		connection.sendStr(user_cases.getActive().getLogin());
		connection.sendStr(user_cases.getActive().getFio().toString());
		AirlineCases::output(airline_cases.getVec(), connection);
		choise = Validator::checkInterval(0, 5, connection);

		switch (choise) {
		case 1:
			airline_cases.searchFiltr(connection);
			break;
		case 2:
			connection.sendInt(airline_cases.getVec().size());
			if (airline_cases.getVec().size() > 1) {
				opinion_cases.getOpinion(user_cases.getActive().getLogin(), airline_cases.getVec().size()).setDefaultMarks(airline_cases.getVec().size());
				opinion_cases.getOpinion(user_cases.getActive().getLogin(), airline_cases.getVec().size()).setMarks(airline_cases, connection);
				opinion_cases.write();
			}
			break;
		case 3:
			connection.sendInt(airline_cases.getVec().size());
			if (airline_cases.getVec().size() > 1) {
				opinion_cases.getOpinion(user_cases.getActive().getLogin(), airline_cases.getVec().size()).getMarks(connection);
			}
			break;
		case 4:
			connection.sendInt(opinion_cases.getVec().size());
			if (opinion_cases.getVec().size() > 0) {
				opinion_cases.result(connection, airline_cases.getVec().size());
			}
			break;
		default: break;
		}

	} while (choise != 5);
}

void WorkWithTables::workWithUser(UserCases& user_cases, Connection& connection)
{
	int choise;
	do {

		UserCases::output(user_cases.getVector(), connection);
		choise = Validator::checkInterval(0, 4, connection);

		switch (choise) {
		case 1:
			user_cases.add("EXPERT", connection);
			break;
		case 2:
			user_cases.edit(connection);
			break;
		case 3:
			user_cases.del(connection);
			break;
		case 4:
			user_cases.searchFiltr(connection);
			break;
		default: break;
		}

		if (choise >= 1 && choise <= 3) {
			user_cases.encryp();
			user_cases.write();
			user_cases.decryp();
		}

	} while (choise != 0);
}
