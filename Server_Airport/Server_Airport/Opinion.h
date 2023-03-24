#pragma once
#include "Connection.h"
#include "Validator.h"
#include "AirlineCases.h"

class Opinion {

protected:

	char* user_name;
	vector<vector<int>> marks;

public:

	Opinion() : user_name(0),  marks(0) {}
	Opinion(const Opinion& obj) : user_name(0), marks(0) {
		set(obj.user_name, obj.marks);
	}
	~Opinion() { 
		for (auto& element : marks)
			element.clear();
		marks.clear();
		delete[] user_name;
	}

	void setDefaultMarks(int size) {
		this->marks.resize(size);
		for (int i = 0; i < marks.size(); i++) {
			for (int j = 0; j < marks.size(); j++) {
				if (i == j) this->marks[i].push_back(-1);
				else this->marks[i].push_back(0);
			}
		}
	}

	void setMarks(AirlineCases& airline_cases, Connection& connection);
	void setUserName(const char* user_name) { Validator::copyStr(this->user_name, user_name); }

	void getMarks(Connection& connection);
	vector<vector<int>>& getMarks() { return this->marks; }
	char* getUserName() { return this->user_name; }

	void set(const char* user_name,const vector<vector<int>>& marks) {
		Validator::copyStr(this->user_name, user_name);
		this->marks = marks;
	}

	void findWeight(vector<double>& result);

	friend ostream& operator<<(ostream& stream, Opinion& obj);
	friend istream& operator>>(istream& stream, Opinion& obj);

	void operator=(const Opinion& obj) {
		set(obj.user_name, obj.marks);
	}

};
