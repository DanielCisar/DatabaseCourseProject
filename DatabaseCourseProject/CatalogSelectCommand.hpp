#pragma once
#include "Command.hpp"
#include "CommandContext.hpp"

/**
 * @class CatalogSelectCommand
 * @brief Command to select and display rows from a table that meet a specific condition.
 *
 * This command allows users to filter and view data from a table based on a
 * value match in a designated column. All rows satisfying the condition are
 * displayed in a paginated format.
 */
class CatalogSelectCommand : public  Command {
private:
	/// Reference to the shared command execution context, providing access to the loaded catalog and I/O utilities.
	CommandContext& context;
public:
	/**
	 * @brief Constructs a CatalogSelectCommand instance.
	 *
	 * @param context A reference to the `CommandContext` object, which encapsulates
	 * the application's shared database catalog and console I/O handlers.
	 */
	CatalogSelectCommand(CommandContext& context);

    /**
	* @brief Executes the 'select' command, filtering and printing matching table rows.
	*
	* This method identifies rows in a specified `tableName` where the value in
	* `searchColumnIndex` matches `searchValue`. It retrieves the table and the
	* target column. For each row, if the condition is met, the entire row is
	* formatted as a string and collected. The collected matching rows are then
	* displayed to the console using a paginated format via `IOUtils::printInPageFormat`.
	 *
	* @param params A constant reference to a vector of strings representing command-line parameters.
	* Expected format:
	* - `params[0]`: "select" (command name)
	* - `params[1]`: The 0-indexed integer position of the column to search within (as a string).
	* - `params[2]`: The value (as a string) to match against cells in the specified column.
	* - `params[3]`: The name of the table to perform the selection on.
	*
	* @throws std::runtime_error If no catalog is currently loaded.
	* @throws std::runtime_error If the number of parameters is incorrect (not 4).
	* @throws std::runtime_error If `params[1]` cannot be converted to an integer.
	* @throws std::runtime_error If the specified table does not exist in the catalog.
	* @throws std::out_of_range If `searchColumnIndex` is out of bounds for the table's columns.
	* @throws std::exception Any other unexpected exceptions propagated from underlying operations
	* (e.g., during table data retrieval or I/O operations from `IOUtils::printInPageFormat`).
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