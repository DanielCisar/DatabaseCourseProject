#include "InputConsoleReader.hpp"
#include <vector>
#include <string>
#include <iostream> 


/**
 * @brief Constructs a new `InputConsoleReader` instance.
 *
 * This constructor performs no specific initialization beyond default-constructing
 * member variables (of which there are none in this class).
 */
InputConsoleReader::InputConsoleReader() {

}

/**
 * @brief Destroys the `InputConsoleReader` instance.
 *
 * As `InputConsoleReader` does not own any dynamically allocated resources,
 * the default destructor behavior is sufficient for proper cleanup.
 */
InputConsoleReader::~InputConsoleReader() {

}


/**
 * @brief Reads a line of input from the console and parses it into words.
 *
 * Utilizes `std::getline` to read the full line from `std::cin`, then delegates
 * parsing to `CommandParser::parseCommand` using a space as the delimiter.
 *
 * @return A `std::vector<std::string>` containing the space-separated words from the input.
 */
std::vector<std::string> InputConsoleReader::readLine() const{

    std::string input;

    std::getline(std::cin, input);

    return CommandParser::parseCommand(input, ' ');
}

/**
 * @brief Reads an entire line of input from the console as a single string.
 *
 * Reads input from `std::cin` up to the newline character and returns it as is.
 * No parsing or tokenization is performed.
 *
 * @return A `std::string` containing the raw input line.
 */
std::string InputConsoleReader::readLineAsString() const {
	std::string input;
	std::getline(std::cin, input);
	return input;
}