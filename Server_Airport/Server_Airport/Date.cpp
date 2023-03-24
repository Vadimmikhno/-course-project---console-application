#include "Date.h"

void Date::set(Connection& connection)
{
	Date date;
	int controller;
	char* str = new char[11];
	do {
		controller = 0;
		connection.recvStr(str);
		if (strlen(str) != 10 || str[2] != '.' || str[5] != '.' || str[6] == '0') {
			controller = -1;
		}
		else {
			for (int i = 0; i < 10; i++) {
				if (i != 2 && i != 5) {
					if (!isdigit(str[i])) {
						controller = -1;
						break;
					}
				}
			}
			if (controller != -1) {
				char day[3], month[3], year[5];
				if (str[0] == '0') {
					day[0] = str[1];
					day[1] = '\0';
				}
				else {
					day[0] = str[0];
					day[1] = str[1];
					day[2] = '\0';
				}
				if (str[3] == '0') {
					month[0] = str[4];
					month[1] = '\0';
				}
				else {
					month[0] = str[3];
					month[1] = str[4];
					month[2] = '\0';
				}
				strcpy(year, &str[6]);
				date.day = atoi(day);
				date.month = atoi(month);
				date.year = atoi(year);
				/*cout << date.day << endl;
				cout << date.month << endl;
				cout << date.year << endl;*/
				controller = Validator::validDate(date.day, date.month, date.year);
			}
		}
		connection.sendInt(controller);
	} while (controller == -1);
	this->day = date.day;
	this->month = date.month;
	this->year = date.year;
	delete[] str;
}
void Date::setLocalDate()
{
	struct tm localtime;
	time_t now = time(NULL);
	localtime_s(&localtime, &now);
	this->day = localtime.tm_mday;
	this->month = localtime.tm_mon + 1;
	this->year = localtime.tm_year + 1900;
}
char* Date::toString()
{
	char date[11];
	char day[3], month[3], year[5];
	strcpy(date, _itoa(this->day, day, 10));
	if (date[1] == '\0') {
		date[1] = date[0];
		date[0] = '0';
	}
	date[2] = '.'; date[3] = '\0';
	strcat(date, _itoa(this->month, month, 10));
	if (date[4] == '\0') {
		date[4] = date[3];
		date[3] = '0';
	}
	date[5] = '.'; date[6] = '\0';
	strcat(date, _itoa(this->year, year, 10));
	Validator::copyStr(this->fullDate, date);
	return this->fullDate;
}
bool Date::operator>(const Date& obj)
{
	if ((this->year > obj.year) ||
		(this->year == obj.year && this->month > obj.month) ||
		(this->year == obj.year && this->month == obj.month && this->day > obj.day)) {
		return true;
	}
	else return false;
}
bool Date::operator<(const Date& obj)
{
	if ((this->year < obj.year) ||
		(this->year == obj.year && this->month < obj.month) ||
		(this->year == obj.year && this->month == obj.month && this->day < obj.day)) {
		return true;
	}
	else return false;
}
bool Date::operator==(const Date& obj)
{
	if (this->year == obj.year && this->month == obj.month && this->day) return true;
	else return false;
}
void Date::checkInterval(Date& value, Date min, Date max, Connection& connection)
{
	value.set(connection);
	while (value < min || value > max) {
		connection.sendInt(-1);
		value.set(connection);
	}
	connection.sendInt(0);
}
istream& operator>>(istream& stream, Date& obj)
{
	int day, month, year;
	if (stream >> day >> month >> year)
		obj.set(day, month, year);
	return stream;
}
ostream& operator<<(ostream& stream, const Date& obj)
{
	stream << obj.day << " " << obj.month << " " << obj.year;
	return stream;
}