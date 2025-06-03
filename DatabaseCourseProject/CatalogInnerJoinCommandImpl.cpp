#include "CatalogInnerJoinCommand.hpp"
#include "CommandContext.hpp" 
#include "Table.hpp"          
#include "TableColumn.hpp"    
#include "ColumnType.hpp"     
#include "OutputFileWritter.hpp" 
#include "FileUtils.hpp"      
#include <stdexcept>          
#include <string>             
#include <vector>             

/**
 * @brief Constructs a CatalogInnerJoinCommand object, initializing it with the shared command context.
 *
 * @param context A reference to the `CommandContext` object. This context provides
 * access to the application's shared database catalog, file writing utilities,
 * and console output handlers, which are necessary for performing join operations.
 */
CatalogInnerJoinCommand::CatalogInnerJoinCommand(CommandContext& context)
	: context(context) {
}

/**
 * @brief Executes the 'innerjoin' command, creating a new table from two joined tables.
 *
 * This function processes the command-line arguments to obtain the names of two tables
 * and the 0-indexed column indices on which to perform the join. It validates that
 * a catalog is loaded, parameters are correct, and both tables exist.
 *
 * The method then retrieves the specified tables from the `context.loadedCatalog`.
 * It performs extensive validation on the column indices to ensure they are within bounds
 * for their respective tables. It also checks that the join columns have compatible data types.
 *
 * A new set of columns (`resultCols`) is initialized by cloning all columns from the first table,
 * followed by cloning all columns from the second table, explicitly *excluding* the join column
 * from the second table to prevent duplication in the result.
 *
 * The core join logic involves nested loops: for each row in the first table and each row in
 * the second table, it compares the values in their respective join columns. If the values
 * match, a new row is constructed in `resultCols` by combining the data from the matching
 * rows (all columns from the first table, and all columns from the second table *except*
 * its join column).
 *
 * Finally, a new `Table` object is created from `resultCols` with an automatically generated
 * name (e.g., "inner_join_of_table1_and_table2") and a file path. This resulting table is then
 * written to a CSV file in the same directory as the first table's source file, using
 * `OutputFileWritter::writeTableToFile`. A confirmation message, including the path to the
 * saved result table, is printed to the console. Errors at any stage are caught and reported.
 *
 * @param params A constant reference to a vector of strings containing command-line arguments.
 * Expected elements:
 * - `params[0]`: "innerjoin"
 * - `params[1]`: Name of the first table.
 * - `params[2]`: 0-indexed integer position of the join column in the first table (as a string).
 * - `params[3]`: Name of the second table.
 * - `params[4]`: 0-indexed integer position of the join column in the second table (as a string).
 *
 * @throws std::runtime_error If `context.loadedCatalogExists` is `false` (no catalog loaded).
 * @throws std::runtime_error If `params.size()` is not 5 (incorrect number of arguments).
 * @throws std::invalid_argument If `params[2]` or `params[4]` cannot be converted to an integer.
 * @throws std::runtime_error If `context.loadedCatalog.returnTableByName()` fails to find either specified table.
 * @throws std::out_of_range If `column1` is less than 0 or greater than or equal to `table1.getNumberOfColumns()`.
 * @throws std::out_of_range If `column2` is less than 0 or greater than or equal to `table2.getNumberOfColumns()`.
 * @throws std::runtime_error If the `ColumnType` of `col1` and `col2` are different.
 * @throws std::exception Catches any other exceptions propagated during table processing (e.g., memory allocation for cloning) or file writing.
 */
void CatalogInnerJoinCommand::execute(const std::vector<std::string>& params) {

    if (!context.loadedCatalogExists) {
        throw std::runtime_error("There is no file opened! ");
    }

    if (params.size() != 5) {
        throw std::runtime_error("Not enough parameters! ");
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

        std::vector<std::string> resultColNames;
        std::vector<std::string> resultColTypes;

        for (auto& col : table1) {
            resultColNames.push_back(col->getName());
            resultColTypes.push_back(col->getTypeAsString());
        }

        for (int i = 0; i < table2.getNumberOfColumns(); ++i) {
            if (i == column2) {
                continue;
            }
            resultColNames.push_back(table2.getColumnAtGivenIndex(i)->getName());
            resultColTypes.push_back(table2.getColumnAtGivenIndex(i)->getTypeAsString());
        }

        std::vector<std::vector<std::string>> resultRows;

        for (int i = 0; i < col1->getSize(); ++i) {
            for (int j = 0; j < col2->getSize(); ++j) {
                if (col1->returnValueAtGivenIndexAsString(i) == col2->returnValueAtGivenIndexAsString(j)) {
                    std::vector<std::string> row;

                    for (auto& col : table1) {
                        row.push_back(col->returnValueAtGivenIndexAsString(i));
                    }

                    for (int k = 0; k < table2.getNumberOfColumns(); ++k) {
                        if (k == column2) {
                            continue;
                        }
                        row.push_back(table2.getColumnAtGivenIndex(k)->returnValueAtGivenIndexAsString(j));
                    }

                    resultRows.push_back(row);
                }
            }
        }

        std::vector<TableColumn*> resultCols;

        for (int i = 0; i < resultColNames.size(); ++i) {
            TableColumn* newCol = ColumnFactory::makeColumn(resultColNames[i], resultColTypes[i]);
            for (const auto& row : resultRows) {
                newCol->addCell(row[i]);
            }
            resultCols.push_back(newCol);
        }

        std::string targetFolder = FileUtils::getDirectoryPath(table1.getFilename());
        std::string name = "inner_join_of_" + table1.getName() + "_and_" + table2.getName();
        std::string newName = name;
        std::string newTablePath = targetFolder + "/" + newName + ".csv";

        int counter = 1;
        while (FileUtils::fileExists(newTablePath)) {
            newName = name + "_" + std::to_string(counter++);
            newTablePath = targetFolder + "/" + newName + ".csv";
        }

        Table resTable(resultCols, "Inner_join_result", newTablePath);
        context.outputFileWritter.writeTableToFile(resTable, newTablePath);
        context.outputConsoleWritter.printLine("The result of the operation was saved at: " + newTablePath);
    }
    catch (const std::exception& e) {
        context.outputConsoleWritter.printLine(e.what());
    }
}

/**
 * @brief Creates a deep copy of the current `CatalogInnerJoinCommand` object.
 *
 * This override constructs a new `CatalogInnerJoinCommand` instance,
 * associating it with the provided `newContext`. Since `CatalogInnerJoinCommand`
 * itself only holds a reference to `CommandContext` and no other dynamically
 * allocated members, a simple construction with the new context is sufficient
 * for cloning this command object.
 *
 * @param newContext A reference to the `CommandContext` that the new cloned command should use.
 * @return A pointer to a newly allocated `CatalogInnerJoinCommand` object.
 * @warning The caller is responsible for deleteing the returned pointer.
 */
Command* CatalogInnerJoinCommand::clone(CommandContext& newContext) const {
    return new CatalogInnerJoinCommand(newContext);
}