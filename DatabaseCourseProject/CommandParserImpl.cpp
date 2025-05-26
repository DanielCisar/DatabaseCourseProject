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

std::vector<std::string> CommandParser::parseRawCommand(const std::string& line) {
    std::vector<std::string> tokens;
    std::string token;
    bool insideQuotes = false;

    for (char ch : line) {
        if (ch == '"') {
            insideQuotes = !insideQuotes;
            if (!insideQuotes && !token.empty()) {
                tokens.push_back(token);
                token.clear();
            }
        }
        else if (ch == ' ' && !insideQuotes) {
            if (!token.empty()) {
                tokens.push_back(token);
                token.clear();
            }
        }
        else {
            token += ch;
        }
    }

    if (!token.empty()) {
        tokens.push_back(token);
    }

    return tokens;
}
