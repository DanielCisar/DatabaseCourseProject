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

    for (size_t i = 0; i < line.size(); ++i) {
        char ch = line[i];

        if (ch == '"') {
            insideQuotes = !insideQuotes;
            continue;
        }

        if (ch == ' ' && !insideQuotes) {
            tokens.push_back(token);
            token.clear();

            while (i + 1 < line.size() && line[i + 1] == ' ') {
                tokens.emplace_back("");
                ++i;
            }
        }
        else {
            token += ch;
        }
    }

    tokens.push_back(token);

    return tokens;

}
