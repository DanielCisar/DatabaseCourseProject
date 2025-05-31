#include "FileSaveAsCommand.hpp"
#include "CommandContext.hpp"
#include "Catalog.hpp"
#include "Table.hpp"          
#include "FileUtils.hpp"    
#include <fstream>           
#include <iostream>          
#include <stdexcept>          


/**
 * @brief Constructs a FileSaveAsCommand object, initializing it with the shared command context.
 *
 * @param context A reference to the `CommandContext` object. This context provides
 * access to the application's shared state, including the
 * loaded database catalog and the necessary I/O utility handlers
 * for writing files.
 */
FileSaveAsCommand::FileSaveAsCommand(CommandContext& context)
    : context(context) {
}

/**
 * @brief Executes the 'saveas' command, creating a new set of catalog and table files.
 *
 * This function initiates the process of saving the current in-memory catalog
 * and all its contained tables to a new location specified by the user.
 * It first performs validation checks:
 * 1. Ensures a catalog is currently loaded in the application.
 * 2. Verifies that the correct number of parameters has been provided (the command name and one filepath).
 *
 * A new `Catalog` object is constructed to represent the data at the new save location.
 * Each table from the `context.loadedCatalog` is iterated over, a new name (prefixed with "copy_")
 * and a new file path (within the specified target directory) are generated for its saved version.
 * The table is then cloned with this new name and path, written to its new file,
 * and added to the `newCatalog` object.
 *
 * Finally, the `newCatalog` (which now contains metadata for all the copied tables)
 * is written to the main catalog file at the specified `filepath`.
 * A success message is printed to the console, or an error message if any step fails.
 *
 * @param params A constant reference to a vector of strings containing the command name and its arguments.
 * - `params[0]` is "saveas".
 * - `params[1]` is the target file path (e.g., "new_db/catalog.csv").
 *
 * @throws std::runtime_error If `context.loadedCatalogExists` is `false` (no file open).
 * @throws std::runtime_error If `params.size()` is not equal to 2 (incorrect arguments).
 * @throws std::exception Any exceptions propagated from file writing operations (`writeTableToFile`,
 * `writeCatalogToFile`) or table cloning, indicating issues like
 * invalid paths, permissions errors, or data conversion problems during saving.
 */
void FileSaveAsCommand::execute(const std::vector<std::string>& params) {
    if (!context.loadedCatalogExists) {
        throw std::runtime_error("No file is currently loaded. Please open a file first.");
        return;
    }

    if (params.size() != 2) {
        throw std::runtime_error("Not enough parameters! ");
    }

    const std::string& filepath = params[1];
    Catalog newCatalog(filepath);
    std::string targetFolder = FileUtils::getDirectoryPath(filepath);

    for (auto& table : context.loadedCatalog) {
        std::string newName = "copy_" + table.getName();
        std::string newTablePath = targetFolder + "/copy_" + newName + ".csv";

        try {
            Table newTable = table.cloneWithNewNameAndPath(newName, newTablePath);
            context.outputFileWritter.writeTableToFile(newTable, newTablePath);
            newCatalog.addTable(newTable);
        }
        catch (const std::exception& e) {
            context.outputConsoleWritter.printLine(e.what());
        }
    }

    try {
        context.outputFileWritter.writeCatalogToFile(newCatalog, filepath);
        context.outputConsoleWritter.printLine("Changes saved to: " + filepath);
    }
    catch (const std::exception& e) {
        context.outputConsoleWritter.printLine(e.what());
    }
}

/**
 * @brief Creates a deep copy of the current `FileSaveAsCommand` object.
 *
 * This override constructs a new `FileSaveAsCommand` instance,
 * associating it with the provided `newContext`. Since `FileSaveAsCommand`
 * itself only holds a reference to `CommandContext` and no other dynamically
 * allocated members, a simple construction with the new context is sufficient
 * for cloning this command object.
 *
 * @param newContext A reference to the `CommandContext` that the new cloned command should use.
 * @return A pointer to a newly allocated `FileSaveAsCommand` object.
 * @warning The caller is responsible for deleteing the returned pointer.
 */
Command* FileSaveAsCommand::clone(CommandContext& newContext) const {
    return new FileSaveAsCommand(newContext);
}