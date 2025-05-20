#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "CommandParser.hpp"

class InputConsoleReader {
public:
	InputConsoleReader(CommandParser parser);
	~InputConsoleReader();

	std::vector<std::string> parseLine();
};