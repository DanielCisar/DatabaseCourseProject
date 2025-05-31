#include "CatalogDescribeCommand.hpp"
#include "CommandContext.hpp" 
#include "Table.hpp"          
#include "TableColumn.hpp"    
#include <stdexcept>          
#include <string>

/**
 * @brief Constructs a CatalogDescribeCommand object, initializing it with the shared command context.
 *
 * @param context A reference to the `CommandContext` object. This context provides
 * access to the application's shared database catalog and console output utilities,
 * which are necessary for querying table schemas and displaying information.
 */
CatalogDescribeCommand::CatalogDescribeCommand(CommandContext& context)
	: context(context) {
}

/**
 * @brief Executes the 'describe' command, displaying the column types of a table.
 *
 * This function processes the command-line arguments to identify the target table.
 * It performs validation checks to ensure a catalog is loaded and parameters are correct.
 *
 * The method then retrieves the specified table from the `context.loadedCatalog`.
 * It iterates through each `TableColumn` within the table and prints its data type
 * to the console. The columns are displayed with a 1-based index for user-friendliness,
 * rather than their internal 0-based index.
 * Any exceptions (e.g., table not found) are caught and their messages are printed to the console.
 *
 * @param params A constant reference to a vector of strings containing command-line arguments.
 * Expected elements:
 * - `params[0]`: "describe"
 * - `params[1]`: The name of the table to describe.
 *
 * @throws std::runtime_error If `context.loadedCatalogExists` is `false` (no catalog loaded).
 * @throws std::runtime_error If `params.size()` is not 2 (incorrect number of arguments).
 * @throws std::runtime_error If `context.loadedCatalog.returnTableByName()` fails to find the specified table.
 * @throws std::exception Catches any other unexpected exceptions and reports their messages to the console.
 */
void CatalogDescribeCommand::execute(const std::vector<std::string>& params) {

    if (!context.loadedCatalogExists) {
        throw std::runtime_error("There is no file opened! ");
    }

    if (params.size() != 2) {
        throw std::runtime_error("Not enough parameters! ");
    }

	const std::string& name = params[1];

    try {
        Table& table = context.loadedCatalog.returnTableByName(name);

        int index = 1;

        for (auto& col : table) {
            context.outputConsoleWritter.printLine(
                "Type of column " + std::to_string(index) + ": " + col->getTypeAsString()
            );
            index++;
        }
    }
    catch (const std::exception& e) {
        context.outputConsoleWritter.printLine(e.what());
    }
}

/**
 * @brief Creates a deep copy of the current `CatalogDescribeCommand` object.
 *
 * This override constructs a new `CatalogDescribeCommand` instance,
 * associating it with the provided `newContext`. Since `CatalogDescribeCommand`
 * itself only holds a reference to `CommandContext` and no other dynamically
 * allocated members, a simple construction with the new context is sufficient
 * for cloning this command object.
 *
 * @param newContext A reference to the `CommandContext` that the new cloned command should use.
 * @return A pointer to a newly allocated `CatalogDescribeCommand` object.
 * @warning The caller is responsible for deleteing the returned pointer.
 */
Command* CatalogDescribeCommand::clone(CommandContext& newContext) const {
    return new CatalogDescribeCommand(newContext);
}