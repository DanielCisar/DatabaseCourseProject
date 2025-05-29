#include "CatalogAddColumnCommand.hpp"
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

CatalogAddColumnCommand::CatalogAddColumnCommand(CommandContext& context)
	: context(context) {
}

void CatalogAddColumnCommand::execute(const std::vector<std::string>& params) {

    if (!context.loadedCatalogExists) {
        throw std::runtime_error("There is no file opened! ");
    }

    try {
        const std::string& tableName = params[1];
        const std::string& columnName = params[2];

        const std::string& columnTypeStr = params[3];

        ColumnType columnType;

        if (columnTypeStr == "String") {
            columnType = ColumnType::STRING;
        }
        else if (columnTypeStr == "Integer") {
            columnType = ColumnType::INTEGER;
        }
        else if (columnTypeStr == "Double") {
            columnType = ColumnType::DOUBLE;
        }
        else {
            throw std::runtime_error("Invalid column type! Use 'String', 'Integer' or 'Double'. ");
        }

        Table& table = context.loadedCatalog.returnTableByName(tableName);

        int colSize = table.getColumnAtGivenIndex(0)->getSize();

        if (columnType == ColumnType::STRING) {

			StringColumn* stringColumn = ColumnFactory::makeStringColumn(columnName);
            stringColumn->fillColumnWithNULL(colSize);

            table.addColumn(stringColumn);
        }
        else if (columnType == ColumnType::INTEGER) {
            IntegerColumn* integerColumn = ColumnFactory::makeIntegerColumn(columnName);
            integerColumn->fillColumnWithNULL(colSize);

            table.addColumn(integerColumn);
        }
        else {
            DoubleColumn* doubleColumn = ColumnFactory::makeDoubleColumn(columnName);
            doubleColumn->fillColumnWithNULL(colSize);

            table.addColumn(doubleColumn);
        }

        context.outputConsoleWritter.printLine("New empty column created and added successfuly. ");
    }
    catch (const std::exception& e) {
        context.outputConsoleWritter.printLine(e.what());
    }
}
