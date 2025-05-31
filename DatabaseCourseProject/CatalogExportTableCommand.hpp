#pragma once
#include "Command.hpp"
#include "CommandContext.hpp"

/**
 * @class CatalogExportTableCommand
 * @brief Command to export a specific table from the loaded catalog to a new file.
 *
 * This command allows users to save a single table, identified by its name,
 * to a specified external file path. It's useful for extracting individual
 * tables from the current in-memory catalog for further use or inspection.
 */
class CatalogExportTableCommand : public  Command {
private:
	/// Reference to the shared command execution context, providing access to the loaded catalog and I/O utilities.
	CommandContext& context;
public:
	/**
	* @brief Constructs a CatalogExportTableCommand instance.
	*
	* @param context A reference to the `CommandContext` object, which encapsulates
	* the application's shared database catalog, file writers, and console output handlers.
	*/
	CatalogExportTableCommand(CommandContext& context);

    /**
     * @brief Executes the 'export' command, saving a table to a specified file.
     *
     * This method retrieves a table by its name from the currently loaded catalog
     * and writes its entire content to the specified file path. The export includes
     * the table's name, column types, column names, and all data rows, formatted
     * as a standard CSV file.
     *
     * @param params A constant reference to a vector of strings representing command-line parameters.
     * Expected format:
     * - `params[0]`: "export" (command name)
     * - `params[1]`: The name of the table to be exported.
     * - `params[2]`: The target file path (e.g., "my_table_data.csv") where the table will be saved.
     *
     * @throws std::runtime_error If no catalog is currently loaded.
     * @throws std::runtime_error If the number of parameters is incorrect (not 3).
     * @throws std::runtime_error If the specified table does not exist in the catalog.
     * @throws std::exception Any exceptions propagated from `OutputFileWritter::writeTableToFile`
     * during the file write operation (e.g., file creation/write errors, permissions issues, invalid path).
     */
	void execute(const std::vector<std::string>& params) override;

    /**
    * @brief Creates a deep copy of the current object.
    *
    * This override implements the polymorphic cloning behavior defined in `Command`.
    * It constructs a new instance, associating it
    * with the provided `newContext`.
    *
    * @param newContext A reference to the `CommandContext` that the new cloned command should use.
    * @return A pointer to a newly allocated object, which is a deep copy of this instance.
    */
    Command* clone(CommandContext& newContext) const override;

};