#include "CatalogPrintCommand.hpp"
#include "CommandContext.hpp"     
#include "Table.hpp"              
#include "TableColumn.hpp"        
#include "IOUtils.hpp"            
#include "Catalog.hpp"            
#include <stdexcept>              
#include <string>                 
#include <vector>                 

/**
 * @brief Constructs a CatalogPrintCommand object, initializing it with the shared command context.
 *
 * @param context A reference to the `CommandContext` object. This context provides
 * access to the application's shared database catalog and console I/O handlers,
 * which are necessary for retrieving and displaying table data.
 */
CatalogPrintCommand::CatalogPrintCommand(CommandContext& context)
	: context(context) {
}

/**
 * @brief Executes the 'print' command, displaying the content of a table with pagination.
 *
 * This function processes the command-line arguments to obtain the target table name.
 * It performs validation checks to ensure a catalog is loaded and the correct number
 * of parameters (2) is provided.
 *
 * The method then retrieves the specified table from the `context.loadedCatalog`.
 * It first prints the table's name. Following that, it iterates through the table's
 * columns to print all column names on one line, and then all column types on the next line,
 * serving as a header for the data.
 *
 * All rows of the table are then retrieved as formatted strings using `table.getRowAsString(i)`.
 * These rows are collected into a `std::vector<std::string>`. Finally, `IOUtils::printInPageFormat`
 * is used to output these rows to the console with pagination, allowing the user to
 * navigate through large result sets. Any errors (e.g., table not found) are caught
 * and reported to the console.
 *
 * @param params A constant reference to a vector of strings containing command-line arguments.
 * Expected elements:
 * - `params[0]`: "print"
 * - `params[1]`: The name of the table whose content is to be displayed.
 *
 * @throws std::runtime_error If `context.loadedCatalogExists` is `false` (no catalog loaded).
 * @throws std::runtime_error If `params.size()` is not 2 (incorrect number of arguments).
 * @throws std::runtime_error If `context.loadedCatalog.returnTableByName()` fails to find the specified table.
 * @throws std::exception Catches any other unexpected exceptions propagated during table data access or I/O.
 */
void CatalogPrintCommand::execute(const std::vector<std::string>& params) {

    if (!context.loadedCatalogExists) {
        throw std::runtime_error("There is no file opened! ");
    }

    if (params.size() != 2) {
        throw std::runtime_error("Not enough parameters! ");
    }

	const std::string& name = params[1];

    try {
        Table& table = context.loadedCatalog.returnTableByName(name);

        std::string command;

        context.outputConsoleWritter.printLine("Table: " + name);

        for (auto& col : table) {
            context.outputConsoleWritter.print(col->getName() + " ");
        }
        context.outputConsoleWritter.printLine("");
        for (auto& col : table) {
            context.outputConsoleWritter.print(col->getTypeAsString() + " ");
        }
        context.outputConsoleWritter.printLine("");
        std::vector<std::string> rows;

        int size = table.getColumnAtGivenIndex(0)->getSize();

        for (int i = 0; i < size; i++) {
            rows.push_back(table.getRowAsString(i));

        }

        IOUtils::printInPageFormat(rows, context.outputConsoleWritter, context.inputConsoleReader);

    }
    catch (const std::exception& e) {
        context.outputConsoleWritter.printLine(e.what());
    }
}

/**
 * @brief Creates a deep copy of the current `CatalogPrintCommand` object.
 *
 * This override constructs a new `CatalogPrintCommand` instance,
 * associating it with the provided `newContext`. Since `CatalogPrintCommand`
 * itself only holds a reference to `CommandContext` and no other dynamically
 * allocated members, a simple construction with the new context is sufficient
 * for cloning this command object.
 *
 * @param newContext A reference to the `CommandContext` that the new cloned command should use.
 * @return A pointer to a newly allocated `CatalogPrintCommand` object.
 * @warning The caller is responsible for deleteing the returned pointer.
 */
Command* CatalogPrintCommand::clone(CommandContext& newContext) const {
    return new CatalogPrintCommand(newContext);
}