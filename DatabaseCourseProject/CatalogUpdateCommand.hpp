#pragma once
#include "Command.hpp"

class CatalogUpdateCommand : public  Command {
private:
	CommandContext& context;
public:
	CatalogUpdateCommand(CommandContext& context);
	void execute(const std::vector<std::string>& params) override;
};