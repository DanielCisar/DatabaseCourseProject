#pragma once
#include "Command.hpp"

/**
 * @class FileCloseCommand
 * @brief Command that handles closing the currently loaded file/catalog.
 *
 * This command resets the current catalog, effectively "closing" the session,
 * and provides user feedback through the console output writer.
 */
class FileCloseCommand : public Command {
private:
    /**
     * @brief Reference to the shared command execution context.
     *
     * Used to access the loaded catalog and I/O interfaces.
     */
    CommandContext& context;

public:
    /**
     * @brief Constructs the FileCloseCommand with a given context.
     *
     * @param context The shared command context which contains the catalog and I/O interfaces.
     */
    FileCloseCommand(CommandContext& context);

    /**
     * @brief Executes the file close operation.
     *
     * @param params Parameters passed to the command (ignored in this case).
     */
    void execute(const std::vector<std::string>& params) override;
};