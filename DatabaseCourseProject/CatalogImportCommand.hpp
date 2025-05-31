#pragma once
#include "Command.hpp"
#include "CommandContext.hpp"

/**
 * @class CatalogImportCommand
 * @brief Command to import a new table from a file into the currently loaded catalog.
 *
 * This command allows users to load external table data, typically from a CSV file,
 * and integrate it into the application's in-memory database catalog. The imported
 * table becomes available for further operations within the application.
 */
class CatalogImportCommand : public  Command {
private:
	/// Reference to the shared command execution context, providing access to the loaded catalog and I/O utilities.
	CommandContext& context;
public:
	/**
	 * @brief Constructs a CatalogImportCommand instance.
	 *
	 * @param context A reference to the `CommandContext` object, which encapsulates
	 * the application's shared database catalog and I/O utility handlers.
	 */
	CatalogImportCommand(CommandContext& context);

    /**
	* @brief Executes the 'import' command, loading a table from a file.
	*
	* This method reads a table from the specified `filepath` and adds it to the
	* `context.loadedCatalog`. The imported table's name is derived from the
	* file's content (or is implicitly part of the Table object from `readTableFromFile`).
	* A success message is printed to the console upon successful import.
	*
	* @param params A constant reference to a vector of strings representing command-line parameters.
	* Expected format:
	* - `params[0]`: "import" (command name)
	* - `params[1]`: The file path to the table file (e.g., "data/employees.csv").
	*
	* @throws std::runtime_error If no catalog is currently loaded.
	* @throws std::runtime_error If the number of parameters is incorrect (not 2).
	* @throws std::exception Any exceptions propagated from `InputFileReader::readTableFromFile`
	* (e.g., file not found, read errors, parsing errors, invalid file format).
	* @throws std::runtime_error If a table with the same name already exists in the catalog (if `Catalog::addTable` enforces uniqueness).
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