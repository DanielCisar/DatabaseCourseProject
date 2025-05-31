#pragma once
#include "Command.hpp"
#include "CommandContext.hpp"

/**
 * @class CatalogInsertCommand
 * @brief Command to insert a new row of data into a specified table.
 *
 * This command allows users to add a new record to an existing table in the
 * loaded database catalog. It requires the table name and a list of values,
 * which must correspond to the number and types of columns in the table.
 */
class CatalogInsertCommand : public  Command {
private:
	/// Reference to the shared command execution context, providing access to the loaded catalog and I/O utilities.
	CommandContext& context;
public:
	/**
	* @brief Constructs a CatalogInsertCommand instance.
	*
	* @param context A reference to the `CommandContext` object, which encapsulates
	* the application's shared database catalog and console output handler.
	*/
	CatalogInsertCommand(CommandContext& context);

    /**
     * @brief Executes the 'insert' command, adding a new row to a table.
     *
     * This method adds a new row of data to the table identified by `params[1]`.
     * The values for the new row are taken from `params[2]` onwards.
     * The number of provided values must exactly match the number of columns
     * in the target table. Each value is added to its corresponding column,
     * potentially involving type conversion based on the column's type.
     *
     * @param params A constant reference to a vector of strings representing command-line parameters.
     * Expected format:
     * - `params[0]`: "insert" (command name)
     * - `params[1]`: The name of the table into which the row will be inserted.
     * - `params[2]`...`params[N]`: The values for each column in the new row,
     * in order corresponding to the table's columns.
     *
     * @throws std::runtime_error If no catalog is currently loaded.
     * @throws std::runtime_error If the number of parameters is insufficient (less than 2).
     * @throws std::runtime_error If the specified table does not exist in the catalog.
     * @throws std::runtime_error If the number of provided values does not match the number of columns in the table.
     * @throws std::exception Any exceptions propagated from `TableColumn::addCell`
     * (e.g., invalid format for type conversion, such as trying to insert "abc" into an Integer column).
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