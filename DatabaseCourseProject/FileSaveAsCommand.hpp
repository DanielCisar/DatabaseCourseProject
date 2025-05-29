#pragma once
#include "Command.hpp"

class FileSaveAsCommand : public Command {
private:
	CommandContext& context;
public:
	FileSaveAsCommand(CommandContext& context);
	void execute(const std::vector<std::string>& params) override;
};