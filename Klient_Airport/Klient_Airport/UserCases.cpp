#include "UserCases.h"

int UserCases::singIn(Connection& connection)
{
	int controller;

	do {

		system("cls");

		cout << "Логин: ";
		Validator::setStr(connection);
		cout << "Пароль: ";
		Validator::encryption(connection);

		connection.recvInt(controller);

		if (controller == 0) {
			cout << "Неверный логин или пароль!" << endl;
			cout << "Попробовать еще раз? (1 - Да / 2 - Нет): ";
			if (Validator::checkInterval_int(connection) == 2)
				controller = 4;
		}
		else if (controller == 3) {
			cout << "Данная учетная запись заблокирована!" << endl;
			Sleep(2000);
		}

	} while (controller == 0);

	return controller;

}

void UserCases::add(Connection& connection)
{
	char* status = new char[0];
	system("cls");
	cout << "Регистрация <" << connection.recvStr(status) << ">" << endl;
	cout << "Заполните ФИО" << endl;
	Validator::setFio(connection);
	cout << "Дата рождения" << endl;
	Validator::checkInterval_date(connection);
	Validator::setPassport(connection);
	Validator::setLogin(connection);
	Validator::setPassword(connection);
	if (strcmp(status, "ADMIN") != 0) {
		cout << "Подтвердить регистрацию?" << endl;
		cout << "(1 - Да / 2 - Нет): ";
		Validator::checkInterval_int(connection);
	}
	delete[] status;
}

void UserCases::edit(Connection& connection)
{
	if (connection.recvInt() > 0) {
		cout << "Выберите номер пользователя, которого хотите редактировать(0 - вернуться назад): ";
		if (Validator::checkInterval_int(connection) != 0) {
			cout << "Критерии редактирования" << endl;
			cout << "1 - Логин" << endl;
			cout << "2 - Пароль" << endl;
			cout << "3 - Статус блокировки" << endl;
			cout << "4 - ФИО" << endl;
			cout << "5 - Дата рождения" << endl;
			cout << "6 - Серия№ паспорта" << endl;
			cout << "Ваш выбор(0 - вернуться назад): ";
			switch (Validator::checkInterval_int(connection)) {
			case 1:
				Validator::setLogin(connection);
				break;
			case 2:
				Validator::setPassword(connection);
				break;
			case 3:
				if (connection.recvInt() == 0) {
					cout << "Нельзя заблокировать данного пользователя!" << endl;
					Sleep(2000);
				}
				break;
			case 4:
				cout << "Заполните ФИО" << endl;
				Validator::setFio(connection);
				break;
			case 5:
				cout << "Дата рождения" << endl;
				Validator::checkInterval_date(connection);
				break;
			case 6:
				Validator::setPassport(connection);
				break;
			default: break;
			}
		}
	}
	else { cout << "Нет пользователей!" << endl; Sleep(1500); }
}

void UserCases::del(Connection& connection)
{
	if (connection.recvInt() > 0) {
		cout << "Выберите номер пользователя, которого хотите удалить(0 - вернуться назад): ";
		if (Validator::checkInterval_int(connection) != 0) {
			if (connection.recvInt() == 0) {
				cout << "Нельзя удалить данного пользователя!" << endl;
				Sleep(2000);
			}
			else {
				cout << "Подтвердить удаление?" << endl;
				cout << "(1 - Да / 2 - Нет): ";
				Validator::checkInterval_int(connection);
			}
		}
	}
	else { cout << "Нет пользователей!" << endl; Sleep(1500); }
}

void UserCases::output(Connection& connection)
{
	int size;
	connection.recvInt(size);
	if (size > 0) {
		char* str = new char[0];
		int lock_status;
		UserCases::header();
		for (int i = 0; i < size; i++) {
			cout << "|" << setw(5) << i + 1;
			cout << "|" << setw(10) << connection.recvStr(str);
			cout << "|" << setw(20) << connection.recvStr(str);
			if (connection.recvInt(lock_status) == 0)
				cout << "|" << setw(10) << "False";
			else cout << "|" << setw(10) << "True";
			cout << "|" << setw(30) << connection.recvStr(str);
			cout << "|" << setw(15) << connection.recvStr(str);
			cout << "|" << setw(15) << connection.recvStr(str);
			cout << "|" << endl;
		}
		delete[] str;
	}
	else {
		cout << "|" << setw(62) << "Нет записей" << setw(50) << "|" << endl;
	}
}

void UserCases::searchFiltr(Connection& connection)
{
	if (connection.recvInt() > 0) {
		cout << "Критерии поика и фильтрации" << endl;
		cout << "1 - Поиск по фамилии" << endl;
		cout << "2 - Поиск по логину" << endl;
		cout << "3 - Поиск по серии № паспорта" << endl;
		cout << "4 - Сортировка по фамилии(А-Я)" << endl;
		cout << "5 - Сортировка по дате рождения" << endl;
		cout << "Ваш выбор(0 - вернуться назад): ";
		int choise = Validator::checkInterval_int(connection);
		if (choise != 0) {
			if (choise >= 1 && choise <= 3) {
				cout << "Введите информацию для поиска: ";
				Validator::setStr(connection);
			}
			system("cls");
			UserCases::header();
			UserCases::output(connection);
			system("pause");
		}
	}
	else { cout << "Нет пользователей!" << endl; Sleep(1500); }
}

void UserCases::header()
{
	cout << "|" << setw(5) << "#" << "|" << setw(10) << "Статус"
		<< "|" << setw(20) << "Логин" << "|" << setw(10) << "Блокировка"
		<< "|" << setw(30) << "ФИО" << "|" << setw(15) << "Серия№ паспорта"
		<< "|" << setw(15) << "Дата рождения" << "|" << endl;
}
