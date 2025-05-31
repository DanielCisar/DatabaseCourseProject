#pragma once
#include "Command.hpp"
#include "CommandContext.hpp"

/**
 * @class FileOpenCommand
 * @brief Command to open or create a database catalog file.
 *
 * This command handles loading a specified catalog file into the application's
 * memory. If the file does not exist, it creates a new empty catalog file.
 * Upon successful loading (or creation), the application's state is updated
 * to reflect the newly opened catalog, making it accessible for subsequent commands.
 */
class FileOpenCommand : public Command {
private:
	/// Reference to the shared command context used across all commands.
	CommandContext& context;
public:
	/**
	 * @brief Constructs a FileOpenCommand with the provided command context.
	 *
	 * @param context A reference to the command context containing shared components.
	 */
	FileOpenCommand(CommandContext& context);

	/**
	 * @brief Executes the "open" command.
	 *
	 * This method attempts to open a catalog file specified by the user.
	 * If the file does not exist, it will create an empty one at the given path.
	 * If the file exists, it reads the catalog data from it and loads it into
	 * the application's shared `Catalog` object. The application's state
	 * (`loadedCatalogExists`) is updated accordingly.
	 *
	 * @param params A constant reference to a vector of strings representing
	 * command-line parameters. Expected to contain exactly two elements:
	 * `params[0]` is the command name ("open"), and `params[1]` is
	 * the file path to the catalog to be opened or created.
	 *
	 * @throws std::runtime_error If the number of parameters is incorrect (not 2).
	 * @throws std::runtime_error If there's an issue creating a new empty file
	 * (e.g., due to permissions or invalid path).
	 * @throws std::exception (or more specific types) If `InputFileReader::readCatalogFromFile`
	 * encounters an error during file reading or parsing.
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