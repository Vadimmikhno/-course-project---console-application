#include "Validator.h"
#include "Connection.h"

void Validator::copyStr(char*& data_1, const char* data_2)
{
	delete[] data_1;
	data_1 = new char[strlen(data_2) + 1];
	strcpy(data_1, data_2);
}

void Validator::setStr(char*& str, Connection& connection)
{
	char* buf = new char(0);
	connection.recvStr(buf);
	for (int i = 0; buf[i] != '\0'; i++)
		if (buf[i] == ' ')
			buf[i] = '_';
	copyStr(str, buf);
	delete[] buf;
}

int Validator::checkInt(int& value, Connection& connection)
{
	int counter = 0, i = 0, result = 0;
	char* BufForWriting = new char(0);
	setStr(BufForWriting, connection);
	if (BufForWriting[0] == '-') {
		counter++;
		i++;
	}
	for (i; BufForWriting[i] != '\0'; i++)
		if (isdigit(BufForWriting[i]))
			counter++;
	if (strlen(BufForWriting) != counter)
		result = -1;
	else value = atoi(BufForWriting);
	delete[] BufForWriting;
	return result;
}

int Validator::checkInterval(int min, int max, Connection& connection)
{
	int value = 0, controller = 0;
	connection.sendInt(min);
	connection.sendInt(max);
	controller = checkInt(value, connection);
	connection.sendInt(controller);
	connection.sendInt(value);
	while (value < min || value > max || controller == -1) {
		controller = checkInt(value, connection);
		connection.sendInt(controller);
		connection.sendInt(value);
	}
	return value;
}

int Validator::checkDouble(double& value, Connection& connection)
{
	int controller1 = 0, controller2 = 0, result = 0, i = 0;
	char* BufForWriting = new char(0);
	setStr(BufForWriting, connection);
	if (BufForWriting[0] == '-') {
		controller1++;
		i++;
	}
	for (i; BufForWriting[i] != '\0'; i++)
	{
		if (isdigit(BufForWriting[i]))
			controller1++;
		if (BufForWriting[i] == ',')
			controller2++;
	}
	if (strlen(BufForWriting) != (controller1 + controller2) || controller2 > 1)
		result = -1;
	else value = atof(BufForWriting);
	delete[] BufForWriting;
	return result;
}

double Validator::checkInterval(double min, double max, Connection& connection)
{
	double value = 0.0;
	int controller = 0;
	connection.sendDouble(min);
	connection.sendDouble(max);
	controller = checkDouble(value, connection);
	connection.sendInt(controller);
	connection.sendDouble(value);
	while (value < min || value > max || controller == -1) {
		controller = checkDouble(value, connection);
		connection.sendInt(controller);
		connection.sendDouble(value);
	}
	return value;
}

void Validator::generCode(char*& str, int lenth)
{
	char bufWrt[256], randNum[2];
	bufWrt[0] = '\0';
	srand(time(NULL));
	for (int i = 0; i < lenth; i++) {
		strcat(bufWrt, _itoa(rand() % 10, randNum, 10));
		bufWrt[i + 1] = '\0';
	}
	Validator::copyStr(str, bufWrt);
}

void Validator::setPassport(char*& str, Connection& connection)
{
	char symbols[] = "QWERTYUIOPASDFGHJKLZXCVBNM";
	int controller;
	char* seriesNumberPassport = new char(0);
	do {
		controller = 0;
		connection.recvStr(seriesNumberPassport);
		if (strlen(seriesNumberPassport) == 9) {
			for (int i = 0; i < 2; i++) {
				controller = -1;
				for (int j = 0; j < symbols[j] != '\0'; j++) {
					if (symbols[j] == seriesNumberPassport[i]) {
						controller = 0;
						break;
					}
				}
				if (controller == -1) break;
			}
			if (controller == 0) {
				for (int i = 2; seriesNumberPassport[i] != '\0'; i++) {
					if (!isdigit(seriesNumberPassport[i])) {
						controller = -1;
						break;
					}
				}
			}
		}
		else controller = -1;
		connection.sendInt(controller);
	} while (controller != 0);
	copyStr(str, seriesNumberPassport);
	delete[] seriesNumberPassport;
}

int Validator::validDate(int day, int month, int year)
{
	int controller = 0;
	int days_in_month[] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
	if (year % 4 == 0)
		days_in_month[2] = 29;
	if ((month < 1) || (month > 12))
		controller = -1;
	if ((day < 1) || (day > days_in_month[month]))
		controller = -1;
	return controller;
}

bool Validator::comparator(char* str_1, char* str_2)
{
	int len;
	if (strlen(str_1) < strlen(str_2))
		len = strlen(str_1);
	else len = strlen(str_2);
	for (int i = 0; i < len; i++) {
		if (str_1[i] < str_2[i])
			return true;
		if (str_1[i] > str_2[i])
			return false;
	}
	if (strlen(str_1) < strlen(str_2))
		return true;
	if (strlen(str_1) > strlen(str_2))
		return false;
	return false;
}
