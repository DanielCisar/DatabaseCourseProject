#pragma once
#include "Command.hpp"
#include "CommandContext.hpp"

/**
 * @class FileSaveCommand
 * @brief Command to persist the current in-memory catalog and its tables to disk.
 *
 * This command handles the application's "save" operation, writing all changes
 * made to the loaded catalog and its associated tables back to their original
 * respective file paths.
 */
class FileSaveCommand : public Command {
private:
    /// Reference to the shared command context, providing access to the loaded catalog and I/O utilities.
    CommandContext& context;  

public:
    /**
     * @brief Constructs a FileSaveCommand instance.
     *
     * @param context A reference to the `CommandContext` object, which provides
     * access to the application's shared database catalog, file writers, and console I/O handlers.
     */
    FileSaveCommand(CommandContext& context);

    /**
     * @brief Executes the 'save' command, writing all loaded data back to original files.
     *
     * This method iterates through each table currently loaded in the `context.loadedCatalog`
     * and attempts to save its data to the file path originally associated with that table.
     * Subsequently, it saves the `context.loadedCatalog` itself (which contains the metadata
     * and file paths of all tables) to its original catalog file path.
     * Success or error messages are displayed to the console.
     *
     * @param params A constant reference to a vector of strings representing command-line parameters.
     * This command expects no parameters other than the command name itself (`params[0]` must be "save").
     *
     * @throws std::runtime_error If no catalog is currently loaded in memory when the command is executed.
     * @throws std::exception Any exceptions propagated from `OutputFileWritter::writeTableToFile`
     * or `OutputFileWritter::writeCatalogToFile` during the saving process (e.g., file write errors,
     * permissions issues, invalid paths).
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