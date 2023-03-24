#include "WorkWithTables.h"

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "rus");

	Connection connection;
	connection.acept();

	AirlineCases airline_cases;
	OpinionCases opinion_cases;
	UserCases user_cases;
	
	user_cases.read(connection);
	airline_cases.read();
	opinion_cases.read();

	int choise;

	do {
		choise = Validator::checkInterval(1, 2, connection);
		switch (choise) {
		case 1:
			switch (user_cases.signIn(connection)) {
			case 1:
				do {
					connection.sendStr(user_cases.getActive().getLogin());
					connection.sendStr(user_cases.getActive().getFio().toString());
					choise = Validator::checkInterval(1, 3, connection);
					switch (choise) {
					case 1:
						WorkWithTables::workWithAirlineForAdmin(airline_cases, opinion_cases, connection);
						break;
					case 2:
						WorkWithTables::workWithUser(user_cases, connection);
						break;
					default: break;
					}
				} while (choise != 3);
				break;
			case 2:
				WorkWithTables::workWithAirlineForExpert(user_cases, airline_cases, opinion_cases, connection);
				break;
			default: break;
			}
			break;
		case 2:
			user_cases.encryp();
			user_cases.write();
			opinion_cases.write();
			airline_cases.write();
			break;
		default: break;
		}
	} while (choise != 2);
	return 0;
}