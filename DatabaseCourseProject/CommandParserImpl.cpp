#include "CommandParser.hpp"

/**
 * @brief Parses a string into a vector of tokens using a specified delimiter.
 *
 * This implementation builds `currentToken` character by character until the `delimiter`
 * is encountered. Once the delimiter is hit, the `currentToken` is pushed to `tokens`,
 * and `currentToken` is cleared. After the loop, the last `currentToken` is also added.
 *
 * @param line The input string to parse.
 * @param delimiter The character used to separate tokens.
 * @return A `std::vector<std::string>` containing the parsed tokens.
 */
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

/**
 * @brief Parses a raw command string, specifically handling spaces and quoted arguments.
 *
 * This method iterates through the input string, identifying tokens based on spaces
 * while respecting double quotes. Characters within quotes are part of a single token.
 * Double quotes themselves are consumed and not included in the output tokens.
 *
 * @param line The raw command string to parse.
 * @return A `std::vector<std::string>` containing the parsed tokens.
 */
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
