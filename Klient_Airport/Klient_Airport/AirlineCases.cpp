#include "AirlineCases.h"

void AirlineCases::setType(Connection& connection)
{
	cout << "Тип перевозок" << endl;
	for (int i = 0; i < 3; i++) 
		cout << i + 1 << " - " << connection.recvStr() << endl;
	cout << "Ваш выбор: ";
	Validator::checkInterval_int(connection);
}

void AirlineCases::add(Connection& connection)
{
	system("cls");
	cout << "Процедура добавления авикомпании" << endl;
	cout << "(заполните поля ниже)" << endl;
	cout << "Код записи: " << connection.recvStr() << endl;
	cout << "Название авиакомпании: ";
	Validator::setStr(connection);
	AirlineCases::setType(connection);
	cout << "Кол-во рейсов в год: ";
	Validator::checkInterval_int(connection);
	cout << "Добавить запись?" << endl;
	cout << "(1 - Да / 2 - Нет): ";
	Validator::checkInterval_int(connection);
}

void AirlineCases::edit(Connection& connection)
{
	cout << "Выберите запись, которую хотите редактировать(0 - вернуться назад): ";
	
	if (Validator::checkInterval_int(connection) != 0) {
		
		cout << "Критерии редактирования" << endl;
		cout << "1 - Название авиакомпании" << endl;
		cout << "2 - Тип перевозок" << endl;
		cout << "3 - Кол-во рейсов в год" << endl;
		cout << "Ваш выбор(0 - вернуться назад): ";

		switch (Validator::checkInterval_int(connection)) {
		case 1:
			cout << "Название авиакомании: ";
			Validator::setStr(connection);
			break;
		case 2:
			AirlineCases::setType(connection);
			break;
		case 3:
			cout << "Кол-во рейсов в год: ";
			Validator::checkInterval_int(connection);
			break;
		default: break;
		}

	}
}

void AirlineCases::del(Connection& connection)
{
	cout << "Выберите запись, которую хотите удалить(0 - вернуться назад): ";
	if (Validator::checkInterval_int(connection) != 0) {
		cout << "Подтвердить удаление?" << endl;
		cout << "(1 - Да / 2 - Нет): ";
		Validator::checkInterval_int(connection);
	}
}

void AirlineCases::searchFiltr(Connection& connection)
{
	if (connection.recvInt() > 0) {
		
		system("cls");
		cout << "Критерии поиска и фильтрации" << endl;
		cout << "1 - Поиск по коду" << endl;
		cout << "2 - Поиск по названию авиакомпании" << endl;
		cout << "3 - Фильтрация по кол-ву рейсов в год" << endl;
		cout << "4 - Сортировка по типу перевозок" << endl;
		cout << "5 - Сортировка по кол-ву рейсов в год" << endl;
		cout << "Ваш выбор(0 - вернуться назад): ";

		int choise = Validator::checkInterval_int(connection);

		if (choise != 0) {

			switch (choise) {
			case 1:
				cout << "Введите код: ";
				Validator::setStr(connection);
				break;
			case 2:
				cout << "Введите назавание авикампании: ";
				Validator::setStr(connection);
				break;
			case 3:
				cout << "Минимальное кол-во рейсов: ";
				Validator::checkInterval_int(connection);
				cout << "Максимальное кол-во рейсов: ";
				Validator::checkInterval_int(connection);
				break;
			default: break;
			}

			system("cls");
			cout << "Результат: " << endl;
			AirlineCases::output(connection);
			system("pause");

		}

	}
	else { cout << "Добавьте хотябы одну запись!" << endl; Sleep(2000); }
}

void AirlineCases::output(Connection& connection)
{
	cout << "|" << setw(5) << "#"
		<< "|" << setw(5) << "Код"
		<< "|" << setw(30) << "Название авиакомпании"
		<< "|" << setw(30) << "Тип перевозок"
		<< "|" << setw(20) << "Кол-во рейсов в год" 
		<< "|" << endl;

	int size = connection.recvInt();

	if (size > 0) {
		for (int i = 0; i < size; i++) {

			cout << "|" << setw(5) << i + 1;
			cout << "|" << setw(5) << connection.recvStr();
			cout << "|" << setw(30) << connection.recvStr();
			cout << "|" << setw(30) << connection.recvStr();
			cout << "|" << setw(20) << connection.recvInt();
			cout << "|" << endl;

		}
	}
	else { cout << "|" << setw(54) << "Нет записей" << setw(40) << "|" << endl; }
}
