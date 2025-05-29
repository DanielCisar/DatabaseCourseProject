#pragma once
#include "Command.hpp"

class CatalogExportTableCommand : public  Command {
private:
	CommandContext& context;
public:
	CatalogExportTableCommand(CommandContext& context);
	void execute(const std::vector<std::string>& params) override;
};