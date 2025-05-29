#include "CatalogSelectCommand.hpp"
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

CatalogSelectCommand::CatalogSelectCommand(CommandContext& context)
	: context(context) {
}

void CatalogSelectCommand::execute(const std::vector<std::string>& params) {

    if (!context.loadedCatalog) {
        throw std::runtime_error("There is no file opened! ");
    }
    
    try {
        const int numberOfColumn = std::stoi(params[1]);
        const std::string& value = params[2];
        const std::string& name = params[3];

        Table table = context.loadedCatalog->returnTableByName(name);

        TableColumn* columnToSearch = table.getColumnAtGivenIndex(numberOfColumn);

        if (numberOfColumn < 0 || numberOfColumn >= columnToSearch->getSize()) {
            throw std::out_of_range("Invalid column index");
        }

        std::vector<std::string> rows;

        int size = columnToSearch->getSize();

        for (int i = 0; i < size; i++) {
            if (columnToSearch->matchesValues(i, value)) {
                rows.push_back(table.getRowAsString(i));

            }
        }

        IOUtils::printInPageFormat(rows, context.outputConsoleWritter, context.inputConsoleReader);
    }
    catch (const std::exception& e) {
        context.outputConsoleWritter.printLine(e.what());
    }
}
