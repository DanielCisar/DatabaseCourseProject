#pragma once
#include "Command.hpp"
#include "CommandContext.hpp" 

/**
 * @class CatalogShowTablesCommand
 * @brief Command to display a list of all tables currently loaded in the catalog.
 *
 * This command provides an overview of the tables available in the active
 * database catalog. It prints the name of each loaded table to the console.
 */
class CatalogShowTablesCommand : public  Command {
private:
	/// Reference to the shared command execution context, providing access to the loaded catalog and I/O utilities.
	CommandContext& context;
public:
	/**
	* @brief Constructs a CatalogShowTablesCommand instance.
	*
	* @param context A reference to the `CommandContext` object, which encapsulates
	* the application's shared database catalog and console output handler.
	*/
	CatalogShowTablesCommand(CommandContext& context);

    /**
     * @brief Executes the 'showtables' command, listing all loaded tables.
     *
     * This method displays a header "List of tables:" followed by the name
     * of each table currently present in the `context.loadedCatalog`.
     * Each table name is printed on a new line to the console.
     *
     * @param params A constant reference to a vector of strings representing command-line parameters.
     * Expected format:
     * - `params[0]`: "showtables" (command name)
     * This command does not accept any additional parameters.
     *
     * @throws std::runtime_error If no catalog is currently loaded.
     * @throws std::runtime_error If more than one parameter is provided (i.e., `params.size()` is not 1).
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