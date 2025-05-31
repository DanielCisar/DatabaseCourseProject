#pragma once
#include "Command.hpp"
#include "CommandContext.hpp"

/**
 * @class CatalogCountCommand
 * @brief Command to count rows in a table that satisfy a specific column-value condition.
 *
 * This command enables users to query a table and determine how many rows
 * have a particular value in a designated column. The result, which is the
 * total count of matching rows, is displayed to the console.
 */
class CatalogCountCommand : public Command {
private:
    /// Reference to the command context (shared environment and resources)
    CommandContext& context;

public:
    /**
     * @brief Constructs a CatalogCountCommand instance.
     *
     * @param context A reference to the `CommandContext` object, which encapsulates
     * the application's shared database catalog and I/O utility handlers.
     */
    CatalogCountCommand(CommandContext& context);

    /**
    * @brief Executes the count command, determining the number of matching rows.
    *
    * This method counts the occurrences of a specified `searchValue` within a
    * `searchColumnIndex` of a given `tableName`. It retrieves the table from
    * the loaded catalog, iterates through the relevant column, and increments
    * a counter for each cell that matches the criteria. The final count is
    * then printed to the console.
    *
    * @param params A constant reference to a vector of strings representing command-line parameters.
    * Expected format:
    * - `params[0]`: "count" (command name)
    * - `params[1]`: The name of the table to perform the count operation on.
    * - `params[2]`: The 0-indexed integer position of the column to search within.
    * - `params[3]`: The value (as a string) to match against cells in the specified column.
    *
    * @throws std::runtime_error If no catalog is currently loaded.
    * @throws std::runtime_error If the number of parameters is incorrect (not 4).
    * @throws std::runtime_error If the specified table does not exist in the catalog.
    * @throws std::out_of_range If `params[2]` cannot be converted to an integer, or if the
    * resulting `searchColumnIndex` is out of bounds for the table.
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