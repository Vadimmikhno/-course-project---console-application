#pragma once
#include "Human.h"

class Human;

class User : public Human {

protected:

	char* status;
	char* login;
	char* password;
	int lockStatus;

public:

	User() : Human(), status(0), login(0), password(0), lockStatus(0) { }
	User(const User& obj) : Human(obj), status(0), login(0), password(0), lockStatus(0) {
		set(obj.status, obj.login, obj.password, obj.lockStatus);
	}

	~User() {
		delete[] status;
		delete[] login;
		delete[] password;
	}

	void set(const char* status, const char* login, const char* password, int block) {
		Validator::copyStr(this->status, status);
		Validator::copyStr(this->login, login);
		Validator::copyStr(this->password, password);
		this->lockStatus = block;
	}

	void setStatus(const char* status) { Validator::copyStr(this->status, status); }
	void setLogin(vector<User>& vecUser, Connection& connection);
	void setPassword(Connection& connection);
	void setLockStatus() {
		if (lockStatus == 0)
			lockStatus = 1;
		else lockStatus = 0;
	}

	char* getStatus() { return status; }
	char* getLogin() { return login; }
	char* getPassword() { return password; }
	int getLockStatus() { return lockStatus; }

	void encrypPassword() {
		for (int i = 0; password[i] != '\0'; i++) {
			password[i] -= 5;
		}
	}
	void decrypPassword() {
		for (int i = 0; password[i] != '\0'; i++) {
			password[i] += 5;
		}
	}

	void operator=(const User& obj) {
		set(obj.status, obj.login, obj.password, obj.lockStatus);
		Human::operator=(obj);
	}
	/*bool operator<(User& obj);*/
	//static bool compSurname(User& A, User& B);

	friend istream& operator>>(istream& stream, User& obj);
	friend ostream& operator<<(ostream& stream, User& obj);

};