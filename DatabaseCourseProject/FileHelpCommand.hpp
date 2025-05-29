#pragma once
#include "Command.hpp"

class FileHelpCommand : public Command {
private:
	CommandContext& context;
public:
	FileHelpCommand(CommandContext& context);
	void execute(const std::vector<std::string>& params) override;
};