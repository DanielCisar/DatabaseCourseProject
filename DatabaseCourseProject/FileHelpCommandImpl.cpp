#include "FileHelpCommand.hpp"
#include "CommandContext.hpp" 

/**
 * @brief Constructs a help command for file and catalog operations.
 *
 * @param context A reference to the shared command context.
 */
FileHelpCommand::FileHelpCommand(CommandContext& context)
	: context(context) {
}

/**
 * @brief Prints all supported commands for both file and catalog operations.
 *
 * @param params Command parameters (not used in this command).
 */
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
	context.outputConsoleWritter.printLine("  import <file name> - Adds a new table from file (fails if name exists)");
	context.outputConsoleWritter.printLine("  showtables - Lists all loaded tables");
	context.outputConsoleWritter.printLine("  describe <table name> - Displays column types of the specified table");
	context.outputConsoleWritter.printLine("  print <table name> - Shows all table rows with paging (next/prev/exit)");
	context.outputConsoleWritter.printLine("  export <table name> <file name> - Saves table to file");
	context.outputConsoleWritter.printLine("  select <column-n> <value> <table> - Shows rows where <column-n> equals <value>");
	context.outputConsoleWritter.printLine("  addcolumn <table> <col name> <type> - Adds a new column with NULLs");
	context.outputConsoleWritter.printLine("  update <table> <search-col> <search-val> <target-col> <target-val> - Updates values conditionally");
	context.outputConsoleWritter.printLine("  delete <table> <column-n> <value> - Deletes rows matching value");
	context.outputConsoleWritter.printLine("  insert <table> <val1> ... <valN> - Inserts a new row");
	context.outputConsoleWritter.printLine("  innerjoin <table1> <col1> <table2> <col2> - Joins two tables by columns");
	context.outputConsoleWritter.printLine("  rename <old> <new> - Renames a table (fails if <new> exists)");
	context.outputConsoleWritter.printLine("  count <table> <column> <value> - Counts rows matching value");
	context.outputConsoleWritter.printLine("  aggregate <table> <search-col> <val> <target-col> <op> - Applies sum/product/max/min");

	context.outputConsoleWritter.printLine("");
}

/**
 * @brief Creates a deep copy of the current `FileHelpCommand` object.
 *
 * This override constructs a new `FileHelpCommand` instance,
 * associating it with the provided `newContext`. Since `FileHelpCommand`
 * itself only holds a reference to `CommandContext` and no other dynamically
 * allocated members, a simple construction with the new context is sufficient
 * for cloning this command object.
 *
 * @param newContext A reference to the `CommandContext` that the new cloned command should use.
 * @return A pointer to a newly allocated `FileHelpCommand` object.
 * @warning The caller is responsible for deleteing the returned pointer.
 */
Command* FileHelpCommand::clone(CommandContext& newContext) const {
	return new FileHelpCommand(newContext);
}