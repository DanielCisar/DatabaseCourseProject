#pragma once
#include "Command.hpp"
#include "CommandContext.hpp"

/**
 * @class CatalogDescribeCommand
 * @brief Command to display the schema (column types) of a specified table.
 *
 * This command allows users to inspect the structure of a table loaded in the
 * current database catalog. It lists each column's type, helping users
 * understand the data types stored within the table.
 */
class CatalogDescribeCommand : public  Command {
private:
	/// Reference to the shared command execution context, providing access to the loaded catalog and I/O utilities.
	CommandContext& context;
public:
	/**
	* @brief Constructs a CatalogDescribeCommand instance.
	*
	* @param context A reference to the `CommandContext` object, which encapsulates
	* the application's shared database catalog and console output handler.
	*/
	CatalogDescribeCommand(CommandContext& context);

    /**
     * @brief Executes the 'describe' command, showing a table's column types.
     *
     * This method retrieves the specified table from the loaded catalog and
     * then iterates through all its columns. For each column, it prints
     * its data type to the console. The columns are listed with a 1-based index
     * for user readability.
     *
     * @param params A constant reference to a vector of strings representing command-line parameters.
     * Expected format:
     * - `params[0]`: "describe" (command name)
     * - `params[1]`: The name of the table whose schema is to be described.
     *
     * @throws std::runtime_error If no catalog is currently loaded.
     * @throws std::runtime_error If the number of parameters is incorrect (not 2).
     * @throws std::runtime_error If the specified table does not exist in the catalog.
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