#pragma once
#pragma comment (lib, "ws2_32.lib")
#pragma warning(disable: 4996)
#include <winsock2.h>

class Validator;

class Connection {

protected:

	SOCKET connection;
	SOCKADDR_IN address;
	char* message;

public:

	Connection() : message(0) {}
	~Connection() { delete[] message; }

	void conect();

	void sendStr(const char* str);
	char* recvStr(char*& str);
	char* recvStr();

	void sendInt(int value);
	int recvInt(int& value);
	int recvInt();

	void sendDouble(double value);
	double recvDouble(double& value);
	double recvDouble();

};