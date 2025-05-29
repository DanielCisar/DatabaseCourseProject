#pragma once
#include "Command.hpp"

class CatalogAggregateCommand : public  Command {
private:
	CommandContext& context;
public:
	CatalogAggregateCommand(CommandContext& context);
	void execute(const std::vector<std::string>& params) override;
};