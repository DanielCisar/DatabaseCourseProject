#pragma once
#include "Command.hpp"

class FileCloseCommand : public Command {
private:
	CommandContext& context;
public:
	FileCloseCommand(CommandContext& context);
	void execute(const std::vector<std::string>& params) override;
};