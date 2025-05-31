#include "FileExitCommand.hpp"
#include "CommandContext.hpp"

/**
 * @brief Constructs a FileExitCommand with the provided command context.
 *
 * @param context A reference to the command context containing shared state.
 */
FileExitCommand::FileExitCommand(CommandContext& context)
    : context(context) {
}

/**
 * @brief Executes the "exit" command.
 *
 * Outputs a message to notify the user that the program is exiting.
 * This function does not terminate the program itself — it is expected
 * that the main Engine loop will check for this command and handle termination.
 *
 * @param params Unused parameter vector for this command.
 */
void FileExitCommand::execute(const std::vector<std::string>& params) {
    context.outputConsoleWritter.printLine("Exiting the program... ");
}

/**
 * @brief Creates a deep copy of the current `FileExitCommand` object.
 *
 * This override constructs a new `FileExitCommand` instance,
 * associating it with the provided `newContext`. Since `FileExitCommand`
 * itself only holds a reference to `CommandContext` and no other dynamically
 * allocated members, a simple construction with the new context is sufficient
 * for cloning this command object.
 *
 * @param newContext A reference to the `CommandContext` that the new cloned command should use.
 * @return A pointer to a newly allocated `FileExitCommand` object.
 * @warning The caller is responsible for deleteing the returned pointer.
 */
Command* FileExitCommand::clone(CommandContext& newContext) const {
    return new FileExitCommand(newContext);
}