#include "CatalogAddColumnCommand.hpp"
#include "CommandContext.hpp" 
#include "Table.hpp"          
#include "ColumnType.hpp"     
#include "ColumnFactory.hpp"  
#include "StringColumn.hpp"   
#include "IntegerColumn.hpp"  
#include "DoubleColumn.hpp"  
#include <stdexcept>         
#include <string>            

/**
 * @brief Constructs a CatalogAddColumnCommand object, initializing it with the shared command context.
 *
 * @param context A reference to the `CommandContext` object. This context provides
 * access to the application's shared database catalog and console output utilities,
 * which are necessary for performing the add column operation and reporting status.
 */
CatalogAddColumnCommand::CatalogAddColumnCommand(CommandContext& context)
    : context(context) {
}

/**
 * @brief Executes the 'addcolumn' command, adding a new column to a specified table.
 *
 * This function processes the command-line arguments to identify the target table,
 * the name for the new column, and its data type. It performs validation checks:
 * 1. Ensures a catalog is currently loaded.
 * 2. Verifies the correct number of parameters (4) is provided.
 * 3. Validates that the specified column type string is one of "String", "Integer", or "Double".
 *
 * Upon successful validation, a new `TableColumn` of the specified type and name is created
 * using `ColumnFactory`. This new column is then pre-filled with NULL values for all
 * existing rows in the table. Finally, the new column is added to the table.
 * Status messages are printed to the console upon success or error.
 *
 * @param params A constant reference to a vector of strings containing the command-line arguments.
 * Expected elements:
 * - `params[0]`: "addcolumn"
 * - `params[1]`: Name of the table to modify.
 * - `params[2]`: Name for the new column.
 * - `params[3]`: Type of the new column ("String", "Integer", or "Double").
 *
 * @throws std::runtime_error If `context.loadedCatalogExists` is `false` (no catalog loaded).
 * @throws std::runtime_error If `params.size()` is not 4 (incorrect number of arguments).
 * @throws std::runtime_error If `context.loadedCatalog.returnTableByName()` fails to find the specified table.
 * @throws std::runtime_error If `params[3]` (column type string) is not a recognized type.
 * @throws std::exception Any other exceptions that may arise during table modification,
 * such as memory allocation failures when creating new columns.
 */
void CatalogAddColumnCommand::execute(const std::vector<std::string>& params) {

    if (!context.loadedCatalogExists) {
        throw std::runtime_error("There is no file opened! ");
    }

    if (params.size() != 4) {
        throw std::runtime_error("Not enough parameters! ");
    }

    try {
        const std::string& tableName = params[1];
        const std::string& columnName = params[2];
        const std::string& columnTypeStr = params[3];

        Table& table = context.loadedCatalog.returnTableByName(tableName);
        int colSize = table.getColumnAtGivenIndex(0)->getSize();
        try {
            TableColumn* col = ColumnFactory::makeColumn(columnName, columnTypeStr);
            col->fillColumnWithNULL(colSize);
            table.addColumn(col);
        }
        catch (const std::exception& e) {
            context.outputConsoleWritter.printLine(e.what());
            return;
        }
        context.outputConsoleWritter.printLine("New empty column created and added successfuly. ");
    }
    catch (const std::exception& e) {
        context.outputConsoleWritter.printLine(e.what());
    }
}

/**
 * @brief Creates a deep copy of the current `CatalogAddColumnCommand` object.
 *
 * This override constructs a new `CatalogAddColumnCommand` instance,
 * associating it with the provided `newContext`. Since `CatalogAddColumnCommand`
 * itself only holds a reference to `CommandContext` and no other dynamically
 * allocated members, a simple construction with the new context is sufficient
 * for cloning this command object.
 *
 * @param newContext A reference to the `CommandContext` that the new cloned command should use.
 * @return A pointer to a newly allocated `CatalogAddColumnCommand` object.
 * @warning The caller is responsible for `delete`ing the returned pointer.
 */
Command* CatalogAddColumnCommand::clone(CommandContext& newContext) const {
    return new CatalogAddColumnCommand(newContext);
}
