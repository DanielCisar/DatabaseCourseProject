#pragma once
#include "Command.hpp"

class CatalogCountCommand : public  Command {
private:
	CommandContext& context;
public:
	CatalogCountCommand(CommandContext& context);
	void execute(const std::vector<std::string>& params) override;
};