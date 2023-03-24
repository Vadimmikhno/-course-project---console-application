#pragma once
#include "Validator.h"
#include "Connection.h"

class Date
{
private:

	int day;
	int month;
	int year;
	char* fullDate;

public:

	Date() : day(0), month(0), year(0), fullDate(0) { }
	Date(int day, int month, int year) : day(0), month(0), year(0), fullDate(0) {
		set(day, month, year);
	}
	Date(const Date& obj) : day(0), month(0), year(0), fullDate(0) {
		set(obj.day, obj.month, obj.year);
	}
	~Date() { delete[] fullDate; }

	void set(int day, int month, int year) {
		this->day = day; this->month = month; this->year = year;
	}
	void set(Connection& connection);
	void setLocalDate();

	void setDay(int day) { this->day = day; }
	void setMonth(int month) { this->month = month; }
	void setYear(int year) { this->year = year; }

	int getDay() { return this->day; }
	int getMonth() { return this->month; }
	int getYear() { return this->year; }

	char* toString();

	friend istream& operator>>(istream& stream, Date& obj);
	friend ostream& operator<<(ostream& stream, const Date& obj);

	void operator=(const Date& obj) {
		set(obj.day, obj.month, obj.year);
	}
	bool operator>(const Date& obj);
	bool operator<(const Date& obj);
	bool operator==(const Date& obj);

	static void checkInterval(Date& value, Date min, Date max, Connection& connection);

};
