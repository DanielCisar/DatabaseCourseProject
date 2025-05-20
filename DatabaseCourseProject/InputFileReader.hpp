#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "Table.hpp"
#include "ColumnFactory.hpp"
#include "CommandParser.hpp"
#include "Catalog.hpp"

class InputFileReader {
private:
	ColumnFactory factory;
public:
	InputFileReader(ColumnFactory cf, CommandParser parser);
	~InputFileReader();

	Table readTableFromFile(const std::string& filepath);
	Catalog readCatalogFromFile(const std::string& filepath);
};