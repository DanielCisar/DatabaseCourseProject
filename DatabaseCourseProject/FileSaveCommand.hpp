#pragma once
#include "Command.hpp"

class FileSaveCommand : public Command {
private:
	CommandContext& context;
public:
	FileSaveCommand(CommandContext& context);
	void execute(const std::vector<std::string>& params) override;
};