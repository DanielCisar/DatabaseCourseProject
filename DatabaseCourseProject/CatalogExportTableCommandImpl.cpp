#include "CatalogExportTableCommand.hpp"
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

CatalogExportTableCommand::CatalogExportTableCommand(CommandContext& context)
	: context(context) {
}
void CatalogExportTableCommand::execute(const std::vector<std::string>& params) {

	if (!context.loadedCatalog) {
		throw std::runtime_error("There is no file opened! ");
	}
	const std::string& name = params[1];
	const std::string& filepath = params[2];

    Table table = context.loadedCatalog->returnTableByName(name);

    context.outputFileWritter.writeTableToFile(table, filepath);
    context.outputConsoleWritter.printLine("Table exported to: " + filepath);
}
