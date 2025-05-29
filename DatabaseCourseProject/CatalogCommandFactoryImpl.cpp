#include "CatalogCommandFactory.hpp"

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
    if (name == "decribe") return new CatalogDescribeCommand(context);
    if (name == "showtables") return new CatalogShowTablesCommand(context);
    if (name == "update") return new CatalogUpdateCommand(context);
    throw std::runtime_error("Unknown catalog command: " + name);
}