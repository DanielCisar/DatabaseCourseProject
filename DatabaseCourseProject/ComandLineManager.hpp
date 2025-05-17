#pragma once
#include "Table.hpp"
#include "TableColumn.hpp"
#include "DoubleColumn.hpp"
#include "IntegerColumn.hpp"
#include "StringColumn.hpp"
#include "ColumnType.hpp"
#include "ColumnFactory.hpp"
#include <vector>
#include <string>
#include "Catalog.hpp"

class CommandLineManager {
private:
	Catalog catalog;
	std::string openedFile;
public:
	CommandLineManager();
	~CommandLineManager();

	Table open(std::string filepath);
	void close();
	void save();
	void saveAs(std::string filepath);
	void help();
};