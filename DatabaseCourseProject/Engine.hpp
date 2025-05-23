#pragma once
#include "Table.hpp"
#include "Catalog.hpp"
#include "CatalogCommandManager.hpp"
#include "CommandLineManager.hpp"

class Engine {
private:
	OutputConsoleWritter outputConsoleWriter;
	InputConsoleReader inputConsoleReader;
	CatalogCommandManager catalogCommandManager;
	CommandLineManager commandLineManager;

	void dispatchCommand(std::vector<std::string> commandParams);

public:
	Engine(OutputConsoleWritter outputConsoleWriter,
		InputConsoleReader inputConsoleReader, 
		CatalogCommandManager catalogCommandManager, 
		CommandLineManager commandLineManager);

	~Engine();

	void run();
};