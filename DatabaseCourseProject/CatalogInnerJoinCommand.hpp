#pragma once
#include "Command.hpp"

class CatalogInnerJoinCommand : public Command {
private:
	CommandContext& context;
public:
	CatalogInnerJoinCommand(CommandContext& context);
	void execute(const std::vector<std::string>& params) override;
};