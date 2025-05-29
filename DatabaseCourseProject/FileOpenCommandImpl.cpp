#include "FileOpenCommand.hpp"
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

FileOpenCommand::FileOpenCommand(CommandContext& context)
	: context(context) {
}

void FileOpenCommand::execute(const std::vector<std::string>& params) {

	if (params.size() != 2) {
		throw std::runtime_error("Not enough parameters. ");
	}

	const std::string& filepath = params[1];

	if (!FileUtils::fileExists(filepath)) {
		std::ofstream newFile(filepath);
		if (!newFile) {
			throw std::runtime_error("Error creating file at: " + filepath);
		}
		newFile.close();
		context.outputConsoleWritter.printLine("Created new empty file: " + filepath);

	}
	try {
		Catalog catalog = Catalog(context.inputFileReader
			.readCatalogFromFile(filepath));
		context.outputConsoleWritter.printLine("Successfully opened: " + filepath);

		context.loadedCatalog = catalog;
		context.loadedCatalogExists = true;
	}
	catch (const std::exception& e) {
		context.outputConsoleWritter.printLine(e.what());
		return;
	}
}
