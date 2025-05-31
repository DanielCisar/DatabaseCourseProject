#include "CatalogAggregateCommand.hpp"
#include "CommandContext.hpp" 
#include "Table.hpp"          
#include "TableColumn.hpp"   
#include "ColumnType.hpp"    
#include "Operations.hpp"    
#include <stdexcept>        
#include <string>            
#include <vector>            


/**
 * @brief Constructs a CatalogAggregateCommand object, initializing it with the shared command context.
 *
 * @param context A reference to the `CommandContext` object. This context provides
 * access to the application's shared database catalog and console output utilities,
 * which are necessary for performing aggregation operations and reporting results.
 */
CatalogAggregateCommand::CatalogAggregateCommand(CommandContext& context)
    : context(context) {
}

/**
 * @brief Executes the aggregate command, performing a calculation on filtered numeric data.
 *
 * This function parses the command-line arguments to extract the table name,
 * search column index, search value, target column index, and the desired
 * aggregation operation. It then performs the following steps:
 * 1. Validates that a catalog is loaded and that the correct number of parameters (6) is provided.
 * 2. Retrieves the target `Table` from the `context.loadedCatalog`.
 * 3. Validates that both search and target column indices are within valid bounds.
 * 4. Ensures the target column is of a numeric type (Integer or Double) suitable for aggregation.
 * 5. Iterates through the table's rows: if a row matches the `searchValue` in the `searchColumn`,
 * it attempts to convert the value from the `targetColumn` to a `double` and adds it to a
 * temporary collection of cells. Non-numeric values in the target column will cause an error.
 * 6. If no rows match the search condition, an error is thrown.
 * 7. Performs the specified aggregation operation ("sum", "product", "minimum", "maximum")
 * using the collected numeric values.
 * 8. Prints the final calculated aggregate result to the console.
 * Errors during any of these steps are caught and reported to the console.
 *
 * @param params A constant reference to a vector of strings containing command-line arguments.
 * Expected elements:
 * - `params[0]`: "aggregate"
 * - `params[1]`: Table name.
 * - `params[2]`: Search column index (as a string, converted to int).
 * - `params[3]`: Search value (string).
 * - `params[4]`: Target column index (as a string, converted to int).
 * - `params[5]`: Operation name ("sum", "product", "minimum", "maximum").
 *
 * @throws std::runtime_error If `context.loadedCatalogExists` is `false`.
 * @throws std::runtime_error If `params.size()` is not 6.
 * @throws std::runtime_error If `context.loadedCatalog.returnTableByName()` fails (table not found).
 * @throws std::out_of_range If `params[2]` or `params[4]` cannot be converted to an integer, or if the resulting
 * `searchColumn` or `targetColumn` index is out of bounds for the table.
 * @throws std::runtime_error If the `targetColumn` is not `ColumnType::INTEGER` or `ColumnType::DOUBLE`.
 * @throws std::runtime_error If `std::stod` fails to convert a value from the `targetColumn` to a double,
 * indicating non-numeric data where numeric was expected.
 * @throws std::runtime_error If no rows are found that match the `seacrhValue` in the `searchColumn`.
 * @throws std::invalid_argument If `params[5]` (operation name) is not one of the recognized operations.
 * @throws std::exception Catches any other unexpected exceptions and reports their messages.
 */
void CatalogAggregateCommand::execute(const std::vector<std::string>& params) {
    if (!context.loadedCatalogExists) {
        throw std::runtime_error("There is no file opened! ");
    }

    if (params.size() != 6) {
        throw std::runtime_error("Not enough parameters! ");
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

        if (cells.empty()) {
            throw std::runtime_error("No matching rows found.");
        }

        double result;
        if (operation == "sum") {
            result = Operations::sum(cells);
        }
        else if (operation == "product") {
            result = Operations::product(cells);
        }
        else if (operation == "maximum") {
            result = Operations::max(cells);
        }
        else if (operation == "minimum") {
            result = Operations::min(cells);
        }
        else {
            throw std::invalid_argument("Unknown aggregate operation: " + operation);
        }

        context.outputConsoleWritter.printLine(std::to_string(result));
    }
    catch (const std::exception& e) {
        context.outputConsoleWritter.printLine(e.what());
    }
}

/**
 * @brief Creates a deep copy of the current `CatalogAggregateCommand` object.
 *
 * This override constructs a new `CatalogAggregateCommand` instance,
 * associating it with the provided `newContext`. Since `CatalogAggregateCommand`
 * itself only holds a reference to `CommandContext` and no other dynamically
 * allocated members, a simple construction with the new context is sufficient
 * for cloning this command object.
 *
 * @param newContext A reference to the `CommandContext` that the new cloned command should use.
 * @return A pointer to a newly allocated `CatalogAggregateCommand` object.
 * @warning The caller is responsible for deleteing the returned pointer.
 */
Command* CatalogAggregateCommand::clone(CommandContext& newContext) const {
    return new CatalogAggregateCommand(newContext);
}