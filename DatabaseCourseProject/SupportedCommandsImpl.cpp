#include "SupportedCommands.hpp"

/**
 * @brief Returns a list of supported file-related commands.
 * @return A `std::vector<std::string>` containing: "open", "close", "save", "saveas", "help", "exit".
 */
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

/**
 * @brief Returns a list of supported catalog-related commands.
 * @return A `std::vector<std::string>` containing: "addcolumn", "aggregate", "count", "delete",
 * "decribe", "export", "import",
 * "innerjoin", "insert", "print", "rename", "select", "showtables", "update".
 */
std::vector<std::string> SupportedCommands::returnSupportedCatalogCommands() {
	return {
		"addcolumn",
		"aggregate",
		"count",
		"delete",
		"describe",
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