#include "SupportedCommands.hpp"

std::vector<std::string> SupportedCommands::returnSupportedFileCommands() {
	return {
		"open",
		"close",
		"save",
		"saveas",
		"help",
		"exit"
	};
}

std::vector<std::string> SupportedCommands::returnSupportedCatalogCommands() {
	return {
		"addcolumn",
		"aggregate",
		"count",
		"delete",
		"decribe",
		"export",
		"import",
		"innerjoin",
		"insert",
		"print",
		"rename",
		"select",
		"showtables",
		"update"
	};
}