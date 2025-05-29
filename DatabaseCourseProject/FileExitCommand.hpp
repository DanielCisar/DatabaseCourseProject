#pragma once
#include "Command.hpp"

class FileExitCommand : public Command {
private:
	CommandContext& context;
public:
	FileExitCommand(CommandContext& context);
	void execute(const std::vector<std::string>& params) override;
};