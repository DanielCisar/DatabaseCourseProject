#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "Table.hpp"

class InputFileReader {
private:
	std::string filepath;
public:
	InputFileReader(std::string filepath);
	~InputFileReader();
	Table readFromFile();
};