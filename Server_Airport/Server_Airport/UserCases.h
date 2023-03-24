#pragma once
#include "User.h"

class UserCases {

protected:

	vector<User> vecUser;
	User active;

public:

	UserCases() : vecUser(0) {}
	~UserCases() { vecUser.clear(); }

	int signIn(Connection& connection);

	vector<User>& getVector() { return vecUser; }
	User& getActive() { return active; }


	void encryp();
	void decryp();
	void read(Connection& connection);
	void write();
	void add(const char* status, Connection& connection);
	void edit(Connection& connection);
	void del(Connection& connection);
	void searchFiltr(Connection& connection);

	static void output(vector<User>& vecUser, Connection& connection);

};