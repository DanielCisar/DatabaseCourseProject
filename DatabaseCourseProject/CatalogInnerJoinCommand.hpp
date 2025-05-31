#pragma once
#include "Command.hpp"
#include "CommandContext.hpp" 

/**
 * @class CatalogInnerJoinCommand
 * @brief Command to perform an inner join operation between two tables in the catalog.
 *
 * This command facilitates combining rows from two distinct tables based on a
 * matching condition between specified columns in each table. It generates
 * a new table containing only the rows where the join condition is met, and
 * saves this result to a new file.
 */
class CatalogInnerJoinCommand : public Command {
private:
	/// Reference to the shared command execution context, providing access to the loaded catalog and I/O utilities.
	CommandContext& context;
public:
	/**
	* @brief Constructs a CatalogInnerJoinCommand instance.
	*
	* @param context A reference to the `CommandContext` object, which encapsulates
	* the application's shared database catalog, file writers, and console output handlers.
	*/
	CatalogInnerJoinCommand(CommandContext& context);

    /**
     * @brief Executes the 'innerjoin' command, combining two tables based on a key.
     *
     * This method performs an inner join operation between two specified tables (`tableName1`, `tableName2`)
     * based on equality of values in their respective join columns (`column1`, `column2`).
     * The resulting joined table will include all columns from `tableName1` followed by
     * all columns from `tableName2`, excluding the join column from `tableName2` to avoid redundancy.
     * The new joined table is then saved to a file named 'inner_join_of_[table1_name]_and_[table2_name].csv'
     * in the same directory as the first table.
     *
     * @param params A constant reference to a vector of strings representing command-line parameters.
     * Expected format:
     * - `params[0]`: "innerjoin" (command name)
     * - `params[1]`: Name of the first table.
     * - `params[2]`: 0-indexed integer position of the join column in the first table.
     * - `params[3]`: Name of the second table.
     * - `params[4]`: 0-indexed integer position of the join column in the second table.
     *
     * @throws std::runtime_error If no catalog is currently loaded.
     * @throws std::runtime_error If the number of parameters is incorrect (not 5).
     * @throws std::runtime_error If `params[2]` or `params[4]` cannot be converted to an integer.
     * @throws std::runtime_error If either specified table does not exist in the catalog.
     * @throws std::out_of_range If `column1` is out of bounds for `tableName1` or `column2` is out of bounds for `tableName2`.
     * @throws std::runtime_error If the data types of the join columns (`column1` and `column2`) are incompatible.
     * @throws std::exception Any other exceptions propagated during table processing or file writing
     * (e.g., file creation/write errors, permissions issues, invalid path).
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