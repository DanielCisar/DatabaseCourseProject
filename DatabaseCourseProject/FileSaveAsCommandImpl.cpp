#include "FileSaveAsCommand.hpp"
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

FileSaveAsCommand::FileSaveAsCommand(CommandContext& context)
	: context(context) {
}

void FileSaveAsCommand::execute(const std::vector<std::string>& params) {

	if (!context.loadedCatalog) {
		throw std::runtime_error("No file is currently loaded. Please open a file first.");
		return;
	}
	const std::string& filepath = params[1];

	Catalog newCatalog(filepath);

	std::string targetFolder = FileUtils::getDirectoryPath(filepath);

	for (auto& table : *context.loadedCatalog) {
		std::string newName = "copy_" + table.getName();
		std::string newTablePath = targetFolder + "/copy_" + newName + ".csv";


		try {
			Table newTable = table.cloneWithNewNameAndPath(newName, newTablePath);
			context.outputFileWritter.writeTableToFile(newTable, newTablePath);
			newCatalog.addTable(newTable);
		}
		catch (const std::exception& e) {
			context.outputConsoleWritter.printLine(e.what());
		}
	}
	try {
		context.outputFileWritter.writeCatalogToFile(newCatalog, filepath);
		context.outputConsoleWritter.printLine("Changes saved to: " + filepath);
	}
	catch (const std::exception& e) {
		context.outputConsoleWritter.printLine(e.what());
	}

}
