#pragma once
#include "Command.hpp"

class CatalogSelectCommand : public  Command {
private:
	CommandContext& context;
public:
	CatalogSelectCommand(CommandContext& context);
	void execute(const std::vector<std::string>& params) override;
};