#include "CatalogRenameCommand.hpp"
#include "CommandContext.hpp" 
#include "Table.hpp"          
#include "Catalog.hpp"        
#include <stdexcept>          
#include <string>             

/**
 * @brief Constructs a CatalogRenameCommand object, initializing it with the shared command context.
 *
 * @param context A reference to the `CommandContext` object. This context provides
 * access to the application's shared database catalog and console output utilities,
 * which are necessary for performing table renaming operations and reporting results.
 */
CatalogRenameCommand::CatalogRenameCommand(CommandContext& context)
	: context(context) {
}

/**
 * @brief Executes the 'rename' command, changing the name of a table in the catalog.
 *
 * This function processes the command-line arguments to obtain the current (old)
 * name of the table and its desired new name. It performs validation checks to ensure
 * a catalog is loaded and the correct number of parameters (3) is provided.
 *
 * The method then retrieves the specified table from the `context.loadedCatalog`
 * using its `oldName`. If the table is found, its `setName` method is called
 * to update its internal name property. A confirmation message is printed to the
 * console upon successful renaming. Any errors (e.g., table not found) are caught
 * and reported.
 *
 * @param params A constant reference to a vector of strings containing command-line arguments.
 * Expected elements:
 * - `params[0]`: "rename"
 * - `params[1]`: The current name of the table to rename.
 * - `params[2]`: The new name for the table.
 *
 * @throws std::runtime_error If `context.loadedCatalogExists` is `false` (no catalog loaded).
 * @throws std::runtime_error If `params.size()` is not 3 (incorrect number of arguments).
 * @throws std::runtime_error If `context.loadedCatalog.returnTableByName()` fails to find the specified table.
 * @throws std::exception Catches any other unexpected exceptions propagated from underlying operations.
 */
void CatalogRenameCommand::execute(const std::vector<std::string>& params) {

    if (!context.loadedCatalogExists) {
        throw std::runtime_error("There is no file opened! ");
    }

    if (params.size() != 3) {
        throw std::runtime_error("Not enough parameters! ");
    }

    try {
		const std::string& oldName = params[1];
		const std::string& newName = params[2];

        Table& table = context.loadedCatalog.returnTableByName(oldName);
        table.setName(newName);
        context.outputConsoleWritter.printLine("Table " + oldName + " has been renamed to " + newName);
    }
    catch (const std::exception& e) {
        context.outputConsoleWritter.printLine(e.what());
    }
}

/**
 * @brief Creates a deep copy of the current `CatalogRenameCommand` object.
 *
 * This override constructs a new `CatalogRenameCommand` instance,
 * associating it with the provided `newContext`. Since `CatalogRenameCommand`
 * itself only holds a reference to `CommandContext` and no other dynamically
 * allocated members, a simple construction with the new context is sufficient
 * for cloning this command object.
 *
 * @param newContext A reference to the `CommandContext` that the new cloned command should use.
 * @return A pointer to a newly allocated `CatalogRenameCommand` object.
 * @warning The caller is responsible for deleteing the returned pointer.
 */
Command* CatalogRenameCommand::clone(CommandContext& newContext) const {
    return new CatalogRenameCommand(newContext);
}