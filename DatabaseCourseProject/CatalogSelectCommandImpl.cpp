#include "CatalogSelectCommand.hpp"
#include "CommandContext.hpp"     
#include "Table.hpp"              
#include "TableColumn.hpp"        
#include "IOUtils.hpp"            
#include "Catalog.hpp"            
#include <stdexcept>              
#include <string>                 
#include <vector>                 

/**
 * @brief Constructs a CatalogSelectCommand object, initializing it with the shared command context.
 *
 * @param context A reference to the `CommandContext` object. This context provides
 * access to the application's shared database catalog and console I/O handlers,
 * which are necessary for filtering and displaying table data.
 */
CatalogSelectCommand::CatalogSelectCommand(CommandContext& context)
	: context(context) {
}

/**
 * @brief Executes the 'select' command, displaying rows matching a column condition.
 *
 * This function processes the command-line arguments to obtain the column index for
 * searching, the value to match, and the target table name. It performs validation
 * checks to ensure a catalog is loaded, parameters are correct, and the table exists.
 *
 * The method then retrieves the specified table from the `context.loadedCatalog`
 * and the column to search within. It iterates through all rows of the table.
 * For each row, it checks if the value in the `columnToSearch` matches the `value` argument.
 * If a match is found, the entire row is retrieved as a formatted string using
 * `table.getRowAsString(i)` and added to a `std::vector<std::string>`.
 *
 * Finally, the collected matching rows are passed to `IOUtils::printInPageFormat`
 * for paginated output to the console, allowing the user to browse filtered data.
 * Any errors (e.g., table not found, invalid column index) are caught and reported.
 *
 * @param params A constant reference to a vector of strings containing command-line arguments.
 * Expected elements:
 * - `params[0]`: "select"
 * - `params[1]`: The 0-indexed integer position of the column (as a string) to search.
 * - `params[2]`: The value (string) to match against cells in the search column.
 * - `params[3]`: The name of the table to select from.
 *
 * @throws std::runtime_error If `context.loadedCatalogExists` is `false` (no catalog loaded).
 * @throws std::runtime_error If `params.size()` is not 4 (incorrect number of arguments).
 * @throws std::invalid_argument If `params[1]` cannot be converted to an integer.
 * @throws std::runtime_error If `context.loadedCatalog.returnTableByName()` fails to find the specified table.
 * @throws std::out_of_range If the parsed `numberOfColumn` index is less than 0 or greater than or equal to the table's actual number of columns.
 * @throws std::exception Catches any other unexpected exceptions and reports their messages to the console.
 */
void CatalogSelectCommand::execute(const std::vector<std::string>& params) {

    if (!context.loadedCatalogExists) {
        throw std::runtime_error("There is no file opened! ");
    }
    
    if (params.size() != 4) {
        throw std::runtime_error("Not enough parameters! ");
    }

    try {
        const int numberOfColumn = std::stoi(params[1]);
        const std::string& value = params[2];
        const std::string& name = params[3];

        Table& table = context.loadedCatalog.returnTableByName(name);

        TableColumn* columnToSearch = table.getColumnAtGivenIndex(numberOfColumn);

        if (numberOfColumn < 0 || numberOfColumn >= columnToSearch->getSize()) {
            throw std::out_of_range("Invalid column index");
        }

        std::vector<std::string> rows;

        int size = columnToSearch->getSize();

        for (int i = 0; i < size; i++) {
            if (columnToSearch->matchesValues(i, value)) {
                rows.push_back(table.getRowAsString(i));

            }
        }

        IOUtils::printInPageFormat(rows, context.outputConsoleWritter, context.inputConsoleReader);
    }
    catch (const std::exception& e) {
        context.outputConsoleWritter.printLine(e.what());
    }
}

/**
 * @brief Creates a deep copy of the current `CatalogSelectCommand` object.
 *
 * This override constructs a new `CatalogSelectCommand` instance,
 * associating it with the provided `newContext`. Since `CatalogSelectCommand`
 * itself only holds a reference to `CommandContext` and no other dynamically
 * allocated members, a simple construction with the new context is sufficient
 * for cloning this command object.
 *
 * @param newContext A reference to the `CommandContext` that the new cloned command should use.
 * @return A pointer to a newly allocated `CatalogSelectCommand` object.
 * @warning The caller is responsible for deleteing the returned pointer.
 */
Command* CatalogSelectCommand::clone(CommandContext& newContext) const {
    return new CatalogSelectCommand(newContext);
}