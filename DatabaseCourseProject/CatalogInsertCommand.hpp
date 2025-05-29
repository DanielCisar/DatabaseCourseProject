#pragma once
#include "Command.hpp"

class CatalogInsertCommand : public  Command {
private:
	CommandContext& context;
public:
	CatalogInsertCommand(CommandContext& context);
	void execute(const std::vector<std::string>& params) override;
};