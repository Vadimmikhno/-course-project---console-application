#include "Opinion.h"

void Opinion::setMarks(AirlineCases& airline_cases, Connection& connection)
{
	connection.sendInt(this->marks.size());
	for (auto& i : this->marks)
		for (auto& j : i)
			if (j != -1) {
				AirlineCases::output(airline_cases.getVec(), connection);
				getMarks(connection);
				j = Validator::checkInterval(0, 30, connection);
			}
}

void Opinion::getMarks(Connection& connection)
{
	connection.sendInt(this->marks.size());
	for (auto& i : this->marks)
		for (auto& j : i)
			if (j != -1) connection.sendInt(j);
}

void Opinion::findWeight(vector<double>& result)
{
	int counter = 0;
	double weight;
	for (auto& i : this->marks) {
		weight = 0.0000;
		for (auto& j : i)
			if (j != -1)
				weight += j;
		weight /= 30.00;
		weight /= this->marks.size() * (this->marks.size() - 1);
		result[counter] += weight;
		counter++;
	}
}

ostream& operator<<(ostream& stream, Opinion& obj)
{
	stream << obj.getUserName() << " " << obj.getMarks().size();
	for (auto& i : obj.getMarks())
		for (auto& j : i)
			stream << " " << j;
	return stream;
}

istream& operator>>(istream& stream, Opinion& obj)
{
	vector<vector<int>> marks;
	char user_name[100];
	int size;

	if (stream >> user_name >> size) {
		marks.resize(size);
		for (int i = 0; i < size; i++) {
			marks[i].resize(size);
			for (int j = 0; j < size; j++) {
				stream >> marks[i][j];
			}
		}
		obj.set(user_name, marks);
	}

	return stream;
}
