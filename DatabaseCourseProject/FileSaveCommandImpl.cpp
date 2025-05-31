#include "FileSaveCommand.hpp"
#include "CommandContext.hpp" 
#include "Table.hpp"        
#include "Catalog.hpp"        
#include <stdexcept>

/**
 * @brief Constructs the FileSaveCommand object, initializing it with the provided command context.
 *
 * @param context A reference to the `CommandContext` object. This context is
 * crucial for the command to access the application's shared database catalog,
 * as well as the necessary file output and console output utility handlers.
 */
FileSaveCommand::FileSaveCommand(CommandContext& context)
    : context(context) {
}

/**
 * @brief Executes the 'save' command, persisting the current in-memory catalog and tables.
 *
 * This function performs the core save operation. It first validates that a catalog
 * is currently loaded in the application's memory. If so, it proceeds to:
 * 1. Iterate through each `Table` object within the `context.loadedCatalog`.
 * 2. For each table, it calls `OutputFileWritter::writeTableToFile` to save the table's
 * data back to its original file path (retrieved via `table.getFilename()`).
 * Errors during individual table saves are caught and reported to the console,
 * but the process continues for other tables.
 * 3. After all tables are processed, it calls `OutputFileWritter::writeCatalogToFile`
 * to save the `context.loadedCatalog` itself to its original catalog file path
 * (retrieved via `context.loadedCatalog.getPath()`). This updates the catalog
 * metadata, including any newly imported tables.
 * 4. Finally, a confirmation message is printed to the console upon successful completion
 * of all saves.
 *
 * @param params A constant reference to a vector of strings containing command-line arguments.
 * This command does not accept any parameters beyond the command name ("save");
 * its signature is mandated by the `Command::execute` interface.
 *
 * @throws std::runtime_error If `context.loadedCatalogExists` is `false`, indicating
 * that no catalog has been opened prior to attempting the save operation.
 * @throws std::exception Any exceptions propagated from the `OutputFileWritter` methods
 * during file write operations (e.g., file access errors, permissions issues,
 * disk full errors), which are caught and reported to the console.
 */
void FileSaveCommand::execute(const std::vector<std::string>& params) {

    if (!context.loadedCatalogExists) {
        throw std::runtime_error("No file is currently loaded. Please open a file first.");
        return;
    }

    for (auto& table : context.loadedCatalog) {
        try {
            context.outputFileWritter.writeTableToFile(table, table.getFilename());
        }
        catch (const std::exception& e) {
            context.outputConsoleWritter.printLine(e.what());
        }
    }

    try {
        context.outputFileWritter.writeCatalogToFile(
            context.loadedCatalog,
            context.loadedCatalog.getPath()
        );
    }
    catch (const std::exception& e) {
        context.outputConsoleWritter.printLine(e.what());
    }

    context.outputConsoleWritter.printLine("Saved changes to same files.");
}

/**
 * @brief Creates a deep copy of the current `FileSaveCommand` object.
 *
 * This override constructs a new `FileSaveCommand` instance,
 * associating it with the provided `newContext`. Since `FileSaveCommand`
 * itself only holds a reference to `CommandContext` and no other dynamically
 * allocated members, a simple construction with the new context is sufficient
 * for cloning this command object.
 *
 * @param newContext A reference to the `CommandContext` that the new cloned command should use.
 * @return A pointer to a newly allocated `FileSaveCommand` object.
 * @warning The caller is responsible for deleteing the returned pointer.
 */
Command* FileSaveCommand::clone(CommandContext& newContext) const {
    return new FileSaveCommand(newContext);
}