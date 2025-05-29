#include "CatalogShowTablesCommand.hpp"
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

CatalogShowTablesCommand::CatalogShowTablesCommand(CommandContext& context)
	: context(context) {
}

void CatalogShowTablesCommand::execute(const std::vector<std::string>& params) {

    if (!context.loadedCatalogExists) {
        throw std::runtime_error("There is no file opened! ");
    }

    context.outputConsoleWritter.printLine("List of tables: ");

    for (auto& table : context.loadedCatalog) {
        context.outputConsoleWritter.printLine(table.getName());
    }
}
