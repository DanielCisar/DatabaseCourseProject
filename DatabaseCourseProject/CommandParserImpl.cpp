#include "CommandParser.hpp"
#include <vector>
#include <string>

CommandParser::CommandParser() {

}
CommandParser::~CommandParser() {

}

std::vector<std::string> CommandParser::parseCommand(const std::string& line, char delimiter) {
    std::vector<std::string> tokens;
    int pos = 0;
    int prevPos = 0;

    for (char el : line) {
        if (el == delimiter) {
            std::string subStr = line.substr(prevPos + 1, pos + 1);

            tokens.push_back(subStr);

            prevPos = pos;
        }
        ++pos;
    }

    return tokens;
}