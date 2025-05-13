#pragma once
#include <string>
#include <vector>
#include "TableColumn.hpp"

class Table {
private:
	std::vector<TableColumn> columns;
	std::string name;
	std::string filename;


	template <typename T>
	bool checkValidityOfTemplateParameters(const T& value);

	template <typename T>
	bool checkEquivelenceBetweenColumnAndType(int column, const T& value);
public:

	Table(const std::vector<TableColumn> columns, const std::string name, const std::string filename);

	~Table();

	//TODO: Think about copy constructor and assignment operator and iterator

	using iterator = std::vector<TableColumn>::iterator;
	
	iterator begin() { return columns.begin(); }
	iterator end() { return columns.end(); }

	std::string getName() const;

	std::string getFilename() const;

	std::string getColumnNameAtGivenIndex(int index) const;

	std::string toString() const;

	void deleteGivenRow(int index);

	int getNumberOfColumns() const;
};