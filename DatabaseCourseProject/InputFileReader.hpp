#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "Table.hpp"
#include "ColumnFactory.hpp"
#include "CommandParser.hpp"

class InputFileReader {
private:
	ColumnFactory factory;
	CommandParser parser;

public:
	InputFileReader(ColumnFactory cf, CommandParser parser);
	~InputFileReader();

	Table readFromFile(std::string filepath);
};