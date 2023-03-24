#include "Validator.h"
#include "Connection.h"

void Validator::copyStr(char*& data_1, const char* data_2)
{
	delete[] data_1;
	data_1 = new char[strlen(data_2) + 1];
	strcpy(data_1, data_2);
}

void Validator::setStr(Connection& connection)
{
	char* str = new char[256];
	do {
		cin.clear(); 
		cin.getline(str, 256, '\n');
		if (strlen(str) == 0) {
			cout << "������ ������, ������� ������ ��� ���: ";
		}
	} while (strlen(str) == 0);
	connection.sendStr(str);
	delete[] str;
}

int Validator::checkInterval_int(Connection& connection)
{
	int min, max, value, controller;
	connection.recvInt(min);
	connection.recvInt(max);
	setStr(connection);
	connection.recvInt(controller);
	connection.recvInt(value);
	while (value < min || value > max || controller == -1) {
		cout << "��� ������ ��������, ���������� ��� ���: ";
		setStr(connection);
		connection.recvInt(controller);
		connection.recvInt(value);
	}
	return value;
}

double Validator::checkInterval_double(Connection& connection)
{
	double min, max, value;
	int controller;
	connection.recvDouble(min);
	connection.recvDouble(max);
	setStr(connection);
	connection.recvInt(controller);
	connection.recvDouble(value);
	while (value < min || value > max || controller == -1) {
		cout << "��� ������ ��������, ���������� ��� ���: ";
		setStr(connection);
		connection.recvInt(controller);
		connection.recvDouble(value);
	}
	return value;
}

void Validator::checkInterval_date(Connection& connection)
{
	int controller;
	Validator::setDate(connection);
	while (connection.recvInt(controller) == -1) {
		cout << "��� ������ ��������!" << endl;
		Validator::setDate(connection);
	}
}

void Validator::setPassport(Connection& connection)
{
	int controller;
	do {
		controller = 0;
		cout << "������� ����� � ��������: ";
		setStr(connection);
		connection.recvInt(controller);
		if (controller == -1)
			cout << "�������� ������ ����!" << endl;
	} while (controller == -1);
}

void Validator::encryption(Connection& connection)
{
	char BufForWriting[256];
	register int i;
	for (i = 0; (BufForWriting[i] = _getch()) != '\r';) {
		if (BufForWriting[i] == '\b' && i != 0) {
			cout << "\b \b";
			i--;
		}
		else if (BufForWriting[i] != '\b') {
			cout << "*";
			i++;
		}
	}
	BufForWriting[i] = '\0';
	cout << endl;
	if (strlen(BufForWriting) == 0)
		strcpy(BufForWriting, "0");
	connection.sendStr(BufForWriting);
}

void Validator::setFio(Connection& connection)
{
	cout << "�������: "; 
	Validator::setStr(connection);
	cout << "���: ";
	Validator::setStr(connection);
	cout << "��������: ";
	Validator::setStr(connection);
}

void Validator::setDate(Connection& connection)
{
	int controller;
	do {
		cout << "������� ����(dd.mm.yyyy): ";
		Validator::setStr(connection);
		if (connection.recvInt(controller) == -1)
			cout << "�������� ������ ����!" << endl;
	} while (controller == -1);
}

void Validator::setLogin(Connection& connection)
{
	int controller;
	while (1) {
		cout << "�����: ";
		Validator::setStr(connection);
		connection.recvInt(controller);
		if (controller == 1)
			cout << "����� ������ ��������� 6 ��� ����� ��������!" << endl;
		else if (controller == 2)
			cout << "����� ����� ��������� ��������� �����, ����� � ����������� �������(-._)!" << endl;
		else if (controller == 3)
			cout << "������ ����� �����!" << endl;
		else break;
	}
}

void Validator::setPassword(Connection& connection)
{
	int controller;
	do {
		cout << "������� ������: ";
		Validator::encryption(connection);
		connection.recvInt(controller);
		if (controller == 0) {
			cout << "��������� ������: ";
			Validator::encryption(connection);
			connection.recvInt(controller);
		}
		switch (controller) {
		case 1:
			cout << "������ ������ ��������� 8 ��� ����� ��������!" << endl;
			break;
		case 2:
			cout << "������ �� ������ ��������� �������!" << endl;
			break;
		case 3:
			cout << "������ ������ ��������� ����� � �����!" << endl;
			break;
		case 4:
			cout << "������ �� ���������!" << endl;
			break;
		default: break;
		}
	} while (controller != 0);
}
