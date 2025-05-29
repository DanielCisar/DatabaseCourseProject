#include "FileSaveCommand.hpp"
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

FileSaveCommand::FileSaveCommand(CommandContext& context)
	: context(context) {
}

void FileSaveCommand::execute(const std::vector<std::string>& params) {

	if (!context.loadedCatalogExists) {
		throw std::runtime_error("No file is currently loaded. Please open a file first. ");
		return;
	}

	for (auto& table : context.loadedCatalog) {
		try {
			context.outputFileWritter.writeTableToFile(table, table.getFilename());
		}
		catch (const std::exception& e) {
			context.outputConsoleWritter.printLine(e.what());
		}
	}

	try {
		context.outputFileWritter.writeCatalogToFile(context.loadedCatalog
			, context.loadedCatalog.getPath());
	}
	catch (const std::exception& e) {
		context.outputConsoleWritter.printLine(e.what());
	}

	context.outputConsoleWritter.printLine("Saved changes to same files. ");

}
