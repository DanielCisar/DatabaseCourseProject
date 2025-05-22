#include "InputConsoleReader.hpp"
#include <vector>
#include <string>

InputConsoleReader::InputConsoleReader(CommandParser parser) {

}
InputConsoleReader::~InputConsoleReader() {

}

std::vector<std::string> InputConsoleReader::readLine() {

    std::string input;

    std::getline(std::cin, input);

    return CommandParser::parseCommand(input, ' ');
}