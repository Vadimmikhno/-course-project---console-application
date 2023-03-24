#include "WorkWithTables.h"

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "rus");

	Connection connection;
	connection.conect();

	if (connection.recvInt() == 0) {
		system("cls");
		UserCases::add(connection);
	}

	int choise;

	do {

		system("cls");
		cout << "Программное обеспечение для выбора авиакомпании" << endl;
		cout << "методом полного попарного сапоставления" << endl;
		cout << "1 - Войти под существующим аккаунтом" << endl;
		cout << "2 - Выйти из программы" << endl;
		cout << "Ваш выбор: ";
		choise = Validator::checkInterval_int(connection);

		if (choise == 1) {

			switch (UserCases::singIn(connection)) {
			case 1:

				do {
					system("cls");
					cout << "Status: ADMIN" << endl;
					cout << "UserName: " << connection.recvStr() << endl;
					cout << "ФИО: " << connection.recvStr() << endl;
					cout << "1 - Работать с авиакомпаниями" << endl;
					cout << "2 - Работать с пользователями" << endl;
					cout << "3 - Выход" << endl;
					cout << "Ваш выбор: ";
					choise = Validator::checkInterval_int(connection);

					switch (choise) {
						case 1:
							WorkWithTables::workWithAirlineForAdmin(connection);
							break;
						case 2:
							WorkWithTables::workWithUser(connection);
							break;
						default: break;
					}

				} while (choise != 3);

				break;
			case 2:

				WorkWithTables::workWithAirlineForExpert(connection);

				break;
			default: break;
			}

		}


	} while (choise != 2);
	
	return 0;
}
