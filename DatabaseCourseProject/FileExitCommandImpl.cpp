#include "FileExitCommand.hpp"
#include "Table.hpp"
#include "TableColumn.hpp"
#include "DoubleColumn.hpp"
#include "IntegerColumn.hpp"
#include "StringColumn.hpp"
#include "ColumnType.hpp"
#include "ColumnFactory.hpp"
#include <vector>
#include <string>
#include "Catalog.hpp"
#include <filesystem>
#include <stdexcept>
#include <fstream>
#include "FileUtils.hpp"
#include <ostream>
#include <iostream>

FileExitCommand::FileExitCommand(CommandContext& context)
	: context(context) {
}

void FileExitCommand::execute(const std::vector<std::string>& params) {
	context.outputConsoleWritter.printLine("Exiting the program... ");
}
