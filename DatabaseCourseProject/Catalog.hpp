#pragma once
#include <vector>
#include "Table.hpp"
#include <string>

class Catalog {
private:
	std::vector<Table> tableCollection;
	std::string catalogPath;

public:
	Catalog(const std::string catalogPath);
	~Catalog();
	Catalog& operator=(const Catalog& other);
	void addTable(Table table);
	void removeTable(int index);
	Table returnTableByName(std::string name) const;
	std::string getPath() const;

	std::vector<Table>::iterator begin();
	std::vector <Table>::iterator end();
};