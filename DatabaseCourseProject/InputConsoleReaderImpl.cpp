#include "InputConsoleReader.hpp"
#include <vector>
#include <string>

InputConsoleReader::InputConsoleReader() {

}
InputConsoleReader::~InputConsoleReader() {

}

std::vector<std::string> InputConsoleReader::readLine() const{

    std::string input;

    std::getline(std::cin, input);

    return CommandParser::parseCommand(input, ' ');
}

std::string InputConsoleReader::readLineAsString() const {
	std::string input;
	std::getline(std::cin, input);
	return input;
}