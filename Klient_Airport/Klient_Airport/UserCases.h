#pragma once
#include "Validator.h"
#include "Connection.h"

class UserCases {

public:

	static int singIn(Connection& connection);
	static void add(Connection& connection);
	static void edit(Connection& connection);
	static void del(Connection& connection);
	static void output(Connection& connection);
	static void searchFiltr(Connection& connection);
	static void header();

};