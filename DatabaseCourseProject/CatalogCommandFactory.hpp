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
#include <memory>
#include <string>
#include "CatalogUpdateCommand.hpp"
#include "CatalogShowTablesCommand.hpp"

class CatalogCommandFactory {
public:
    static Command* createCommand(const std::string& name, CommandContext& context);
};
