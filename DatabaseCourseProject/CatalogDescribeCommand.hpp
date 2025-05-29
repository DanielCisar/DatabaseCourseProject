#pragma once
#include "Command.hpp"

class CatalogDescribeCommand : public  Command {
private:
	CommandContext& context;
public:
	CatalogDescribeCommand(CommandContext& context);
	void execute(const std::vector<std::string>& params) override;
};