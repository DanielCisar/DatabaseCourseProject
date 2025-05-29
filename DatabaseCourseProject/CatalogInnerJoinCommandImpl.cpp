#include "CatalogInnerJoinCommand.hpp"
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

CatalogInnerJoinCommand::CatalogInnerJoinCommand(CommandContext& context)
	: context(context) {
}

void CatalogInnerJoinCommand::execute(const std::vector<std::string>& params) {

    if (!context.loadedCatalogExists) {
        throw std::runtime_error("There is no file opened! ");
    }

    try {
		const std::string& tableName1 = params[1];
		int column1 = std::stoi(params[2]);
		const std::string& tableName2 = params[3];
		int column2 = std::stoi(params[4]);

        Table& table1 = context.loadedCatalog.returnTableByName(tableName1);
        Table& table2 = context.loadedCatalog.returnTableByName(tableName2);

        if (column1 >= table1.getColumnAtGivenIndex(0)->getSize() ||
            column2 >= table1.getColumnAtGivenIndex(0)->getSize()) {

            throw std::runtime_error("Invalid column index. ");
        }

        TableColumn* col1 = table1.getColumnAtGivenIndex(column1);
        TableColumn* col2 = table2.getColumnAtGivenIndex(column2);

        if (col1->getType() != col2->getType()) {
            throw std::runtime_error("Incompatible column types. ");
        }

        std::vector<TableColumn*> resultCols;

        for (auto& col : table1) {
            resultCols.push_back(col->clone());
        }

        for (auto& col : table2) {
            if (col == col2) {
                continue;
            }
            resultCols.push_back(col->clone());
        }

        for (int i = 0; i < col1->getSize(); ++i) {
            for (int j = 0; j < col2->getSize(); ++j) {
                if (col1->returnValueAtGivenIndexAsString(i) == col2->returnValueAtGivenIndexAsString(j)) {
                    int m = 0;
                    for (auto& col : table1) {
                        resultCols[m]->addCell(col->returnValueAtGivenIndexAsString(i));
                        ++m;
                    }

                    for (int k = 0; k < table2.getNumberOfColumns(); ++k) {
                        if (k == column2) {
                            continue;
                        }
                        resultCols[table1.getNumberOfColumns() + k - 1]->
                            addCell(table2.getColumnAtGivenIndex(k)->
                                returnValueAtGivenIndexAsString(j));

                    }
                }
            }
        }
        std::string targetFolder = FileUtils::getDirectoryPath(table1.getFilename());
        std::string newName = "inner_join_of_" + table1.getName() + "_and_" + table2.getName();

        std::string newTablePath = targetFolder + "/" + newName + ".csv";

        Table resTable(resultCols, "Inner_join_result", newTablePath);
        context.outputFileWritter.writeTableToFile(resTable, newTablePath);
        context.outputConsoleWritter.printLine("The result of the operation was saved at: " + newTablePath);
    }
    catch (const std::exception& e) {
        context.outputConsoleWritter.printLine(e.what());
    }
}
