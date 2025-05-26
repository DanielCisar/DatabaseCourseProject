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
		std::shared_ptr<Catalog> catalog = std::make_shared<Catalog>(fileReader
			.readCatalogFromFile(filepath));
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

	outputConsoleWriter.printLine("Closed the currently opened file: "
		+ currentLoadedFile->getPath());

	loadedFileExists = false;
	currentLoadedFile.reset();

}

void CommandLineManager::save() {
	if (!loadedFileExists) {
		throw std::runtime_error("No file is currently loaded. Please open a file first. ");
		return;
	}

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

	outputConsoleWriter.printLine("Saved changes to same files. ");
}

void CommandLineManager::saveAs(const std::string& filepath) {
	if (!loadedFileExists) {
		throw std::runtime_error("No file is currently loaded. Please open a file first.");
		return;
	}

	Catalog newCatalog(filepath);

	std::string targetFolder = FileUtils::getDirectoryPath(filepath);

	for (auto& table : *currentLoadedFile) {
		std::string newName = "copy_" + table.getName();
		std::string newTablePath = targetFolder + "/copy_" + newName + ".csv";


		try {
			Table newTable = table.cloneWithNewNameAndPath(newName, newTablePath);
			outputFileWritter.writeTableToFile(newTable, newTablePath);
			newCatalog.addTable(newTable);
		}
		catch (const std::exception& e) {
			outputConsoleWriter.printLine(e.what());
		}
	}
	try {
		outputFileWritter.writeCatalogToFile(newCatalog, filepath);
		outputConsoleWriter.printLine("Changes saved to: " + filepath);
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

std::shared_ptr<Catalog> CommandLineManager::getCurrentLoadedFile() {
	return currentLoadedFile;
}

void CommandLineManager::setCurrentLoadedFile(std::shared_ptr<Catalog> catalog) {
	this->currentLoadedFile = catalog;
	this->loadedFileExists = (catalog != nullptr);
}