#include "CommandParser.hpp"

std::vector<std::string> CommandParser::parseCommand(const std::string& line, char delimiter) {
    std::vector<std::string> tokens;
    std::string currentToken;

    for (char ch : line) {
        if (ch == delimiter) {
            tokens.push_back(currentToken);
            currentToken.clear(); 
        }
        else {
            currentToken += ch; 
        }
    }
    tokens.push_back(currentToken);

    return tokens;

}