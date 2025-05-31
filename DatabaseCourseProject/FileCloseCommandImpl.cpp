#include "FileCloseCommand.hpp"
#include "CommandContext.hpp"

/**
 * @brief Constructs the FileCloseCommand with a reference to the command context.
 *
 * @param context The shared context used to access the loaded catalog and I/O interfaces.
 */
FileCloseCommand::FileCloseCommand(CommandContext& context)
    : context(context) {
}

/**
 * @brief Executes the close command, resetting the loaded catalog state.
 *
 * This function performs the necessary actions to "close" the currently loaded database catalog.
 * It first verifies that a catalog is indeed open by checking the `context.loadedCatalogExists` flag.
 * If a catalog is open, it prints a confirmation message to the console, then proceeds to
 * clear the contents of the `context.loadedCatalog` (by assigning an empty `Catalog` object)
 * and updates the `context.loadedCatalogExists` flag to `false`.
 *
 * @param params A constant reference to a vector of strings containing command-line arguments.
 * For the `close` command, these parameters are not used, but the signature
 * is required by the `Command::execute` interface.
 *
 * @throws std::runtime_error if no catalog is currently loaded (`context.loadedCatalogExists` is false).
 * The exception message will guide the user to open a file first.
 */
void FileCloseCommand::execute(const std::vector<std::string>& params) {
    if (!context.loadedCatalogExists) {
        throw std::runtime_error("No file is currently loaded. Please open a file first.");
    }

    context.outputConsoleWritter.printLine("Closed the currently opened file: "
        + context.loadedCatalog.getPath());

    context.loadedCatalogExists = false;
}

/**
 * @brief Creates a deep copy of the current `FileCloseCommand` object.
 *
 * This override constructs a new `FileCloseCommand` instance,
 * associating it with the provided `newContext`. Since `FileCloseCommand`
 * itself only holds a reference to `CommandContext` and no other dynamically
 * allocated members, a simple construction with the new context is sufficient
 * for cloning this command object.
 *
 * @param newContext A reference to the `CommandContext` that the new cloned command should use.
 * @return A pointer to a newly allocated `FileCloseCommand` object.
 * @warning The caller is responsible for deleteing the returned pointer.
 */
Command* FileCloseCommand::clone(CommandContext& newContext) const {
    return new FileCloseCommand(newContext);
}