#pragma once
#include "Command.hpp"

class CatalogDeleteRowsCommand : public  Command {
private:
	CommandContext& context;
public:
	CatalogDeleteRowsCommand(CommandContext& context);
	void execute(const std::vector<std::string>& params) override;
};