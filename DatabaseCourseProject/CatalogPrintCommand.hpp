#pragma once
#include "Command.hpp"

class CatalogPrintCommand : public  Command {
private:
	CommandContext& context;
public:
	CatalogPrintCommand(CommandContext& context);
	void execute(const std::vector<std::string>& params) override;
};