#include "CatalogAggregateCommand.hpp"
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
#include "Operations.hpp"

CatalogAggregateCommand::CatalogAggregateCommand(CommandContext& context)
	: context(context) {
}

void CatalogAggregateCommand::execute(const std::vector<std::string>& params) {

    if (!context.loadedCatalogExists) {
        throw std::runtime_error("There is no file opened! ");
    }

    try {
		const std::string& tableName = params[1];
        int searchColumn = std::stoi(params[2]);
        const std::string& seacrhValue = params[3];
        int targetColumn = std::stoi(params[4]);
		const std::string& operation = params[5];

        Table& table = context.loadedCatalog.returnTableByName(tableName);
        if (searchColumn >= table.getNumberOfColumns() || searchColumn < 0) {
            throw std::out_of_range("Invalid search column index. ");
        }

        if (targetColumn >= table.getNumberOfColumns() || targetColumn < 0) {
            throw std::out_of_range("Invalid target column index. ");
        }

        TableColumn* col1 = table.getColumnAtGivenIndex(searchColumn);
        TableColumn* col2 = table.getColumnAtGivenIndex(targetColumn);

        if (col2->getType() != ColumnType::INTEGER && col2->getType() != ColumnType::DOUBLE) {
            throw std::runtime_error("Incompatible column types. ");
        }

        std::vector<double> cells;

        for (int i = 0; i < table.getColumnAtGivenIndex(0)->getSize(); i++) {
            if (col1->matchesValues(i, seacrhValue)) {
                std::string valStr = col2->returnValueAtGivenIndexAsString(i);
                try {
                    double val = std::stod(valStr);
                    cells.push_back(val);
                }
                catch (...) {
                    throw std::runtime_error("Non-numeric value found in aggregation target column.");
                }

            }
        }

        if (cells.size() == 0) {
            throw std::runtime_error("No matching rows found.");

        }
        if (operation == "sum") {
            double val = Operations::sum(cells);

            context.outputConsoleWritter.printLine(std::to_string(val));
        }
        else if (operation == "product") {
            double val = Operations::product(cells);

            context.outputConsoleWritter.printLine(std::to_string(val));
        }
        else if (operation == "maximum") {

            double val = Operations::max(cells);

            context.outputConsoleWritter.printLine(std::to_string(val));
        }
        else if (operation == "minimum") {
            double val = Operations::min(cells);

            context.outputConsoleWritter.printLine(std::to_string(val));
        }
        else {
            throw std::invalid_argument("Unknown aggregate operation: " + operation);
        }

    }
    catch (const std::exception& e) {
        context.outputConsoleWritter.printLine(e.what());
    }
}
