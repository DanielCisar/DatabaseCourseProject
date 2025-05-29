#include "CatalogDeleteRowsCommand.hpp"
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

CatalogDeleteRowsCommand::CatalogDeleteRowsCommand(CommandContext& context)
	: context(context) {
}   

void CatalogDeleteRowsCommand::execute(const std::vector<std::string>& params) {

    if (!context.loadedCatalogExists) {
        throw std::runtime_error("There is no file opened! ");
    }

    try {
		const std::string& tableName = params[1];
		int searchColumnIndex = std::stoi(params[2]);
		const std::string& searchValue = params[3];

        Table& table = context.loadedCatalog.returnTableByName(tableName);

        TableColumn* searchCol = table.getColumnAtGivenIndex(searchColumnIndex);

        int size = searchCol->getSize();
        int deletedCount = 0;

        for (int i = size - 1; i >= 0; --i) {
            if (searchCol->matchesValues(i, searchValue)) {
                table.deleteGivenRow(i);
                deletedCount++;
            }
        }

        context.outputConsoleWritter.printLine("Deleted " + std::to_string(deletedCount) + " row(s).");

    }
    catch (const std::exception& e) {
        context.outputConsoleWritter.printLine(e.what());
    }
}
