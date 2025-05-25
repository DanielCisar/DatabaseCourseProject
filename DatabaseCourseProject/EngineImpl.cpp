#include "Engine.hpp"

void Engine::dispatchCommand(std::vector<std::string> commandParams) {
	std::string command = commandParams[0];

	if (command == "open") {
		try {
			commandLineManager.open(commandParams[1]);
			catalogCommandManager.setLoadedCatalog(commandLineManager.getCurrentLoadedFile());
		}
		catch (const std::exception& e) {
			outputConsoleWriter.printLine(e.what());
		}
	}
	else if (command == "close") {
		try {
			commandLineManager.close();
			catalogCommandManager.closeLoadedCatalog();
		}
		catch (const std::exception& e) {
			outputConsoleWriter.printLine(e.what());
		}
	}
	else if (command == "save") {
		try {
			commandLineManager.setCurrentLoadedFile(catalogCommandManager.getCurrentLoadedFile());

			commandLineManager.save();
		}
		catch (const std::exception& e) {
			outputConsoleWriter.printLine(e.what());
		}
	}
	else if (command == "saveas") {
		try {
			commandLineManager.saveAs(commandParams[1]);
		}
		catch (const std::exception& e) {
			outputConsoleWriter.printLine(e.what());
		}
	}
	else if (command == "help") {
		try {
			commandLineManager.help();
		}
		catch (const std::exception& e) {
			outputConsoleWriter.printLine(e.what());
		}
	}
	else if (command == "exit") {
		try {
			commandLineManager.exit();
		}
		catch (const std::exception& e) {
			outputConsoleWriter.printLine(e.what());
		}
	}
	else if (command == "import") {
		try {
			catalogCommandManager.import(commandParams[1]);
		}
		catch (const std::exception& e) {
			outputConsoleWriter.printLine(e.what());
		}
	}
	else if (command == "showtables") {
		try {
			catalogCommandManager.showTables();
		}
		catch (const std::exception& e) {
			outputConsoleWriter.printLine(e.what());
		}
	}
	else if (command == "describe") {
		try {
			catalogCommandManager.describe(commandParams[1]);
		}
		catch (const std::exception& e) {
			outputConsoleWriter.printLine(e.what());
		}
	}
	else if (command == "print") {
		try {
			catalogCommandManager.print(commandParams[1]);
		}
		catch (const std::exception& e) {
			outputConsoleWriter.printLine(e.what());
		}
	}
	else if (command == "export") {
		try {
			catalogCommandManager.exportTable(commandParams[1], commandParams[2]);
		}
		catch (const std::exception& e) {
			outputConsoleWriter.printLine(e.what());
		}
	}
	else if (command == "select") {
		try {
			catalogCommandManager.select(std::stoi(commandParams[1]), commandParams[2], commandParams[3]);
		}
		catch (const std::exception& e) {
			outputConsoleWriter.printLine(e.what());
		}
	}
	else if (command == "addcolumn") {
		try {
			if (commandParams[3] == "String") {
				catalogCommandManager.addColumn(commandParams[1], commandParams[2], ColumnType::STRING);
			}
			else if (commandParams[3] == "Integer") {
				catalogCommandManager.addColumn(commandParams[1], commandParams[2], ColumnType::INTEGER);
			}
			else if (commandParams[3] == "Double") {
				catalogCommandManager.addColumn(commandParams[1], commandParams[2], ColumnType::DOUBLE);
			}
			else {
				outputConsoleWriter.printLine("Unsupported type. ");
			}
		}
		catch (const std::exception& e) {
			outputConsoleWriter.printLine(e.what());
		}

	}
	else if (command == "update") {
		try {
			catalogCommandManager.update(commandParams[1],
				std::stoi(commandParams[2]),
				commandParams[3],
				std::stoi(commandParams[4]),
				commandParams[5]);
		}
		catch (const std::exception& e) {
			outputConsoleWriter.printLine(e.what());
		}
	}
	else if (command == "delete") {
		try {
			catalogCommandManager.deleteRows(commandParams[1],
				std::stoi(commandParams[2]),
				commandParams[3]);
		}
		catch (const std::exception& e) {
			outputConsoleWriter.printLine(e.what());
		}
	}
	else if (command == "insert") {
		try {
			std::vector<std::string> values;

			for (auto& p : commandParams) {
				if (p == command) {
					continue;
				}
				values.push_back(p);
			}

			catalogCommandManager.insert(commandParams[1], values);
		}
		catch (const std::exception& e) {
			outputConsoleWriter.printLine(e.what());
		}
	}
	else if (command == "innerjoin") {
		try {
			catalogCommandManager.innerJoin(commandParams[1],
				std::stoi(commandParams[2]),
				commandParams[3],
				std::stoi(commandParams[4]));
		}
		catch (const std::exception& e) {
			outputConsoleWriter.printLine(e.what());
		}
	}
	else if (command == "rename") {
		try {
			catalogCommandManager.rename(commandParams[1], commandParams[2]);
		}
		catch (const std::exception& e) {
			outputConsoleWriter.printLine(e.what());
		}
	}
	else if (command == "count") {
		try {
			catalogCommandManager.count(commandParams[1], std::stoi(commandParams[2]), commandParams[3]);
		}
		catch (const std::exception& e) {
			outputConsoleWriter.printLine(e.what());
		}
	}
	else if (command == "agregate") {
		try {
			catalogCommandManager.agregate(commandParams[1],
				std::stoi(commandParams[2]),
				commandParams[3],
				std::stoi(commandParams[4]),
				commandParams[5]);
		}
		catch (const std::exception& e) {
			outputConsoleWriter.printLine(e.what());
		}
	}
	else {
		outputConsoleWriter.printLine("Unsupported command! Please enter another. ");
	}
}

Engine::Engine(OutputConsoleWritter outputConsoleWriter,
	InputConsoleReader inputConsoleReader,
	CatalogCommandManager& catalogCommandManager,
	CommandLineManager& commandLineManager) :
	outputConsoleWriter(outputConsoleWriter),
	inputConsoleReader(inputConsoleReader),
	catalogCommandManager(catalogCommandManager),
	commandLineManager(commandLineManager)

{
}

Engine::~Engine() {

}

void Engine::run() {
	std::vector<std::string> params = inputConsoleReader.readLine();

	while (true) {

		this->dispatchCommand(params);

		if (params[0] == "exit") {
			break;
		}
		params = inputConsoleReader.readLine();
	}
}