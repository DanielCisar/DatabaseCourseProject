#include "FileCommandFactory.hpp"
#include <stdexcept> 
#include <string>    

/**
 * @brief Creates and returns a new `Command` object based on the provided name for file operations.
 *
 * This static method implements the factory logic for file-related commands.
 * It checks the `name` against a list of recognized commands and returns a
 * dynamically allocated instance of the corresponding command class.
 *
 * @param name The string identifier of the command to create.
 * @param context A reference to the `CommandContext` to be used by the created command.
 * @return A pointer to a newly allocated `Command` object. The caller assumes ownership.
 * @throws std::runtime_error If the provided `name` does not match any
 * of the supported file commands.
 */
Command* FileCommandFactory::createCommand(const std::string& name, CommandContext& context) {
    if (name == "open") return new FileOpenCommand(context);
    if (name == "close") return new FileCloseCommand(context);
    if (name == "save") return new FileSaveCommand(context);
    if (name == "saveas") return new FileSaveAsCommand(context);
    if (name == "help") return new FileHelpCommand(context);
    if (name == "exit") return new FileExitCommand(context);
    throw std::runtime_error("Unknown file command: " + name + "Please type 'help' for a list of supported commands. ");
}