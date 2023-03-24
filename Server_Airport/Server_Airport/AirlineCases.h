#pragma once
#include "Airline.h"

class AirlineCases {

protected:

	vector<Airline> vecAirline;

public:

	AirlineCases() : vecAirline(0) {}
	~AirlineCases() { vecAirline.clear(); }

	vector<Airline>& getVec() { return this->vecAirline; }

	void read();
	void write();

	void add(Connection& connection);
	void edit(Connection& connection);
	void del(Connection& connection);
	void searchFiltr(Connection& connection);
	
	static void output(vector<Airline>& vecAirline, Connection& connection);

};