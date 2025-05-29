#pragma once
#include <string>
#include <vector>

class SupportedCommands {
public:
	static std::vector<std::string> returnSupportedFileCommands();
	static std::vector<std::string> returnSupportedCatalogCommands();
};