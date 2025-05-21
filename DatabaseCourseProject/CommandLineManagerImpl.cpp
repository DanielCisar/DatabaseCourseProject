#include "CommandLineManager.hpp"
#include "Table.hpp"
#include "TableColumn.hpp"
#include "DoubleColumn.hpp"
#include "IntegerColumn.hpp"
#include "StringColumn.hpp"
#include "ColumnType.hpp"
#include "ColumnFactory.hpp"
#include <vector>
#include <string>
#include "Catalog.hpp"
#include <filesystem>
#include <stdexcept>
#include <fstream>
#include "FileUtils.hpp"
#include <ostream>
#include <iostream>

CommandLineManager::CommandLineManager(CatalogRepository repo,
	InputFileReader fileReader, 
	OutputConsoleWritter outputConsoleWriter, 
	OutputFileWritter outputFileWritter
) :
repo(repo),
loadedFileExists(false), 
currentLoadedFile(nullptr), 
fileReader(fileReader), 
outputConsoleWriter(outputConsoleWriter), 
outputFileWritter(outputFileWritter)
{
	
}

CommandLineManager::~CommandLineManager() {
	delete currentLoadedFile;
}

void CommandLineManager::open(const std::string& filepath) {
	if (!FileUtils::fileExists(filepath)) {
		std::ofstream newFile(filepath);
		if (!newFile) {
			throw std::runtime_error("Error creating file at: " + filepath);
		}
		newFile.close();
		outputConsoleWriter.printLine("Created new empty file: " + filepath);

	}

	Catalog catalog = fileReader.readCatalogFromFile(filepath);

	std::ifstream file(filepath);
	if (!file.is_open()) {
		throw std::runtime_error("Failed to open catalog file: " + filepath);
	}

	std::string line;

	while (std::getline(file, line)) {
		if (line.empty()) {
			continue;
		}
		std::vector<std::string> params = CommandParser::parseCommand(line, ',');
		if (params.size() != 2) {
			throw std::runtime_error("Wrong file format. ");
		}

		std::string path = params[1];

		try{
			Table table = fileReader.readTableFromFile(filepath);
			catalog.addTable(table);
		}
		catch (std::exception& e) {
			outputConsoleWriter.printLine(e.what());
		}
	}
	outputConsoleWriter.printLine("Successfully opened: " + filepath);

	if (currentLoadedFile != nullptr) {
		delete currentLoadedFile;
		currentLoadedFile = nullptr;
	}

	currentLoadedFile = &catalog;
	loadedFileExists = true;

	file.close();
}

void CommandLineManager::close() {
	delete currentLoadedFile;
	currentLoadedFile = nullptr;
	loadedFileExists = false;
}

void CommandLineManager::save() {
	for (auto& table : *currentLoadedFile) {
		try {
			outputFileWritter.writeTableToFile(table, table.getFilename());
		}
		catch (const std::exception& e) {
			outputConsoleWriter.printLine(e.what());
		}
	}
	try {
		outputFileWritter.writeCatalogToFile(*currentLoadedFile, currentLoadedFile->getPath());
	}
	catch (const std::exception& e) {
		outputConsoleWriter.printLine(e.what());
	}
}

void CommandLineManager::saveAs(std::string filepath) {
	Catalog newCatalog(filepath);

	for (auto& table : *currentLoadedFile) {
		std::string newTablePath = "copy_" + table.getName() + ".csv";

		try {
			outputFileWritter.writeTableToFile(table, newTablePath);
		}
		catch (const std::exception& e) {
			outputConsoleWriter.printLine(e.what());
		}
		Table newTable = table;
		newTable.setTablePath(newTablePath);

		newCatalog.addTable(table);
	}
	try {
		outputFileWritter.writeCatalogToFile(*currentLoadedFile, filepath);
	}
	catch (const std::exception& e) {
		outputConsoleWriter.printLine(e.what());
	}
}