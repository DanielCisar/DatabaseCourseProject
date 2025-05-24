#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "CommandParser.hpp"

class InputConsoleReader {
public:
	InputConsoleReader();
	~InputConsoleReader();

	std::vector<std::string> readLine() const;
	std::string readLineAsString() const;
};