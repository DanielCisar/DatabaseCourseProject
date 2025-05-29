#pragma once
#include "Command.hpp"

class CatalogAddColumnCommand : public Command {
private:
	CommandContext& context;
public:
	CatalogAddColumnCommand(CommandContext& context);
	void execute(const std::vector<std::string>& params) override;
};