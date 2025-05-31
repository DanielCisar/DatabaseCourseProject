#pragma once
#include <iostream>	
#include <string>

class OutputConsoleWritter {
public:
	/**
	* @brief Constructs a new `OutputConsoleWritter` instance.
	*
	* Initializes the writer. No specific resources are managed by the constructor itself.
	*/
	OutputConsoleWritter();

	/**
	* @brief Destroys the `OutputConsoleWritter` instance.
	*
	* Cleans up any resources held by the writer. As this class currently
	* doesn't manage dynamic memory, the default destructor is sufficient.
	*/
	~OutputConsoleWritter();
	/**
	* @brief Prints a message to the console followed by a newline character.
	*
	* This method sends the given string `message` to `std::cout` and then
	* flushes the output stream, ensuring the message appears immediately on the console.
	*
	* @param messsage The string to be printed.
	*/
	void printLine(const std::string& messsage) const;

	/**
	* @brief Prints a message to the console without a trailing newline character.
	*
	* This method sends the given string `message` to `std::cout` without
	* adding a newline. This allows subsequent output to continue on the same line.
	*
	* @param message The string to be printed.
	*/
	void print(const std::string& message) const;
};