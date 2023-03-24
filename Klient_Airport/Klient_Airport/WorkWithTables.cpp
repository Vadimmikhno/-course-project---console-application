# include "WorkWithTables.h"

void WorkWithTables::workWithAirlineForAdmin(Connection& connection)
{

	int choise;

	do {

		system("cls");
		AirlineCases::output(connection);
		cout << "1 - Добавить авиакомпанию" << endl;
		cout << "2 - Редактировать авиакомпанию" << endl;
		cout << "3 - Удалить авиакомпанию" << endl;
		cout << "4 - Процедуры поиска и фильтрации" << endl;
		cout << "5 - Определить наилучшую альтенативу по мнению экспертов" << endl;
		cout << "Ваш выбор (0 - вернуться назад): ";

		choise = Validator::checkInterval_int(connection);

		switch (choise) {
		case 1:
			if (connection.recvInt() > 0) {
				cout << "При добавлении альтернативы будут удалены частоты экспертов." << endl;
				cout << "Подтвердить действие? (1 - Да / 2 - Нет): ";
				if (Validator::checkInterval_int(connection) == 1)
					AirlineCases::add(connection);
			}
			else AirlineCases::add(connection);
			break;
		case 2:
			AirlineCases::edit(connection);
			break;
		case 3:
			if (connection.recvInt() > 0) {
				cout << "При удалении альтернативы будут удалены частоты экспертов." << endl;
				cout << "Подтвердить действие? (1 - Да / 2 - Нет): ";
				if (Validator::checkInterval_int(connection) == 1)
					AirlineCases::del(connection);
			}
			else AirlineCases::del(connection);
			break;
		case 4:
			AirlineCases::searchFiltr(connection);
			break;
		case 5:
			if (connection.recvInt() > 0) {
				OpinionCases::result(connection);
				system("pause");
			}
			else {
				cout << "Ни один эксперт еще не проставил частоты!" << endl;
				Sleep(2000);
			}
			break;
		default: break;
		}

	} while (choise != 0);

}

void WorkWithTables::workWithAirlineForExpert(Connection& connection)
{
	int choise;
	do {
		system("cls");
		cout << "Status: EXPERT" << endl;
		cout << "UserName: " << connection.recvStr() << endl;
		cout << "ФИО: " << connection.recvStr() << endl;
		AirlineCases::output(connection);
		cout << "1 - Процедуры поиска и фильтрации" << endl;
		cout << "2 - Заполнить матрицу частот" << endl;
		cout << "3 - Просмотреть матрицу частот" << endl;
		cout << "4 - Определить наилучшую альтернативу по мнению экспертов" << endl;
		cout << "5 - Выход" << endl;
		cout << "Ваш выбор: ";
		choise = Validator::checkInterval_int(connection);

		switch (choise) {
		case 1:
			AirlineCases::searchFiltr(connection);
			break;
		case 2:
			if (connection.recvInt() > 1) {
				OpinionCases::setMarks(connection);
			}
			else {
				cout << "Дождитесь когда администратор добавить хотябы 2 альтернативы!" << endl;
				Sleep(2000);
			}
			break;
		case 3:
			if (connection.recvInt() > 1) {
				OpinionCases::getMarks(connection);
				system("pause");
			}
			else {
				cout << "Дождитесь когда администратор добавить хотябы 2 альтернативы!" << endl;
				Sleep(2000);
			}
			break;
		case 4:
			if (connection.recvInt() > 0) {
				OpinionCases::result(connection);
				system("pause");
			}
			else {
				cout << "Ни один эксперт еще не проставил частоты!" << endl;
				Sleep(2000);
			}
			break;
		default: break;
		}

	} while (choise != 5);
}

void WorkWithTables::workWithUser(Connection& connection)
{
	int choise;

	do {
		system("cls");
		UserCases::output(connection);
		cout << "1 - Добавить эксперта" << endl;
		cout << "2 - Редактировать пользователя" << endl;
		cout << "3 - Удалить пользователя" << endl;
		cout << "4 - Процедуры поиска и фильтрации" << endl;
		cout << "Ваш выбор(0 - вернуться назад): ";
		choise = Validator::checkInterval_int(connection);
		switch (choise) {
		case 1:
			UserCases::add(connection);
			break;
		case 2:
			UserCases::edit(connection);
			break;
		case 3:
			UserCases::del(connection);
			break;
		case 4:
			UserCases::searchFiltr(connection);
			break;
		default: break;
		}

	} while (choise != 0);
}
