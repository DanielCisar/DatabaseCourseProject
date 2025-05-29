#pragma once
#include "Command.hpp"

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
};