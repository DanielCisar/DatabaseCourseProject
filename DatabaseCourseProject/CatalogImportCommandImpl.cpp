#include "CatalogImportCommand.hpp"
#include "CommandContext.hpp" 
#include "Table.hpp"          
#include "InputFileReader.hpp" 
#include "Catalog.hpp"        
#include <stdexcept>          
#include <string>             

/**
 * @brief Constructs a CatalogImportCommand object, initializing it with the shared command context.
 *
 * @param context A reference to the `CommandContext` object. This context provides
 * access to the application's shared database catalog, file reading utilities,
 * and console output handlers, which are necessary for importing tables.
 */
CatalogImportCommand::CatalogImportCommand(CommandContext& context)
	: context(context) {
}

/**
 * @brief Executes the 'import' command, loading a table from a specified file into the catalog.
 *
 * This function processes the command-line arguments to obtain the file path of the
 * table to be imported. It performs validation checks to ensure a catalog is loaded
 * and the correct number of parameters (2) is provided.
 *
 * The method then uses `InputFileReader::readTableFromFile` to parse the table data
 * from the specified `filepath`. The resulting `Table` object is then added to the
 * `context.loadedCatalog`. This operation makes the new table part of the active
 * in-memory database. A confirmation message, including the imported table's name,
 * is printed to the console upon success. Any errors during the process are caught
 * and reported.
 *
 * @param params A constant reference to a vector of strings containing command-line arguments.
 * Expected elements:
 * - `params[0]`: "import"
 * - `params[1]`: The file path (as a string) to the table data to be imported.
 *
 * @throws std::runtime_error If `context.loadedCatalogExists` is `false` (no catalog loaded).
 * @throws std::runtime_error If `params.size()` is not 2 (incorrect number of arguments).
 * @throws std::exception Catches any exceptions propagated from `InputFileReader::readTableFromFile`
 * (e.g., file not found, read errors, parsing errors, invalid file format).
 * @throws std::runtime_error If `context.loadedCatalog.addTable()` throws, typically
 * indicating that a table with the same name already exists in the catalog.
 */
void CatalogImportCommand::execute(const std::vector<std::string>& params) {

    if (!context.loadedCatalogExists) {
        throw std::runtime_error("There is no file opened! ");
    }

    if (params.size() != 2) {
        throw std::runtime_error("Not enough parameters! ");
    }

	const std::string& filepath = params[1];

    try {
        Table table = context.inputFileReader.readTableFromFile(filepath);

        context.loadedCatalog.addTable(table);

        context.outputConsoleWritter.printLine("Succesfuly imported table - " + table.getName() + ". ");
    }
    catch (const std::exception& e) {
        context.outputConsoleWritter.printLine(e.what());
    }
}

/**
 * @brief Creates a deep copy of the current `CatalogImportCommand` object.
 *
 * This override constructs a new `CatalogImportCommand` instance,
 * associating it with the provided `newContext`. Since `CatalogImportCommand`
 * itself only holds a reference to `CommandContext` and no other dynamically
 * allocated members, a simple construction with the new context is sufficient
 * for cloning this command object.
 *
 * @param newContext A reference to the `CommandContext` that the new cloned command should use.
 * @return A pointer to a newly allocated `CatalogImportCommand` object.
 * @warning The caller is responsible for deleteing the returned pointer.
 */
    Command* CatalogImportCommand::clone(CommandContext& newContext) const {
    return new CatalogImportCommand(newContext);
}