#include "CatalogInsertCommand.hpp"
#include "CommandContext.hpp" 
#include "Table.hpp"          
#include "TableColumn.hpp"    
#include "Catalog.hpp"        
#include <stdexcept>          
#include <string>             
#include <vector>             

/**
 * @brief Constructs a CatalogInsertCommand object, initializing it with the shared command context.
 *
 * @param context A reference to the `CommandContext` object. This context provides
 * access to the application's shared database catalog and console output utilities,
 * which are necessary for performing insert operations and reporting results.
 */
CatalogInsertCommand::CatalogInsertCommand(CommandContext& context)
	: context(context) {
}

/**
 * @brief Executes the 'insert' command, adding a new row to a specified table.
 *
 * This function processes the command-line arguments to obtain the target table name
 * and a list of values for the new row. It performs validation checks:
 * 1. Ensures a catalog is loaded.
 * 2. Verifies that at least the table name is provided (`params.size() >= 2`).
 * 3. Retrieves the specified table from the `context.loadedCatalog`.
 * 4. Ensures that the number of provided values exactly matches the number of columns in the table.
 *
 * The method then iterates through the table's columns and, for each column, calls its
 * `addCell` method with the corresponding value from the input parameters. This effectively
 * adds a new row to the table. A success message is printed to the console upon
 * successful insertion. Any errors (e.g., table not found, wrong number of values,
 * type conversion failures) are caught and reported to the console.
 *
 * @param params A constant reference to a vector of strings containing command-line arguments.
 * Expected elements:
 * - `params[0]`: "insert"
 * - `params[1]`: The name of the table to insert into.
 * - `params[2]` onwards: The values for the new row, one value per column, in order.
 *
 * @throws std::runtime_error If `context.loadedCatalogExists` is `false` (no catalog loaded).
 * @throws std::runtime_error If `params.size()` is less than 2 (missing table name).
 * @throws std::runtime_error If `context.loadedCatalog.returnTableByName()` fails to find the specified table.
 * @throws std::runtime_error If the number of `values` provided does not match `table.getNumberOfColumns()`.
 * @throws std::exception Any exceptions propagated from `TableColumn::addCell` (e.g.,
 * `std::invalid_argument` or `std::out_of_range` during internal string-to-numeric conversion
 * if the value format is incorrect for the column's type).
 */
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

/**
 * @brief Creates a deep copy of the current `CatalogInsertCommand` object.
 *
 * This override constructs a new `CatalogInsertCommand` instance,
 * associating it with the provided `newContext`. Since `CatalogInsertCommand`
 * itself only holds a reference to `CommandContext` and no other dynamically
 * allocated members, a simple construction with the new context is sufficient
 * for cloning this command object.
 *
 * @param newContext A reference to the `CommandContext` that the new cloned command should use.
 * @return A pointer to a newly allocated `CatalogInsertCommand` object.
 * @warning The caller is responsible for deleteing the returned pointer.
 */
Command* CatalogInsertCommand::clone(CommandContext& newContext) const {
    return new CatalogInsertCommand(newContext);
}