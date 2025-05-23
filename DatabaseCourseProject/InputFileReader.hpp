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
public:
	InputFileReader();
	~InputFileReader();

	Table readTableFromFile(const std::string& filepath);
	Catalog readCatalogFromFile(const std::string& filepath);
};