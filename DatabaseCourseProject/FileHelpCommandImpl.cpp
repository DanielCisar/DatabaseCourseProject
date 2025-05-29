#include "FileHelpCommand.hpp"
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

FileHelpCommand::FileHelpCommand(CommandContext& context)
	: context(context) {
}

void FileHelpCommand::execute(const std::vector<std::string>& params) {
	context.outputConsoleWritter.printLine("The following commands are supported:");
	context.outputConsoleWritter.printLine("open <file>	opens <file>");
	context.outputConsoleWritter.printLine("close			closes currently opened file");
	context.outputConsoleWritter.printLine("save			saves the currently open file");
	context.outputConsoleWritter.printLine("saveas <file>	saves the currently open file in <file>");
	context.outputConsoleWritter.printLine("help			prints this information");
	context.outputConsoleWritter.printLine("exit			exists the program");
}
