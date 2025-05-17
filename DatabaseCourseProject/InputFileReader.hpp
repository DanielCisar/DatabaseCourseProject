#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "Table.hpp"
#include "ColumnFactory.hpp"

class InputFileReader {
private:
	std::string filepath;
	ColumnFactory factory;
	std::vector<std::string> split(const std::string& line, char delimiter);
public:
	InputFileReader(std::string filepath, ColumnFactory cf);
	~InputFileReader();
	Table readFromFile();
};