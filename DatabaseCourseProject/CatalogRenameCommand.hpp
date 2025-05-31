#pragma once
#include "Command.hpp"
#include "CommandContext.hpp"

/**
 * @class CatalogRenameCommand
 * @brief Command to rename an existing table within the loaded catalog.
 *
 * This command allows users to change the name of a specific table that is
 * currently loaded in the application's database catalog.
 * The operation updates the table's identifier in memory.
 */
class CatalogRenameCommand : public  Command {
private:
	/// Reference to the shared command execution context, providing access to the loaded catalog and I/O utilities.
	CommandContext& context;
public:
	/**
	 * @brief Constructs a CatalogRenameCommand instance.
	 *
	 * @param context A reference to the `CommandContext` object, which encapsulates
	 * the application's shared database catalog and console output handler.
	 */
	CatalogRenameCommand(CommandContext& context);

    /**
	* @brief Executes the 'rename' command, changing a table's name.
	*
	* This method renames a table from `oldName` to `newName` within the
	* `context.loadedCatalog`. It retrieves the table by its current name
	* and updates its internal name property. A confirmation message is printed
	* to the console upon successful renaming.
	*
	* @param params A constant reference to a vector of strings representing command-line parameters.
	* Expected format:
	* - `params[0]`: "rename" (command name)
	* - `params[1]`: The current name of the table to be renamed.
	* - `params[2]`: The new name for the table.
	*
	* @throws std::runtime_error If no catalog is currently loaded.
	* @throws std::runtime_error If the number of parameters is incorrect (not 3).
	* @throws std::runtime_error If the table with `oldName` does not exist in the catalog.
	* @throws std::exception Any other unexpected exceptions propagated from underlying operations.
	*
	* @note This command directly changes the table's name property. If the `Catalog`
	* class relies on unique table names as keys in an internal map,
	* an external mechanism in `Catalog` might be required to update
	* its internal mapping for full consistency (e.g., a `Catalog::renameTable` method).
	* As implemented, it only changes the `Table` object's internal name.
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