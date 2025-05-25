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

CommandLineManager::CommandLineManager(InputFileReader fileReader,
	OutputConsoleWritter outputConsoleWriter,
	OutputFileWritter outputFileWritter
) :
	loadedFileExists(false),
	fileReader(fileReader),
	outputConsoleWriter(outputConsoleWriter),
	outputFileWritter(outputFileWritter)
{
	this->currentLoadedFile = Catalog();
}

CommandLineManager::~CommandLineManager() {

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
	try {
		Catalog catalog = fileReader.readCatalogFromFile(filepath);
		outputConsoleWriter.printLine("Successfully opened: " + filepath);

		this->currentLoadedFile = catalog;
		this->loadedFileExists = true;

	}
	catch (const std::exception& e) {
		outputConsoleWriter.printLine(e.what());
		return;
	}

}

void CommandLineManager::close() {
	if (!loadedFileExists) {
		throw std::runtime_error("No file is currently loaded. Please open a file first.");
		return;
	}

	loadedFileExists = false;
	outputConsoleWriter.printLine("Closed the currently opened file: "
		+ currentLoadedFile.getPath());
}

void CommandLineManager::save() {
	if (!loadedFileExists) {
		throw std::runtime_error("No file is currently loaded. Please open a file first. ");
		return;
	}

	for (auto& table : currentLoadedFile) {
		try {
			outputFileWritter.writeTableToFile(table, table.getFilename());
		}
		catch (const std::exception& e) {
			outputConsoleWriter.printLine(e.what());
		}
	}

	try {
		outputFileWritter.writeCatalogToFile(currentLoadedFile, currentLoadedFile.getPath());
	}
	catch (const std::exception& e) {
		outputConsoleWriter.printLine(e.what());
	}

	outputConsoleWriter.printLine("Saved changes to same files. ");
}

void CommandLineManager::saveAs(std::string filepath) {
	if (!loadedFileExists) {
		throw std::runtime_error("No file is currently loaded. Please open a file first.");
		return;
	}

	Catalog newCatalog(filepath);

	for (auto& table : currentLoadedFile) {
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
		outputFileWritter.writeCatalogToFile(currentLoadedFile, filepath);
	}
	catch (const std::exception& e) {
		outputConsoleWriter.printLine(e.what());
	}
}

void CommandLineManager::help() {
	outputConsoleWriter.printLine("The following commands are supported:");
	outputConsoleWriter.printLine("open <file>	opens <file>");
	outputConsoleWriter.printLine("close			closes currently opened file");
	outputConsoleWriter.printLine("save			saves the currently open file");
	outputConsoleWriter.printLine("saveas <file>	saves the currently open file in <file>");
	outputConsoleWriter.printLine("help			prints this information");
	outputConsoleWriter.printLine("exit			exists the program");
}

void CommandLineManager::exit() {
	outputConsoleWriter.printLine("Exiting the program... ");

}

Catalog& CommandLineManager::getCurrentLoadedFile() {
	return currentLoadedFile;
}

void CommandLineManager::setCurrentLoadedFile(Catalog& catalog) {
	this->currentLoadedFile = catalog;
}