#include "CatalogRenameCommand.hpp"
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
#include "IOUtils.hpp"

CatalogRenameCommand::CatalogRenameCommand(CommandContext& context)
	: context(context) {
}

void CatalogRenameCommand::execute(const std::vector<std::string>& params) {

    if (!context.loadedCatalog) {
        throw std::runtime_error("There is no file opened! ");
    }

    try {
		const std::string& oldName = params[1];
		const std::string& newName = params[2];

        Table& table = context.loadedCatalog->returnTableByName(oldName);
        table.setName(newName);
        context.outputConsoleWritter.printLine("Table " + oldName + " has been renamed to " + newName);
    }
    catch (const std::exception& e) {
        context.outputConsoleWritter.printLine(e.what());
    }
}
