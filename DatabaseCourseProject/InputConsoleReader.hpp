#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "CommandParser.hpp"

/**
 * @class InputConsoleReader
 * @brief Handles reading input from the console.
 *
 * This class provides utility methods to read lines of text from standard
 * input (`std::cin`), either as a single string or parsed into a vector of strings
 * based on whitespace or a specified delimiter. It's designed to abstract
 * the console input mechanism.
 */
class InputConsoleReader {
public:

	/**
	* @brief Constructs a new `InputConsoleReader` instance.
	*
	* Initializes the reader. No specific resources are managed by the constructor itself.
	*/
	InputConsoleReader();

	/**
	* @brief Destroys the `InputConsoleReader` instance.
	*
	* Cleans up any resources held by the reader. As this class currently
	* doesn't manage dynamic memory, the default destructor is sufficient.
	*/
	~InputConsoleReader();

	/**
	* @brief Reads a line of input from the console and parses it into words.
	*
	* This method reads an entire line from `std::cin` until a newline character
	* is encountered. The read line is then passed to `CommandParser::parseCommand`
	* to split it into a vector of strings, using space (' ') as the delimiter.
	*
	* @return A `std::vector<std::string>` containing the words from the input line.
	*/
	std::vector<std::string> readLine() const;

	/**
	* @brief Reads an entire line of input from the console as a single string.
	*
	* This method reads all characters from `std::cin` up to the next newline
	* character and returns them as a single `std::string`, without any parsing or splitting.
	*
	* @return A `std::string` containing the entire line of input.
	*/
	std::string readLineAsString() const;
};