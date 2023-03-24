#pragma once
#include "Opinion.h"

class OpinionCases {

protected:

	vector<Opinion> vecOpinion;

public:

	OpinionCases() : vecOpinion(0) {}
	~OpinionCases() { vecOpinion.clear(); }

	vector<Opinion>& getVec() { return this->vecOpinion; }

	void read();
	void write();
	void delAll() { this->vecOpinion.clear(); }
	void result(Connection& connection, int size);
	Opinion& getOpinion(char* user_name, int size);

};