#include "CatalogShowTablesCommand.hpp"
#include "CommandContext.hpp" 
#include "Catalog.hpp"        
#include "Table.hpp"          
#include <stdexcept>          
#include <string>             

/**
 * @brief Constructs a CatalogShowTablesCommand object, initializing it with the shared command context.
 *
 * @param context A reference to the `CommandContext` object. This context provides
 * access to the application's shared database catalog and console output utilities,
 * which are necessary for querying and displaying the list of tables.
 */
CatalogShowTablesCommand::CatalogShowTablesCommand(CommandContext& context)
	: context(context) {
}

/**
 * @brief Executes the 'showtables' command, displaying names of all loaded tables.
 *
 * This function performs validation checks to ensure a catalog is loaded and
 * that no unexpected parameters are provided (only the command name itself).
 *
 * It then prints a header "List of tables:" to the console. Following the header,
 * the method iterates through each `Table` object present in the `context.loadedCatalog`
 * and prints the `name` of each table on a new line. This provides an overview
 * of all tables currently active in the application's memory. Any errors (e.g.,
 * no catalog loaded) are caught and reported to the console.
 *
 * @param params A constant reference to a vector of strings containing command-line arguments.
 * Expected elements:
 * - `params[0]`: "showtables"
 * This command does not process any additional parameters.
 *
 * @throws std::runtime_error If `context.loadedCatalogExists` is `false` (no catalog loaded).
 * @throws std::runtime_error If `params.size()` is not equal to 1, indicating unexpected arguments.
 * @throws std::exception Catches any other unexpected exceptions and reports their messages to the console.
 */
void CatalogShowTablesCommand::execute(const std::vector<std::string>& params) {

    if (!context.loadedCatalogExists) {
        throw std::runtime_error("There is no file opened! ");
    }

    if (params.size() != 1) {
        throw std::runtime_error("Not enough parameters! ");
    }

    context.outputConsoleWritter.printLine("List of tables: ");

    for (auto& table : context.loadedCatalog) {
        context.outputConsoleWritter.printLine(table.getName());
    }
}

/**
 * @brief Creates a deep copy of the current `CatalogShowTablesCommand` object.
 *
 * This override constructs a new `CatalogShowTablesCommand` instance,
 * associating it with the provided `newContext`. Since `CatalogShowTablesCommand`
 * itself only holds a reference to `CommandContext` and no other dynamically
 * allocated members, a simple construction with the new context is sufficient
 * for cloning this command object.
 *
 * @param newContext A reference to the `CommandContext` that the new cloned command should use.
 * @return A pointer to a newly allocated `CatalogShowTablesCommand` object.
 * @warning The caller is responsible for deleteing the returned pointer.
 */
Command* CatalogShowTablesCommand::clone(CommandContext& newContext) const {
    return new CatalogShowTablesCommand(newContext);
}