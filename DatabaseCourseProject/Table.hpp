#pragma once
#include <string>
#include <vector>
#include "TableColumn.hpp"

class Table {
private:
	std::vector<TableColumn*> columns;
	std::string name;
	std::string filename;

public:

	Table(const std::vector<TableColumn*> columns, const std::string name, const std::string filename);

	~Table();

	Table& operator=(const Table& other);

	using iterator = std::vector<TableColumn*>::iterator;
	using const_iterator = std::vector<TableColumn*>::const_iterator;

	iterator begin() { return columns.begin(); }
	iterator end() { return columns.end(); }

	const_iterator begin() const { return columns.begin(); }
	const_iterator end() const { return columns.end(); }

	std::string getName() const;

	std::string getFilename() const;

	std::string getColumnNameAtGivenIndex(int index) const;

	std::string printRow(int index) const;

	void deleteGivenRow(int index);

	void addColumn(TableColumn* col);

	int getNumberOfColumns() const;

	void setTablePath(std::string filename);
};