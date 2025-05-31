#pragma once
#include <vector>
#include <string>

/**
 * @class CommandParser
 * @brief A static utility class for parsing command strings into tokens.
 *
 * `CommandParser` provides methods to break down a single input string
 * (representing a command and its arguments) into a collection of individual
 * tokens (words or phrases). It supports parsing by a custom delimiter
 * and a specialized parsing for raw commands that handles quoted strings.
 */
class CommandParser {
public:
    /**
     * @brief Parses a string into a vector of tokens using a specified delimiter.
     *
     * This method iterates through the input `line` and splits it into substrings
     * wherever the `delimiter` character is found. Each substring becomes a token
     * in the returned vector. Consecutive delimiters will result in empty tokens.
     *
     * @param line The input string to parse.
     * @param delimiter The character used to separate tokens (e.g., ' ', ',').
     * @return A `std::vector<std::string>` containing the parsed tokens.
     */
	static std::vector<std::string> parseCommand(const std::string& line, char delimiter);

    /**
    * @brief Parses a raw command string, specifically handling spaces and quoted arguments.
    *
    * This method is designed to parse commands from user input where arguments
    * might contain spaces and be enclosed in double quotes.
    * - Spaces outside of double quotes act as delimiters.
    * - Text inside double quotes is treated as a single token, including spaces.
    * - Double quotes themselves are not included in the resulting tokens.
    * - Multiple consecutive spaces outside quotes will generate empty tokens.
    *
    * @param line The raw command string to parse, potentially containing spaces and quotes.
    * @return A `std::vector<std::string>` containing the parsed tokens, with quotes removed.
    */
	static std::vector<std::string> parseRawCommand(const std::string& line);
};