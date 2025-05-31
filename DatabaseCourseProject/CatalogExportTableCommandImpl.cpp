#include "CatalogExportTableCommand.hpp"
#include "CommandContext.hpp" 
#include "Table.hpp"          
#include "OutputFileWritter.hpp" 
#include <stdexcept>          
#include <string>             

/**
 * @brief Constructs a CatalogExportTableCommand object, initializing it with the shared command context.
 *
 * @param context A reference to the `CommandContext` object. This context provides
 * access to the application's shared database catalog, file writing utilities,
 * and console output handlers, which are necessary for performing export operations.
 */
CatalogExportTableCommand::CatalogExportTableCommand(CommandContext& context)
	: context(context) {
}

/**
 * @brief Executes the 'export' command, saving a table to a specified CSV file.
 *
 * This function processes the command-line arguments to identify the target table
 * name and the desired output file path. It performs validation checks to ensure
 * a catalog is loaded and the correct number of parameters (3) is provided.
 *
 * The method then retrieves the specified table from the `context.loadedCatalog`.
 * If the table is found, its entire content (including header and data rows) is
 * written to the designated `filepath` using `OutputFileWritter::writeTableToFile`.
 * A confirmation message indicating the successful export and target file path
 * is printed to the console. Any errors encountered during the process are caught
 * and reported to the console.
 *
 * @param params A constant reference to a vector of strings containing command-line arguments.
 * Expected elements:
 * - `params[0]`: "export"
 * - `params[1]`: The name of the table to export.
 * - `params[2]`: The file path (as a string) where the table data should be saved.
 *
 * @throws std::runtime_error If `context.loadedCatalogExists` is `false` (no catalog loaded).
 * @throws std::runtime_error If `params.size()` is not 3 (incorrect number of arguments).
 * @throws std::runtime_error If `context.loadedCatalog.returnTableByName()` fails to find the specified table.
 * @throws std::exception Catches any exceptions propagated from `OutputFileWritter::writeTableToFile`
 * (e.g., file system errors like invalid path, permissions, or disk full) and reports them to the console.
 */
void CatalogExportTableCommand::execute(const std::vector<std::string>& params) {

	if (!context.loadedCatalogExists) {
		throw std::runtime_error("There is no file opened! ");
	}

	if (params.size() != 3) {
		throw std::runtime_error("Not enough parameters! ");
	}

	const std::string& name = params[1];
	const std::string& filepath = params[2];

    Table& table = context.loadedCatalog.returnTableByName(name);

    context.outputFileWritter.writeTableToFile(table, filepath);
    context.outputConsoleWritter.printLine("Table exported to: " + filepath);
}

/**
 * @brief Creates a deep copy of the current `CatalogExportTableCommand` object.
 *
 * This override constructs a new `CatalogExportTableCommand` instance,
 * associating it with the provided `newContext`. Since `CatalogExportTableCommand`
 * itself only holds a reference to `CommandContext` and no other dynamically
 * allocated members, a simple construction with the new context is sufficient
 * for cloning this command object.
 *
 * @param newContext A reference to the `CommandContext` that the new cloned command should use.
 * @return A pointer to a newly allocated `CatalogExportTableCommand` object.
 * @warning The caller is responsible for deleteing the returned pointer.
 */
Command* CatalogExportTableCommand::clone(CommandContext& newContext) const {
	return new CatalogExportTableCommand(newContext);
}