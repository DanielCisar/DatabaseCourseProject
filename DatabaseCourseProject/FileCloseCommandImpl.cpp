#include "FileCloseCommand.hpp"
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
#include <stdexcept>
#include <fstream>
#include "FileUtils.hpp"
#include <ostream>
#include <iostream>

/**
 * @brief Constructs the FileCloseCommand with a reference to the command context.
 *
 * @param context The shared context used to access the loaded catalog and I/O interfaces.
 */
FileCloseCommand::FileCloseCommand(CommandContext& context)
    : context(context) {
}

/**
 * @brief Executes the close command which resets the loaded catalog.
 *
 * This function checks if a file is currently loaded. If so, it marks the catalog
 * as closed and informs the user via the console. If no file is open, it throws
 * an exception.
 *
 * @param params Command-line parameters (not used for this command).
 *
 * @throws std::runtime_error if no catalog is currently loaded.
 */
void FileCloseCommand::execute(const std::vector<std::string>& params) {
    if (!context.loadedCatalogExists) {
        throw std::runtime_error("No file is currently loaded. Please open a file first.");
    }

    context.outputConsoleWritter.printLine("Closed the currently opened file: "
        + context.loadedCatalog.getPath());

    context.loadedCatalogExists = false;
}
