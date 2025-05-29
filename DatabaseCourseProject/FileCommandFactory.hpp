#pragma once
#include "Command.hpp"
#include "FileOpenCommand.hpp"
#include "FileCloseCommand.hpp"
#include "FileSaveCommand.hpp"
#include "FileSaveAsCommand.hpp"
#include "FileHelpCommand.hpp"
#include "FileExitCommand.hpp"
#include <memory>
#include <string>

class FileCommandFactory {
public:
    static Command* createCommand(const std::string& name, CommandContext& context);
};
