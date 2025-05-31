#include "CatalogDeleteRowsCommand.hpp"
#include "CommandContext.hpp" 
#include "Table.hpp"          
#include "TableColumn.hpp"    
#include <stdexcept>          
#include <string>             
#include <vector>             

/**
 * @brief Constructs a CatalogDeleteRowsCommand object, initializing it with the shared command context.
 *
 * @param context A reference to the `CommandContext` object. This context provides
 * access to the application's shared database catalog and console output utilities,
 * which are necessary for performing row deletion operations and reporting results.
 */
CatalogDeleteRowsCommand::CatalogDeleteRowsCommand(CommandContext& context)
	: context(context) {
}   

/**
 * @brief Executes the 'delete' command, removing rows from a table based on a condition.
 *
 * This function processes the command-line arguments to identify the target table,
 * the column to search within, and the value to match. It performs validation checks
 * to ensure a catalog is loaded, parameters are correct, and the table exists.
 *
 * The method then retrieves the specified table and column. It iterates through
 * the rows of the table in reverse order (from last to first) to safely delete
 * rows without affecting subsequent iteration indices. For each row, it checks
 * if the value in the `searchColumnIndex` matches the `searchValue`. If a match
 * is found, the entire row is deleted from the table, and a counter is incremented.
 * Finally, the total count of deleted rows is printed to the console.
 *
 * @param params A constant reference to a vector of strings containing command-line arguments.
 * Expected elements:
 * - `params[0]`: "delete"
 * - `params[1]`: Name of the table from which rows will be deleted.
 * - `params[2]`: Index of the column (as a string, converted to int) to apply the search condition.
 * - `params[3]`: The value (string) to match against cells in the search column.
 *
 * @throws std::runtime_error If `context.loadedCatalogExists` is `false` (no catalog loaded).
 * @throws std::runtime_error If `params.size()` is not 4 (incorrect number of arguments).
 * @throws std::runtime_error If `context.loadedCatalog.returnTableByName()` fails (table not found).
 * @throws std::out_of_range If `params[2]` cannot be converted to an integer, or if the
 * resulting `searchColumnIndex` is out of bounds for the table.
 * @throws std::exception Catches any other unexpected exceptions and reports their messages to the console.
 */
void CatalogDeleteRowsCommand::execute(const std::vector<std::string>& params) {

    if (!context.loadedCatalogExists) {
        throw std::runtime_error("There is no file opened! ");
    }

    if (params.size() != 4) {
        throw std::runtime_error("Not enough parameters! ");
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

/**
 * @brief Creates a deep copy of the current `CatalogDeleteRowsCommand` object.
 *
 * This override constructs a new `CatalogDeleteRowsCommand` instance,
 * associating it with the provided `newContext`. Since `CatalogDeleteRowsCommand`
 * itself only holds a reference to `CommandContext` and no other dynamically
 * allocated members, a simple construction with the new context is sufficient
 * for cloning this command object.
 *
 * @param newContext A reference to the `CommandContext` that the new cloned command should use.
 * @return A pointer to a newly allocated `CatalogDeleteRowsCommand` object.
 * @warning The caller is responsible for deleteing the returned pointer.
 */
Command* CatalogDeleteRowsCommand::clone(CommandContext& newContext) const {
    return new CatalogDeleteRowsCommand(newContext);
}