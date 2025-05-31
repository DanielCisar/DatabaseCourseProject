#pragma once
#include "Command.hpp"
#include "CommandContext.hpp"

/**
 * @class FileHelpCommand
 * @brief Provides help information for all supported file and catalog commands.
 *
 * This command prints a list of available commands along with a brief description
 * of each, guiding the user on how to interact with the application.
 */
class FileHelpCommand : public Command {
private:
    /// Reference to the shared command context used across all commands.
    CommandContext& context;

public:
    /**
     * @brief Constructs a FileHelpCommand with the provided command context.
     *
     * @param context A reference to the command context containing shared components.
     */
    FileHelpCommand(CommandContext& context);

    /**
     * @brief Executes the "help" command.
     *
     * Displays a list of all supported commands and their usage.
     *
     * @param params Unused parameter vector for this command.
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