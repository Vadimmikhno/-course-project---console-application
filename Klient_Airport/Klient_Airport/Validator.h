#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <iomanip>

using namespace std;

class Connection;

class Validator {

public:

	static void copyStr(char*& data_1, const char* data_2);
	static void setStr(Connection& connection);

	static int checkInterval_int(Connection& connection);
	static double checkInterval_double(Connection& connection);
	static void checkInterval_date(Connection& connection);

	static void setPassport(Connection& connection);
	static void setFio(Connection& connection);
	static void setDate(Connection& connection);
	static void setLogin(Connection& connection);
	static void setPassword(Connection& connection);
	static void encryption(Connection& connection);

};