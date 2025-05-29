#include "CatalogCountCommand.hpp"
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

CatalogCountCommand::CatalogCountCommand(CommandContext& context)
	: context(context) {
}

void CatalogCountCommand::execute(const std::vector<std::string>& params) {

    if (!context.loadedCatalogExists) {
        throw std::runtime_error("There is no file opened! ");
    }

    try {
		const std::string& tableName = params[1];
		int searchColumnIndex = std::stoi(params[2]);
		const std::string& searchValue = params[3];

        Table& table = context.loadedCatalog.returnTableByName(tableName);

        int counter = 0;

        TableColumn* searchCol = table.getColumnAtGivenIndex(searchColumnIndex);
        int size = searchCol->getSize();

        for (int i = 0; i < size; i++) {
            if (searchCol->matchesValues(i, searchValue)) {
                counter++;
            }
        }

        context.outputConsoleWritter.printLine("Column number " + std::to_string(searchColumnIndex)
            + " of table " + tableName + " contains " + searchValue + " " + std::to_string(counter)
            + " time/times. ");
    }
    catch (const std::exception& e) {
        context.outputConsoleWritter.printLine(e.what());
    }
}
