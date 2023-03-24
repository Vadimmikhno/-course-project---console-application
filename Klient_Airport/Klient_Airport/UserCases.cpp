#include "UserCases.h"

int UserCases::singIn(Connection& connection)
{
	int controller;

	do {

		system("cls");

		cout << "�����: ";
		Validator::setStr(connection);
		cout << "������: ";
		Validator::encryption(connection);

		connection.recvInt(controller);

		if (controller == 0) {
			cout << "�������� ����� ��� ������!" << endl;
			cout << "����������� ��� ���? (1 - �� / 2 - ���): ";
			if (Validator::checkInterval_int(connection) == 2)
				controller = 4;
		}
		else if (controller == 3) {
			cout << "������ ������� ������ �������������!" << endl;
			Sleep(2000);
		}

	} while (controller == 0);

	return controller;

}

void UserCases::add(Connection& connection)
{
	char* status = new char[0];
	system("cls");
	cout << "����������� <" << connection.recvStr(status) << ">" << endl;
	cout << "��������� ���" << endl;
	Validator::setFio(connection);
	cout << "���� ��������" << endl;
	Validator::checkInterval_date(connection);
	Validator::setPassport(connection);
	Validator::setLogin(connection);
	Validator::setPassword(connection);
	if (strcmp(status, "ADMIN") != 0) {
		cout << "����������� �����������?" << endl;
		cout << "(1 - �� / 2 - ���): ";
		Validator::checkInterval_int(connection);
	}
	delete[] status;
}

void UserCases::edit(Connection& connection)
{
	if (connection.recvInt() > 0) {
		cout << "�������� ����� ������������, �������� ������ �������������(0 - ��������� �����): ";
		if (Validator::checkInterval_int(connection) != 0) {
			cout << "�������� ��������������" << endl;
			cout << "1 - �����" << endl;
			cout << "2 - ������" << endl;
			cout << "3 - ������ ����������" << endl;
			cout << "4 - ���" << endl;
			cout << "5 - ���� ��������" << endl;
			cout << "6 - ������ ��������" << endl;
			cout << "��� �����(0 - ��������� �����): ";
			switch (Validator::checkInterval_int(connection)) {
			case 1:
				Validator::setLogin(connection);
				break;
			case 2:
				Validator::setPassword(connection);
				break;
			case 3:
				if (connection.recvInt() == 0) {
					cout << "������ ������������� ������� ������������!" << endl;
					Sleep(2000);
				}
				break;
			case 4:
				cout << "��������� ���" << endl;
				Validator::setFio(connection);
				break;
			case 5:
				cout << "���� ��������" << endl;
				Validator::checkInterval_date(connection);
				break;
			case 6:
				Validator::setPassport(connection);
				break;
			default: break;
			}
		}
	}
	else { cout << "��� �������������!" << endl; Sleep(1500); }
}

void UserCases::del(Connection& connection)
{
	if (connection.recvInt() > 0) {
		cout << "�������� ����� ������������, �������� ������ �������(0 - ��������� �����): ";
		if (Validator::checkInterval_int(connection) != 0) {
			if (connection.recvInt() == 0) {
				cout << "������ ������� ������� ������������!" << endl;
				Sleep(2000);
			}
			else {
				cout << "����������� ��������?" << endl;
				cout << "(1 - �� / 2 - ���): ";
				Validator::checkInterval_int(connection);
			}
		}
	}
	else { cout << "��� �������������!" << endl; Sleep(1500); }
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
		cout << "|" << setw(62) << "��� �������" << setw(50) << "|" << endl;
	}
}

void UserCases::searchFiltr(Connection& connection)
{
	if (connection.recvInt() > 0) {
		cout << "�������� ����� � ����������" << endl;
		cout << "1 - ����� �� �������" << endl;
		cout << "2 - ����� �� ������" << endl;
		cout << "3 - ����� �� ����� � ��������" << endl;
		cout << "4 - ���������� �� �������(�-�)" << endl;
		cout << "5 - ���������� �� ���� ��������" << endl;
		cout << "��� �����(0 - ��������� �����): ";
		int choise = Validator::checkInterval_int(connection);
		if (choise != 0) {
			if (choise >= 1 && choise <= 3) {
				cout << "������� ���������� ��� ������: ";
				Validator::setStr(connection);
			}
			system("cls");
			UserCases::header();
			UserCases::output(connection);
			system("pause");
		}
	}
	else { cout << "��� �������������!" << endl; Sleep(1500); }
}

void UserCases::header()
{
	cout << "|" << setw(5) << "#" << "|" << setw(10) << "������"
		<< "|" << setw(20) << "�����" << "|" << setw(10) << "����������"
		<< "|" << setw(30) << "���" << "|" << setw(15) << "������ ��������"
		<< "|" << setw(15) << "���� ��������" << "|" << endl;
}
