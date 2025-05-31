#include "CatalogCountCommand.hpp"
#include "CommandContext.hpp" 
#include "Table.hpp"          
#include "TableColumn.hpp"    
#include <stdexcept>          
#include <string>             
#include <vector>      

/**
 * @brief Constructs a CatalogCountCommand object, initializing it with the shared command context.
 *
 * @param context A reference to the `CommandContext` object. This context provides
 * access to the application's shared database catalog and console output utilities,
 * which are necessary for performing count operations and reporting results.
 */
CatalogCountCommand::CatalogCountCommand(CommandContext& context)
    : context(context) {
}

/**
 * @brief Executes the 'count' command, tallying rows based on a column condition.
 *
 * This function processes the command-line arguments to determine the target table,
 * the column to search within, and the value to match. It performs validation checks
 * to ensure a catalog is loaded, parameters are correct, and the table exists.
 *
 * The method then retrieves the specified table and column. It iterates through
 * the cells of the `searchColumnIndex`. For each cell, it checks if the value
 * matches the `searchValue`. A counter is incremented for every match found.
 * Finally, the total count of matching rows is printed to the console in a user-friendly format.
 *
 * @param params A constant reference to a vector of strings containing command-line arguments.
 * Expected elements:
 * - `params[0]`: "count"
 * - `params[1]`: Name of the table to search.
 * - `params[2]`: Index of the column (as a string, converted to int) to apply the search condition.
 * - `params[3]`: The value (string) to match against cells in the search column.
 *
 * @throws std::runtime_error If `context.loadedCatalogExists` is `false` (no catalog loaded).
 * @throws std::runtime_error If `params.size()` is not 4 (incorrect number of arguments).
 * @throws std::runtime_error If `context.loadedCatalog.returnTableByName()` fails (table not found).
 * @throws std::out_of_range If `params[2]` cannot be converted to an integer, or if the resulting
 * `searchColumnIndex` is out of bounds for the table.
 * @throws std::exception Catches any other unexpected exceptions and reports their messages to the console.
 */
void CatalogCountCommand::execute(const std::vector<std::string>& params) {

    if (!context.loadedCatalogExists) {
        throw std::runtime_error("There is no file opened!");
    }

    if (params.size() != 4) {
        throw std::runtime_error("Not enough parameters! ");
    }

    try {
        const std::string& tableName = params[1];
        int searchColumnIndex = std::stoi(params[2]);
        const std::string& searchValue = params[3];

        Table& table = context.loadedCatalog.returnTableByName(tableName);

        int counter = 0;

        TableColumn* searchCol = table.getColumnAtGivenIndex(searchColumnIndex);
        int size = searchCol->getSize();

        for (int i = 0; i < size; i++) {
            if (searchCol->matchesValues(i, searchValue)) {
                counter++;
            }
        }

        context.outputConsoleWritter.printLine("Column number " + std::to_string(searchColumnIndex)
            + " of table " + tableName + " contains " + searchValue + " " + std::to_string(counter)
            + " time/times.");
    }
    catch (const std::exception& e) {
        context.outputConsoleWritter.printLine(e.what());
    }
}

/**
 * @brief Creates a deep copy of the current `CatalogCountCommand` object.
 *
 * This override constructs a new `CatalogCountCommand` instance,
 * associating it with the provided `newContext`. Since `CatalogCountCommand`
 * itself only holds a reference to `CommandContext` and no other dynamically
 * allocated members, a simple construction with the new context is sufficient
 * for cloning this command object.
 *
 * @param newContext A reference to the `CommandContext` that the new cloned command should use.
 * @return A pointer to a newly allocated `CatalogCountCommand` object.
 * @warning The caller is responsible for deleteing the returned pointer.
 */
Command* CatalogCountCommand::clone(CommandContext& newContext) const {
    return new CatalogCountCommand(newContext);
}