#include "OpinionCases.h"

void OpinionCases::read()
{
	ifstream fin("Opinion.txt");
	Opinion obj;
	while (fin >> obj)
		this->vecOpinion.push_back(obj);
	fin.close();
}

void OpinionCases::write()
{
	ofstream fout("Opinion.txt", ios_base::trunc);
	for (auto& element : this->vecOpinion)
		fout << element << endl;
	fout.close();
}

void OpinionCases::result(Connection& connection, int size)
{
	vector<double> result(size, 0.0000);

	for (auto& element : vecOpinion)
		element.findWeight(result);

	int index_best_alter = 0;
	for (int i = 0; i < size; i++)
		if (result[index_best_alter] < result[i])
			index_best_alter = i;

	connection.sendInt(size);

	for (auto& element : result)
		connection.sendDouble(element);

	connection.sendInt(index_best_alter);

	result.clear();
}

Opinion& OpinionCases::getOpinion(char* user_name, int size)
{
	for (auto& element : this->vecOpinion)
		if (strcmp(element.getUserName(), user_name) == 0)
			return element;
	Opinion obj;
	obj.setUserName(user_name);
	obj.setDefaultMarks(size);
	this->vecOpinion.push_back(obj);
	return this->vecOpinion[vecOpinion.size() - 1];
}
