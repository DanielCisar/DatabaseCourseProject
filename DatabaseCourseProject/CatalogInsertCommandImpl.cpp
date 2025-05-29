#include "CatalogInsertCommand.hpp"
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

CatalogInsertCommand::CatalogInsertCommand(CommandContext& context)
	: context(context) {
}

void CatalogInsertCommand::execute(const std::vector<std::string>& params) {

    if (!context.loadedCatalogExists) {
        throw std::runtime_error("There is no file opened! ");
    }

    try {
		const std::string& tableName = params[1];
		std::vector<std::string> values(params.begin() + 2, params.end());

        Table& table = context.loadedCatalog.returnTableByName(tableName);

        if (values.size() != table.getNumberOfColumns()) {
            throw std::runtime_error("Number of values is not equal to number of column. ");
        }
        int i = 0;
        for (auto& col : table) {
            col->addCell(values[i]);
            ++i;
        }
        context.outputConsoleWritter.printLine("New row added successfuly. ");
    }
    catch (const std::exception& e) {
        context.outputConsoleWritter.printLine(e.what());
    }
}
