#pragma once
#include "Table.hpp"
#include "Catalog.hpp"
#include "CatalogCommandManager.hpp"
#include "CommandLineManager.hpp"

class Engine {
private:
	OutputConsoleWritter outputConsoleWriter;
	InputConsoleReader inputConsoleReader;

	Catalog currentLoadedCatalog;

	CatalogCommandManager& catalogCommandManager; 
	CommandLineManager& commandLineManager;      

	void dispatchCommand(std::vector<std::string> commandParams);

public:
	Engine(InputFileReader& inputFileReader,
		OutputConsoleWritter& outputConsoleWritter,
		OutputFileWritter& outputFileReader,
		InputConsoleReader& inputConsoleReader);

	~Engine();

	void run();
};