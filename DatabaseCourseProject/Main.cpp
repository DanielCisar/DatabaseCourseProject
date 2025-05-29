#include "Engine.hpp"
#include <iostream>

int main() {
	InputFileReader fileReader;

	OutputConsoleWritter outputConsoleWriter;

	OutputFileWritter outputFileWritter;

	InputConsoleReader inputConsoleReader;

	Engine engine(outputConsoleWriter,
		inputConsoleReader,
		outputFileWritter,
		fileReader);

	engine.run();

	return 0;
}