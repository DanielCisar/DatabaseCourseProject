#include "FileCommandFactory.hpp"

Command* FileCommandFactory::createCommand(const std::string& name, CommandContext& context) {
    if (name == "open") return new FileOpenCommand(context);
    if (name == "close") return new FileCloseCommand(context);
    if (name == "save") return new FileSaveCommand(context);
    if (name == "saveas") return new FileSaveAsCommand(context);
    if (name == "help") return new FileHelpCommand(context);
    if (name == "exit") return new FileExitCommand(context);
    throw std::runtime_error("Unknown file command: " + name);
}