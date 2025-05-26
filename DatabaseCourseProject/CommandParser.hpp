#pragma once
#include <vector>
#include <string>

class CommandParser {
public:

	static std::vector<std::string> parseCommand(const std::string& line, char delimiter);
	static std::vector<std::string> parseRawCommand(const std::string& line);
};