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

/**
 * @brief Constructs a FileExitCommand with the provided command context.
 *
 * @param context A reference to the command context containing shared state.
 */
FileExitCommand::FileExitCommand(CommandContext& context)
    : context(context) {
}

/**
 * @brief Executes the "exit" command.
 *
 * Outputs a message to notify the user that the program is exiting.
 * This function does not terminate the program itself — it is expected
 * that the main Engine loop will check for this command and handle termination.
 *
 * @param params Unused parameter vector for this command.
 */
void FileExitCommand::execute(const std::vector<std::string>& params) {
    context.outputConsoleWritter.printLine("Exiting the program... ");
}