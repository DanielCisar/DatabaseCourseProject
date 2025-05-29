#pragma once
#include "Command.hpp"

/**
 * @class FileOpenCommand
 * @brief Opens a file which then will be used when calling other commands.
 *
 * This command prints a list of available commands along with a brief description
 * of each, guiding the user on how to interact with the application.
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
	 * Reads a catalog from a file and loads it into the memory then assings it to loadedCatalog and marks that there is an open catalog.
	 *
	 * @param params Params contain just the filename where the catalog is stored.
	 */
	void execute(const std::vector<std::string>& params) override;
};