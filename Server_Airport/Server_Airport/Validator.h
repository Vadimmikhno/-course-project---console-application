#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

class Connection;

class Validator {

public:

	static void copyStr(char*& data_1, const char* data_2);
	static void setStr(char*& str, Connection& connection);

	static int checkInt(int& value, Connection& connection);
	static int checkInterval(int min, int max, Connection& connection);

	static int checkDouble(double& value, Connection& connection);
	static double checkInterval(double min, double max, Connection& connection);

	static void generCode(char*& str, int lenth);
	static void setPassport(char*& str, Connection& connection);
	static int validDate(int day, int month, int year);
	static bool comparator(char* str_1, char* str_2);

};