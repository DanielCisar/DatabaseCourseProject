#include "CatalogCommandFactory.hpp"
#include <stdexcept> 
#include <string>    

/**
 * @brief Creates and returns a new `Command` object based on the provided name.
 *
 * This static method implements the factory logic. It checks the `name` against
 * a list of recognized catalog command names and returns a dynamically allocated
 * instance of the corresponding command class. The created command is
 * initialized with the provided `context`.
 *
 * @param name The string identifier of the command to create.
 * @param context A reference to the `CommandContext` to be used by the created command.
 * @return A pointer to a newly allocated `Command` object. The caller assumes ownership.
 * @throws std::runtime_error If the provided `name` does not match any
 * of the supported catalog commands.
 */
Command* CatalogCommandFactory::createCommand(const std::string& name, CommandContext& context) {
    if (name == "insert") return new CatalogInsertCommand(context);
    if (name == "select") return new CatalogSelectCommand(context);
    if (name == "print") return new CatalogPrintCommand(context);
    if (name == "describe") return new CatalogDescribeCommand(context);
    if (name == "count") return new CatalogCountCommand(context);
    if (name == "addcolumn") return new CatalogAddColumnCommand(context);
    if (name == "aggregate") return new CatalogAggregateCommand(context);
    if (name == "delete") return new CatalogDeleteRowsCommand(context);
    if (name == "rename") return new CatalogRenameCommand(context);
    if (name == "innerjoin") return new CatalogInnerJoinCommand(context);
    if (name == "import") return new CatalogImportCommand(context);
    if (name == "export") return new CatalogExportTableCommand(context);
    if (name == "describe") return new CatalogDescribeCommand(context);
    if (name == "showtables") return new CatalogShowTablesCommand(context);
    if (name == "update") return new CatalogUpdateCommand(context);
    throw std::runtime_error("Unknown catalog command: " + name + "Please type 'help' for a list of supported commands. ");
}