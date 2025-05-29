#include "FileCloseCommand.hpp"
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

FileCloseCommand::FileCloseCommand(CommandContext& context)
	: context(context) {
}

void FileCloseCommand::execute(const std::vector<std::string>& params) {

	if (!context.loadedCatalogExists) {
		throw std::runtime_error("No file is currently loaded. Please open a file first.");
		return;
	}

	context.outputConsoleWritter.printLine("Closed the currently opened file: "
		+ context.loadedCatalog.getPath());

	context.loadedCatalogExists = false;
}
