#pragma once
#include "Command.hpp"
#include "CommandContext.hpp" 

/**
 * @class CatalogUpdateCommand
 * @brief Command to update values in a target column for rows matching a specified condition.
 *
 * This command allows users to modify data within a table. It identifies rows
 * where a specific search column contains a given value, and for all such
 * matching rows, it updates the value in a different (or the same) target column.
 */
class CatalogUpdateCommand : public  Command {
private:
	/// Reference to the shared command execution context, providing access to the loaded catalog and I/O utilities.
	CommandContext& context;
public:
	/**
	 * @brief Constructs a CatalogUpdateCommand instance.
	 *
	 * @param context A reference to the `CommandContext` object, which encapsulates
	 * the application's shared database catalog and console output handler.
	 */
	CatalogUpdateCommand(CommandContext& context);

    /**
	* @brief Executes the 'update' command, modifying table data conditionally.
	*
	* This method identifies rows in a specified `tableName` where the value in
	* `searchColumnIndex` matches `searchValue`. For each matching row, it updates
	* the cell in `targetColumnIndex` to `targetValue`. The `targetValue` will be
	* converted to the appropriate type for the `targetColumn`. A success message
	* is printed to the console upon completion.
	*
	 * @param params A constant reference to a vector of strings representing command-line parameters.
	* Expected format:
	* - `params[0]`: "update" (command name)
	* - `params[1]`: The name of the table to update.
	* - `params[2]`: The 0-indexed integer position of the column to search within (as a string).
	* - `params[3]`: The value (as a string) to match in the search column.
	* - `params[4]`: The 0-indexed integer position of the column to update (as a string).
	* - `params[5]`: The new value (as a string) to set in the target column.
	*
	* @throws std::runtime_error If no catalog is currently loaded.
	* @throws std::runtime_error If the number of parameters is incorrect (not 6).
	* @throws std::invalid_argument If `params[2]` or `params[4]` cannot be converted to an integer.
	* @throws std::runtime_error If the specified table does not exist in the catalog.
	* @throws std::out_of_range If `searchColumnIndex` or `targetColumnIndex` is out of bounds for the table's columns.
	* @throws std::exception Any exceptions propagated from `TableColumn::changeValueAtIndex`
	* (e.g., `std::invalid_argument` if `targetValue` cannot be converted to the target column's type).
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