#include "OpinionCases.h"

void OpinionCases::result(Connection& connection)
{
	int size = connection.recvInt();

	for (int i = 0; i < size; i++)
		cout << "W(" << i + 1 << ") = " << connection.recvDouble() << endl;

	cout << "������������ �" << connection.recvInt() + 1 
		<< " �������� ������ �� ������ ���������" << endl;
}

void OpinionCases::getMarks(Connection& connection)
{
	int size = connection.recvInt();

	cout << "������� ������: " << endl;

	cout << "|" << setw(5) << " ";
	for (int i = 0; i < size; i++)
		cout << "|" << setw(3) << "�" << setw(2) << i + 1;
	cout << "|" << endl;

	for (int i = 0; i < size; i++) {
		cout << "|" << setw(3) << "�" << setw(2) << i + 1;
		for (int j = 0; j < size; j++) {
			if (i != j) cout << "|" << setw(5) << connection.recvInt();
			else cout << "|" << setw(5) << "---";
		}
		cout << "|" << endl;
	}
}

void OpinionCases::setMarks(Connection& connection)
{
	int size = connection.recvInt();

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (i != j) {
				system("cls");
				AirlineCases::output(connection);
				getMarks(connection);
				cout << "��������� �������[" << i << "][" << j << "]: ";
				Validator::checkInterval_int(connection);
			}
		}
	}

}
