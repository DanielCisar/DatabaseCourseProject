#include "CatalogPrintCommand.hpp"
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

CatalogPrintCommand::CatalogPrintCommand(CommandContext& context)
	: context(context) {
}

void CatalogPrintCommand::execute(const std::vector<std::string>& params) {

    if (!context.loadedCatalog) {
        throw std::runtime_error("There is no file opened! ");
    }

	const std::string& name = params[1];

    try {
        Table table = context.loadedCatalog->returnTableByName(name);

        std::string command;

        context.outputConsoleWritter.printLine("Table: " + name);

        for (auto& col : table) {
            context.outputConsoleWritter.print(col->getName() + " ");
        }
        context.outputConsoleWritter.printLine("");
        for (auto& col : table) {
            context.outputConsoleWritter.print(col->getTypeAsString() + " ");
        }
        context.outputConsoleWritter.printLine("");
        std::vector<std::string> rows;

        int size = table.getColumnAtGivenIndex(0)->getSize();

        for (int i = 0; i < size; i++) {
            rows.push_back(table.getRowAsString(i));

        }

        IOUtils::printInPageFormat(rows, context.outputConsoleWritter, context.inputConsoleReader);

    }
    catch (const std::exception& e) {
        context.outputConsoleWritter.printLine(e.what());
    }
}
