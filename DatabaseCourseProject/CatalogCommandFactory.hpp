#pragma once
#include "Command.hpp"
#include "CatalogInsertCommand.hpp"
#include "CatalogSelectCommand.hpp"
#include "CatalogPrintCommand.hpp"
#include "CatalogDescribeCommand.hpp"
#include "CatalogCountCommand.hpp"
#include "CatalogAddColumnCommand.hpp"
#include "CatalogAggregateCommand.hpp"
#include "CatalogDeleteRowsCommand.hpp"
#include "CatalogRenameCommand.hpp"
#include "CatalogInnerJoinCommand.hpp"
#include "CatalogImportCommand.hpp"
#include "CatalogExportTableCommand.hpp"
#include <string>
#include "CatalogUpdateCommand.hpp"
#include "CatalogShowTablesCommand.hpp"

/**
 * @class CatalogCommandFactory
 * @brief A factory class responsible for creating instances of catalog-related commands.
 *
 * This static factory provides a centralized mechanism to instantiate concrete
 * `Command` objects based on a given command name string. It decouples the
 * command creation logic from the client code.
 */
class CatalogCommandFactory {
public:

    /**
    * @brief Creates and returns a new `Command` object based on the provided name.
    *
    * This static method acts as a factory for all commands that operate on the
    * database catalog. It maps a command name string to a specific `Command`
    * implementation and constructs an instance of that command.
    *
    * @param name The string identifier of the command to create (e.g., "insert", "select", "describe").
    * @param context A reference to the `CommandContext` to be used by the created command.
    * @return A pointer to a newly allocated `Command` object.
    * @throws std::runtime_error If the provided `name` does not correspond to a known catalog command.    
    */
    static Command* createCommand(const std::string& name, CommandContext& context);
};
