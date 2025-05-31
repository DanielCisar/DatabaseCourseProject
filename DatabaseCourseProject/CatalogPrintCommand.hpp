#pragma once
#include "Command.hpp"
#include "CommandContext.hpp"

/**
 * @class CatalogPrintCommand
 * @brief Command to display the content of a specified table with pagination.
 *
 * This command allows users to view the data stored within a table loaded in
 * the current database catalog. It prints the table's header (name, column names,
 * and types) followed by its rows, presented in a paginated format for easy viewing
 * of large datasets.
 */
class CatalogPrintCommand : public  Command {
private:
	/// Reference to the shared command execution context, providing access to the loaded catalog and I/O utilities.
	CommandContext& context;
public:
	/**
	 * @brief Constructs a CatalogPrintCommand instance.
	 *
	 * @param context A reference to the `CommandContext` object, which encapsulates
	 * the application's shared database catalog and console I/O handlers.
	 */
	CatalogPrintCommand(CommandContext& context);

    /**
	* @brief Executes the 'print' command, displaying a table's data with pagination.
	*
	* This method retrieves the specified table from the loaded catalog. It then
	* prints the table's overall name, followed by its column names and their
	* respective data types as headers. Subsequently, all rows of the table are
	* fetched as strings and passed to `IOUtils::printInPageFormat` for paginated
	* output to the console. This allows users to browse large tables page by page.
	*
	* @param params A constant reference to a vector of strings representing command-line parameters.
	* Expected format:
	* - `params[0]`: "print" (command name)
	* - `params[1]`: The name of the table to be printed.
	*
	* @throws std::runtime_error If no catalog is currently loaded.
	* @throws std::runtime_error If the number of parameters is incorrect (not 2).
	* @throws std::runtime_error If the specified table does not exist in the catalog.
	* @throws std::exception Any other unexpected exceptions propagated from underlying operations
	* (e.g., during table data retrieval or I/O operations).
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