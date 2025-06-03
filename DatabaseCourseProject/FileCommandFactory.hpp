#pragma once
#include "Command.hpp"
#include "FileOpenCommand.hpp"
#include "FileCloseCommand.hpp"
#include "FileSaveCommand.hpp"
#include "FileSaveAsCommand.hpp"
#include "FileHelpCommand.hpp"
#include "FileExitCommand.hpp"
#include <string>

/**
 * @class FileCommandFactory
 * @brief A factory class responsible for creating instances of file-related commands.
 *
 * This static factory provides a centralized mechanism to instantiate concrete
 * `Command` objects that handle file system operations (like opening, saving,
 * and closing files). It decouples the command creation logic from the client code.
 */
class FileCommandFactory {
public:
    /**
     * @brief Creates and returns a new `Command` object based on the provided name for file operations.
     *
     * This static method acts as a factory for commands that interact with files.
     * It maps a command name string to a specific `Command` implementation and
     * constructs an instance of that command, passing it the shared `CommandContext`.
     *
     * @param name The string identifier of the file command to create (e.g., "open", "save", "exit").
     * @param context A reference to the `CommandContext` to be used by the created command.
     * @return A pointer to a newly allocated `Command` object.
     * @throws std::runtime_error If the provided `name` does not correspond to a known file command.
     */
    static Command* createCommand(const std::string& name, CommandContext& context);
};
