#include <iostream>
#include "OutputConsoleWritter.hpp"
#include <string>

/**
 * @brief Constructs a new `OutputConsoleWritter` instance.
 *
 * This constructor performs no specific initialization beyond default-constructing
 * member variables (of which there are none in this class).
 */
OutputConsoleWritter::OutputConsoleWritter() {

}

/**
 * @brief Destroys the `OutputConsoleWritter` instance.
 *
 * As `OutputConsoleWritter` does not manage any dynamically allocated resources,
 * the default destructor is sufficient for proper cleanup.
 */
OutputConsoleWritter::~OutputConsoleWritter() {

}

/**
 * @brief Prints a message to the console followed by a newline character.
 * @param messsage The string to be printed.
 */
void OutputConsoleWritter::printLine(const std::string& messsage) const {
	std::cout << messsage << std::endl;
}

/**
 * @brief Prints a message to the console without a trailing newline character.
 * @param message The string to be printed.
 */
void OutputConsoleWritter::print(const std::string& message) const {
	std::cout << message;
}