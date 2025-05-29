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

/**
 * @brief Constructs an open command for file and catalog operations.
 *
 * @param context A reference to the shared command context.
 */
FileOpenCommand::FileOpenCommand(CommandContext& context)
	: context(context) {
}

/**
 * @brief Executes the open command which sets the loaded catalog.
 *
 * This function checks if a file exists. If it does, it reads its content
 * andloads it into the memory. If no file is open, it creates
 * a new empty one.
 *
 * @param params The only parameter is the file path of the catalog.
 *
 * @throws std::runtime_error if the parameters are not the exact value and if there is an issue opening a file.
 */
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
