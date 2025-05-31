#pragma once
#include "Command.hpp"
#include "CommandContext.hpp"

/**
 * @class FileExitCommand
 * @brief Handles the "exit" file command which terminates the program.
 *
 * This command is responsible for displaying a goodbye message and
 * signaling the main loop to stop (typically handled elsewhere after execution).
 */
class FileExitCommand : public Command {
private:
    CommandContext& context; ///< Shared context for accessing I/O components and catalog

public:
    /**
     * @brief Constructs the FileExitCommand with the given execution context.
     *
     * @param context Shared command context providing access to output console and state.
     */
    FileExitCommand(CommandContext& context);

    /**
     * @brief Executes the "exit" command.
     *
     * Prints a farewell message. Actual application termination logic is typically
     * managed in the Engine loop after execution of this command.
     *
     * @param params Arguments provided to the command (not used in this case).
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
