#pragma once
#include "Command.hpp"

class FileOpenCommand : public Command {
private:
	CommandContext& context;
public:
	FileOpenCommand(CommandContext& context);
	void execute(const std::vector<std::string>& params) override;
};