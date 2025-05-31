#pragma once
#include "Command.hpp"
#include "CommandContext.hpp"

/**
 * @class FileSaveAsCommand
 * @brief Command to save the current database catalog and its tables to a new file path.
 *
 * This command allows the user to create a copy of the currently loaded
 * in-memory database catalog and all its associated tables, persisting them
 * to a new set of CSV files at a specified location on disk. This operation
 * does not affect the currently loaded catalog in memory.
 */
class FileSaveAsCommand : public Command {
private:
    /// Shared context containing all dependencies and the loaded catalog reference.
    CommandContext& context;

public:
    /**
     * @brief Constructs a FileSaveAsCommand instance.
     * @param context A reference to the `CommandContext` object, which encapsulates
     * the application's shared database catalog and I/O utility handlers.
     */
    FileSaveAsCommand(CommandContext& context);

    /**
    * @brief Executes the 'saveas' operation, saving the current catalog and tables to a new location.
    *
    * This method performs the following steps:
    * 1. Verifies that a catalog is currently loaded in memory.
    * 2. Validates the number of provided command-line parameters.
    * 3. Constructs a new `Catalog` object representing the save target.
    * 4. Iterates through each table in the currently loaded catalog:
    * - Creates a uniquely named copy of the table for the new location.
    * - Writes this new table to a `.csv` file in the target directory.
    * - Adds the new table's metadata (name, new path) to the `newCatalog` object.
    * 5. Writes the `newCatalog` object (containing metadata for all the copied tables)
    * to the specified catalog file path.
    * 6. Prints a success message to the console, indicating the new save location.
    *
    * @param params A constant reference to a vector of strings representing command-line parameters.
    * - `params[0]` is expected to be the command name ("saveas").
    * - `params[1]` is the full file path where the new catalog file and its associated
    * table files should be saved (e.g., "data/my_new_catalog.csv").
    *
    * @throws std::runtime_error If no catalog is currently loaded in memory.
    * @throws std::runtime_error If the number of parameters is incorrect (not 2).
    * @throws std::exception Any exceptions propagated from `OutputFileWritter::writeTableToFile`
    * or `OutputFileWritter::writeCatalogToFile` during the save process
    * (e.g., file creation/write errors, invalid paths).
    */
    void execute(const std::vector<std::string>& params) override;

    /**
    * @brief Creates a deep copy of the current object.
    *
    * This override implements the polymorphic cloning behavior defined in `Command`.
    * It constructs a new instance, associating it
    * with the provided `newContext`.
    *
    * @param newContext A reference to the `CommandContext` that the new cloned command should use.
    * @return A pointer to a newly allocated object, which is a deep copy of this instance.
    */
    Command* clone(CommandContext& newContext) const override;

};