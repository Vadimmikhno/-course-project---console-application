#include "Connection.h"
#include "Validator.h"

void Connection::conect()
{
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0) {
		cout << "Ошибка загрузки библиотеки wsaData" << endl;
		system("pause");
		exit(1);
	}
	int SizeOfAddr = sizeof(address);
	address.sin_addr.s_addr = inet_addr("127.0.0.1");
	address.sin_port = htons(1111);
	address.sin_family = AF_INET;
	connection = socket(AF_INET, SOCK_STREAM, NULL);
	cout << "Нажмите любую клавишу чтобы подключится к серверу..." << endl; _getch();
	if (connect(connection, (SOCKADDR*)&address, SizeOfAddr) != 0) {
		cout << "ERROR: не удалось подключится к серверу!" << endl;
		system("pause");
		exit(1);
	}
	else { 
		cout << "Подключение к серверу произошло успешно!" << endl;
		Sleep(2000);
	}
}

void Connection::sendStr(const char* str)
{
	int msg_size = strlen(str);
	send(this->connection, (char*)&msg_size, sizeof(int), NULL);
	send(this->connection, str, msg_size, NULL);
}
char* Connection::recvStr(char*& str)
{
	int msg_size = 0;
	recv(this->connection, (char*)&msg_size, sizeof(int), NULL);
	char* msg = new char[msg_size + 1];
	msg[msg_size] = '\0';
	recv(this->connection, msg, msg_size, NULL);
	Validator::copyStr(str, msg);
	delete[] msg;
	return str;
}

char* Connection::recvStr()
{
	int msg_size = 0;
	recv(this->connection, (char*)&msg_size, sizeof(int), NULL);
	char* msg = new char[msg_size + 1];
	msg[msg_size] = '\0';
	recv(this->connection, msg, msg_size, NULL);
	Validator::copyStr(message, msg);
	delete[] msg;
	return message;
}

void Connection::sendInt(int value)
{
	char* str = new char[20];
	itoa(value, str, 10);
	int msg_size = strlen(str);
	send(this->connection, (char*)&msg_size, sizeof(int), NULL);
	send(this->connection, str, msg_size, NULL);
	delete[] str;
}

int Connection::recvInt(int& value)
{
	int msg_size = 0;
	recv(this->connection, (char*)&msg_size, sizeof(int), NULL);
	char* msg = new char[msg_size + 1];
	msg[msg_size] = '\0';
	recv(this->connection, msg, msg_size, NULL);
	value = atoi(msg);
	delete[] msg;
	return value;
}

int Connection::recvInt()
{
	int msg_size = 0, value;
	recv(this->connection, (char*)&msg_size, sizeof(int), NULL);
	char* msg = new char[msg_size + 1];
	msg[msg_size] = '\0';
	recv(this->connection, msg, msg_size, NULL);
	value = atoi(msg);
	delete[] msg;
	return value;
}

void Connection::sendDouble(double value)
{
	char* str = new char[50];
	sprintf(str, "%.2f", value);
	int msg_size = strlen(str);
	send(this->connection, (char*)&msg_size, sizeof(int), NULL);
	send(this->connection, str, msg_size, NULL);
	delete[] str;
}

double Connection::recvDouble(double& value)
{
	int msg_size = 0;
	recv(this->connection, (char*)&msg_size, sizeof(int), NULL);
	char* msg = new char[msg_size + 1]; msg[msg_size] = '\0';
	recv(this->connection, msg, msg_size, NULL);
	value = atof(msg);
	delete[] msg;
	return value;
}

double Connection::recvDouble()
{
	double value;
	int msg_size = 0;
	recv(this->connection, (char*)&msg_size, sizeof(int), NULL);
	char* msg = new char[msg_size + 1]; msg[msg_size] = '\0';
	recv(this->connection, msg, msg_size, NULL);
	value = atof(msg);
	delete[] msg;
	return value;
}
