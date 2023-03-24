# include "WorkWithTables.h"

void WorkWithTables::workWithAirlineForAdmin(Connection& connection)
{

	int choise;

	do {

		system("cls");
		AirlineCases::output(connection);
		cout << "1 - �������� ������������" << endl;
		cout << "2 - ������������� ������������" << endl;
		cout << "3 - ������� ������������" << endl;
		cout << "4 - ��������� ������ � ����������" << endl;
		cout << "5 - ���������� ��������� ����������� �� ������ ���������" << endl;
		cout << "��� ����� (0 - ��������� �����): ";

		choise = Validator::checkInterval_int(connection);

		switch (choise) {
		case 1:
			if (connection.recvInt() > 0) {
				cout << "��� ���������� ������������ ����� ������� ������� ���������." << endl;
				cout << "����������� ��������? (1 - �� / 2 - ���): ";
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
				cout << "��� �������� ������������ ����� ������� ������� ���������." << endl;
				cout << "����������� ��������? (1 - �� / 2 - ���): ";
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
				cout << "�� ���� ������� ��� �� ��������� �������!" << endl;
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
		cout << "���: " << connection.recvStr() << endl;
		AirlineCases::output(connection);
		cout << "1 - ��������� ������ � ����������" << endl;
		cout << "2 - ��������� ������� ������" << endl;
		cout << "3 - ����������� ������� ������" << endl;
		cout << "4 - ���������� ��������� ������������ �� ������ ���������" << endl;
		cout << "5 - �����" << endl;
		cout << "��� �����: ";
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
				cout << "��������� ����� ������������� �������� ������ 2 ������������!" << endl;
				Sleep(2000);
			}
			break;
		case 3:
			if (connection.recvInt() > 1) {
				OpinionCases::getMarks(connection);
				system("pause");
			}
			else {
				cout << "��������� ����� ������������� �������� ������ 2 ������������!" << endl;
				Sleep(2000);
			}
			break;
		case 4:
			if (connection.recvInt() > 0) {
				OpinionCases::result(connection);
				system("pause");
			}
			else {
				cout << "�� ���� ������� ��� �� ��������� �������!" << endl;
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
		cout << "1 - �������� ��������" << endl;
		cout << "2 - ������������� ������������" << endl;
		cout << "3 - ������� ������������" << endl;
		cout << "4 - ��������� ������ � ����������" << endl;
		cout << "��� �����(0 - ��������� �����): ";
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
