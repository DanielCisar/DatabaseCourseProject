#include "Engine.hpp"
#include <iostream>

int main() {
	InputFileReader fileReader;

	OutputConsoleWritter outputConsoleWriter;

	OutputFileWritter outputFileWritter;

	InputConsoleReader inputConsoleReader;

	CatalogCommandManager catalogCommandManager(fileReader,
		outputConsoleWriter,
		outputFileWritter,
		inputConsoleReader);

	CommandLineManager commandLineManager(fileReader
		, outputConsoleWriter
		, outputFileWritter);

	Engine engine(outputConsoleWriter,
		inputConsoleReader,
		catalogCommandManager,
		commandLineManager);

	engine.run();

	return 0;
}