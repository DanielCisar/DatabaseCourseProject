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
	context.outputConsoleWritter.printLine("The following commands are supported:\n");

	context.outputConsoleWritter.printLine("File commands:");
	context.outputConsoleWritter.printLine("  open <file>         - Opens <file>");
	context.outputConsoleWritter.printLine("  close               - Closes currently opened file");
	context.outputConsoleWritter.printLine("  save                - Saves the currently open file");
	context.outputConsoleWritter.printLine("  saveas <file>       - Saves the currently open file in <file>");
	context.outputConsoleWritter.printLine("  help                - Prints this help information");
	context.outputConsoleWritter.printLine("  exit                - Exits the program");

	context.outputConsoleWritter.printLine("");

	context.outputConsoleWritter.printLine("Catalog commands:");
	context.outputConsoleWritter.printLine("  import <file name>");
	context.outputConsoleWritter.printLine("    - Adds a new table from file. If a table with the same name exists, an error is raised.");
	context.outputConsoleWritter.printLine("      The table's schema (column types) must be defined in the file.");

	context.outputConsoleWritter.printLine("  showtables");
	context.outputConsoleWritter.printLine("    - Displays a list of all loaded tables.");

	context.outputConsoleWritter.printLine("  describe <table name>");
	context.outputConsoleWritter.printLine("    - Shows the types of columns in the specified table.");

	context.outputConsoleWritter.printLine("  print <table name>");
	context.outputConsoleWritter.printLine("    - Displays all rows of the table with paging. Supports next, prev, and exit commands.");

	context.outputConsoleWritter.printLine("  export <table name> <file name>");
	context.outputConsoleWritter.printLine("    - Saves the specified table to a file.");

	context.outputConsoleWritter.printLine("  select <column-n> <value> <table name>");
	context.outputConsoleWritter.printLine("    - Prints all rows from the table where column <n> has the specified value (with paging).");

	context.outputConsoleWritter.printLine("  addcolumn <table name> <column name> <column type>");
	context.outputConsoleWritter.printLine("    - Adds a new column to the table. All existing rows get NULL (empty) in the new column.");

	context.outputConsoleWritter.printLine("  update <table name> <search column n> <search value> <target column n> <target value>");
	context.outputConsoleWritter.printLine("    - Updates all rows where column <search column n> has the given value to set <target column n> to the target value. NULL is supported.");

	context.outputConsoleWritter.printLine("  delete <table name> <search column n> <search value>");
	context.outputConsoleWritter.printLine("    - Deletes all rows where the specified column has the given value.");

	context.outputConsoleWritter.printLine("  insert <table name> <value 1> ... <value n>");
	context.outputConsoleWritter.printLine("    - Inserts a new row into the specified table.");

	context.outputConsoleWritter.printLine("  innerjoin <table1> <column n1> <table2> <column n2>");
	context.outputConsoleWritter.printLine("    - Performs an inner join on two tables using the specified columns and creates a new result table.");

	context.outputConsoleWritter.printLine("  rename <old name> <new name>");
	context.outputConsoleWritter.printLine("    - Renames a table. Fails if the new name already exists.");

	context.outputConsoleWritter.printLine("  count <table name> <search column n> <search value>");
	context.outputConsoleWritter.printLine("    - Counts the number of rows where the given column matches the value.");

	context.outputConsoleWritter.printLine("  aggregate <table name> <search column n> <search value> <target column n> <operation>");
	context.outputConsoleWritter.printLine("    - Applies an aggregation (sum, product, maximum, minimum) on the target column for rows matching the search column value. Only numeric types allowed.");

	context.outputConsoleWritter.printLine("");

}
