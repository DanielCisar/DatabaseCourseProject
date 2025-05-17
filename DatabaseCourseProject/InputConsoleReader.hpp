#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "CommandParser.hpp"

class InputConsoleReader {
private:
	CommandParser parser;
public:
	InputConsoleReader(CommandParser parser);
	~InputConsoleReader();

	std::vector<std::string> parseLine();
};