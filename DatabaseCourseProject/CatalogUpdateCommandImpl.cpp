#include "CatalogUpdateCommand.hpp"
#include "CommandContext.hpp"     
#include "Table.hpp"              
#include "TableColumn.hpp"        
#include "Catalog.hpp"            
#include <stdexcept>              
#include <string>                 
#include <vector>                 

/**
 * @brief Constructs a CatalogUpdateCommand object, initializing it with the shared command context.
 *
 * @param context A reference to the `CommandContext` object. This context provides
 * access to the application's shared database catalog and console output utilities,
 * which are necessary for performing update operations and reporting results.
 */
CatalogUpdateCommand::CatalogUpdateCommand(CommandContext& context)
	: context(context) {
}

/**
 * @brief Executes the 'update' command, conditionally modifying table data.
 *
 * This function processes the command-line arguments to obtain the table name,
 * the search column index, the search value, the target column index, and the
 * new target value. It performs validation checks to ensure a catalog is loaded,
 * parameters are correct, and the table exists.
 *
 * The method then retrieves the specified table from the `context.loadedCatalog`,
 * along with the `searchCol` and `targetCol`. It validates that both column
 * indices are within the table's bounds.
 *
 * It iterates through all rows of the table. For each row, if the value in the
 * `searchCol` at the current row index matches the `searchValue`, then the
 * value in the `targetCol` at the same row index is updated to `targetValue`
 * using `targetCol->changeValueAtIndex()`. This method handles necessary type
 * conversions and validations for the target column. A success message is
 * printed to the console upon completion of the update operation. Any errors
 * encountered during parsing, table/column lookup, or value conversion are caught
 * and reported to the console.
 *
 * @param params A constant reference to a vector of strings containing command-line arguments.
 * Expected elements:
 * - `params[0]`: "update"
 * - `params[1]`: Name of the table to be updated.
 * - `params[2]`: 0-indexed integer position of the column to search within (as a string).
 * - `params[3]`: Value (string) to match in the search column.
 * - `params[4]`: 0-indexed integer position of the column to update (as a string).
 * - `params[5]`: New value (string) to set in the target column.
 *
 * @throws std::runtime_error If `context.loadedCatalogExists` is `false` (no catalog loaded).
 * @throws std::runtime_error If `params.size()` is not 6 (incorrect number of arguments).
 * @throws std::invalid_argument If `params[2]` or `params[4]` cannot be converted to a valid integer.
 * @throws std::runtime_error If `context.loadedCatalog.returnTableByName()` fails to find the specified table.
 * @throws std::out_of_range If `searchColumnIndex` or `targetColumnIndex` is less than 0 or greater than or equal to the table's number of columns.
 * @throws std::exception Catches any exceptions propagated from `TableColumn::changeValueAtIndex`
 * (e.g., `std::invalid_argument` if `targetValue` format is incorrect for the target column's type, or `std::out_of_range` if `i` is invalid, though the loop should prevent that).
 * Catches any other unexpected exceptions and reports their messages to the console.
 */
void CatalogUpdateCommand::execute(const std::vector<std::string>& params) {

    if (!context.loadedCatalogExists) {
        throw std::runtime_error("There is no file opened! ");
    }

    if (params.size() != 6) {
        throw std::runtime_error("Not enough parameters! ");
    }

    try {
        const std::string& tableName = params[1];
        int searchColumnIndex = std::stoi(params[2]);
        const std::string& searchValue = params[3];
        int targetColumnIndex = std::stoi(params[4]);
        const std::string& targetValue = params[5];

        Table& table = context.loadedCatalog.returnTableByName(tableName);

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

/**
 * @brief Creates a deep copy of the current `CatalogUpdateCommand` object.
 *
 * This override constructs a new `CatalogUpdateCommand` instance,
 * associating it with the provided `newContext`. Since `CatalogUpdateCommand`
 * itself only holds a reference to `CommandContext` and no other dynamically
 * allocated members, a simple construction with the new context is sufficient
 * for cloning this command object.
 *
 * @param newContext A reference to the `CommandContext` that the new cloned command should use.
 * @return A pointer to a newly allocated `CatalogUpdateCommand` object.
 * @warning The caller is responsible for deleteing the returned pointer.
 */
Command* CatalogUpdateCommand::clone(CommandContext& newContext) const {
    return new CatalogUpdateCommand(newContext);
}