#include "CatalogUpdateCommand.hpp"
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

CatalogUpdateCommand::CatalogUpdateCommand(CommandContext& context)
	: context(context) {
}

void CatalogUpdateCommand::execute(const std::vector<std::string>& params) {

    if (!context.loadedCatalog) {
        throw std::runtime_error("There is no file opened! ");
    }

    try {
        const std::string& tableName = params[1];
        int searchColumnIndex = std::stoi(params[2]);
        const std::string& searchValue = params[3];
        int targetColumnIndex = std::stoi(params[4]);
        const std::string& targetValue = params[5];

        Table& table = context.loadedCatalog->returnTableByName(tableName);

        TableColumn* searchCol = table.getColumnAtGivenIndex(searchColumnIndex);
        TableColumn* targetCol = table.getColumnAtGivenIndex(targetColumnIndex);

        int size = searchCol->getSize();

        for (int i = 0; i < size; ++i) {
            if (searchCol->matchesValues(i, searchValue)) {
                targetCol->changeValueAtIndex(i, targetValue);
            }
        }
        context.outputConsoleWritter.printLine("Update was successful. ");
    }
    catch (const std::exception& e) {
        context.outputConsoleWritter.printLine(e.what());
    }
}
