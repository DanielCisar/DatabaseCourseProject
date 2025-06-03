#include "Engine.hpp"
#include <iostream>

/**
 * @brief The entry point of the Database Course Project application.
 *
 * This `main` function initializes all necessary core components of the database system,
 * including readers and writers for console and file I/O. It then instantiates
 * the `Engine` class, which encapsulates the main application logic, and starts
 * the command-line interface.
 *
 * The `main` function is responsible for setting up the environment and
 * initiating the application's runtime, after which control is handed over
 * to the `Engine::run()` method.
 *
 * @return 0 upon successful execution and program termination.
 */
int main() {

	OutputConsoleWritter outputConsoleWriter;

	OutputFileWritter outputFileWritter;

	InputConsoleReader inputConsoleReader;

	InputFileReader fileReader(outputConsoleWriter);

	Engine engine(outputConsoleWriter,
		inputConsoleReader,
		outputFileWritter,
		fileReader);

	engine.run();

	return 0;
}