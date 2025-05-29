#pragma once
#include "Command.hpp"

class CatalogImportCommand : public  Command {
private:
	CommandContext& context;
public:
	CatalogImportCommand(CommandContext& context);
	void execute(const std::vector<std::string>& params) override;
};