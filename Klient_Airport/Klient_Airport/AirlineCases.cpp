#include "AirlineCases.h"

void AirlineCases::setType(Connection& connection)
{
	cout << "��� ���������" << endl;
	for (int i = 0; i < 3; i++) 
		cout << i + 1 << " - " << connection.recvStr() << endl;
	cout << "��� �����: ";
	Validator::checkInterval_int(connection);
}

void AirlineCases::add(Connection& connection)
{
	system("cls");
	cout << "��������� ���������� �����������" << endl;
	cout << "(��������� ���� ����)" << endl;
	cout << "��� ������: " << connection.recvStr() << endl;
	cout << "�������� ������������: ";
	Validator::setStr(connection);
	AirlineCases::setType(connection);
	cout << "���-�� ������ � ���: ";
	Validator::checkInterval_int(connection);
	cout << "�������� ������?" << endl;
	cout << "(1 - �� / 2 - ���): ";
	Validator::checkInterval_int(connection);
}

void AirlineCases::edit(Connection& connection)
{
	cout << "�������� ������, ������� ������ �������������(0 - ��������� �����): ";
	
	if (Validator::checkInterval_int(connection) != 0) {
		
		cout << "�������� ��������������" << endl;
		cout << "1 - �������� ������������" << endl;
		cout << "2 - ��� ���������" << endl;
		cout << "3 - ���-�� ������ � ���" << endl;
		cout << "��� �����(0 - ��������� �����): ";

		switch (Validator::checkInterval_int(connection)) {
		case 1:
			cout << "�������� �����������: ";
			Validator::setStr(connection);
			break;
		case 2:
			AirlineCases::setType(connection);
			break;
		case 3:
			cout << "���-�� ������ � ���: ";
			Validator::checkInterval_int(connection);
			break;
		default: break;
		}

	}
}

void AirlineCases::del(Connection& connection)
{
	cout << "�������� ������, ������� ������ �������(0 - ��������� �����): ";
	if (Validator::checkInterval_int(connection) != 0) {
		cout << "����������� ��������?" << endl;
		cout << "(1 - �� / 2 - ���): ";
		Validator::checkInterval_int(connection);
	}
}

void AirlineCases::searchFiltr(Connection& connection)
{
	if (connection.recvInt() > 0) {
		
		system("cls");
		cout << "�������� ������ � ����������" << endl;
		cout << "1 - ����� �� ����" << endl;
		cout << "2 - ����� �� �������� ������������" << endl;
		cout << "3 - ���������� �� ���-�� ������ � ���" << endl;
		cout << "4 - ���������� �� ���� ���������" << endl;
		cout << "5 - ���������� �� ���-�� ������ � ���" << endl;
		cout << "��� �����(0 - ��������� �����): ";

		int choise = Validator::checkInterval_int(connection);

		if (choise != 0) {

			switch (choise) {
			case 1:
				cout << "������� ���: ";
				Validator::setStr(connection);
				break;
			case 2:
				cout << "������� ��������� �����������: ";
				Validator::setStr(connection);
				break;
			case 3:
				cout << "����������� ���-�� ������: ";
				Validator::checkInterval_int(connection);
				cout << "������������ ���-�� ������: ";
				Validator::checkInterval_int(connection);
				break;
			default: break;
			}

			system("cls");
			cout << "���������: " << endl;
			AirlineCases::output(connection);
			system("pause");

		}

	}
	else { cout << "�������� ������ ���� ������!" << endl; Sleep(2000); }
}

void AirlineCases::output(Connection& connection)
{
	cout << "|" << setw(5) << "#"
		<< "|" << setw(5) << "���"
		<< "|" << setw(30) << "�������� ������������"
		<< "|" << setw(30) << "��� ���������"
		<< "|" << setw(20) << "���-�� ������ � ���" 
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
	else { cout << "|" << setw(54) << "��� �������" << setw(40) << "|" << endl; }
}
