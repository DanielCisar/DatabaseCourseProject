#pragma once
#include "Command.hpp"

class CatalogShowTablesCommand : public  Command {
private:
	CommandContext& context;
public:
	CatalogShowTablesCommand(CommandContext& context);
	void execute(const std::vector<std::string>& params) override;
};