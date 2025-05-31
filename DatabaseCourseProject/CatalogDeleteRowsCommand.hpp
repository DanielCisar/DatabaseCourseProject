#pragma once
#include "Command.hpp"
#include "CommandContext.hpp"

/**
 * @class CatalogDeleteRowsCommand
 * @brief Command to delete rows from a table that match a specific column-value condition.
 *
 * This command enables users to remove rows from a designated table. It searches
 * for rows where a specified column's value matches a given criterion and
 * deletes all such identified rows.
 */
class CatalogDeleteRowsCommand : public  Command {
private:
	/// Reference to the command context (shared environment and resources)
	CommandContext& context;
public:
	/**
	* @brief Constructs a CatalogDeleteRowsCommand instance.
	*
	* @param context A reference to the `CommandContext` object, which encapsulates
	* the application's shared database catalog and I/O utility handlers.
	*/
	CatalogDeleteRowsCommand(CommandContext& context);

    /**
     * @brief Executes the delete rows command, removing matching records from a table.
     *
     * This method searches for rows in the specified `tableName` where the value in
     * `searchColumnIndex` matches `searchValue`. All rows that satisfy this condition
     * are then deleted from the table. A count of the deleted rows is displayed to the console.
     *
     * @param params A constant reference to a vector of strings representing command-line parameters.
     * Expected format:
     * - `params[0]`: "delete" (command name)
     * - `params[1]`: The name of the target table from which rows will be deleted.
     * - `params[2]`: The 0-indexed integer position of the column to search within.
     * - `params[3]`: The value (as a string) to match against cells in the specified column.
     *
     * @throws std::runtime_error If no catalog is currently loaded.
     * @throws std::runtime_error If the number of parameters is incorrect (not 4).
     * @throws std::runtime_error If the specified table does not exist in the catalog.
     * @throws std::out_of_range If `params[2]` cannot be converted to an integer, or if the
     * resulting `searchColumnIndex` is out of bounds for the table.
     * @throws std::exception Any other unexpected exceptions propagated from underlying operations.
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