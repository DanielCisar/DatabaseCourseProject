#pragma once
#include "Command.hpp"
#include "CommandContext.hpp"

/**
 * @class CatalogAddColumnCommand
 * @brief Command to add a new column to an existing table in the loaded catalog.
 *
 * This command facilitates schema modification by allowing users to extend an
 * existing table with a new column. It requires the target table's name,
 * the desired name for the new column, and its data type. The newly added
 * column will be initialized with NULL (empty) values for all existing rows.
 */
class CatalogAddColumnCommand : public Command {
private:
    /// Reference to the command execution context (catalog, I/O utilities, etc.)
    CommandContext& context;

public:
    /**
     * @brief Constructs a CatalogAddColumnCommand instance.
     *
     * @param context A reference to the `CommandContext` object, which encapsulates
     * the application's shared database catalog and I/O utility handlers.
     */
    CatalogAddColumnCommand(CommandContext& context);

    /**
     * @brief Executes the add column command, modifying the specified table.
     *
     * This method adds a new column to the table identified by `params[1]`.
     * The new column will have the name specified in `params[2]` and the type
     * (String, Integer, or Double) specified in `params[3]`. For all existing
     * rows in the table, the new column will be populated with NULL values.
     *
     * @param params A constant reference to a vector of strings representing
     * command-line parameters. Expected format:
     * - `params[0]`: "addcolumn" (command name)
     * - `params[1]`: The name of the target table to which the column will be added.
     * - `params[2]`: The name for the new column.
     * - `params[3]`: The data type of the new column ("String", "Integer", or "Double").
     *
     * @throws std::runtime_error If no catalog is currently loaded.
     * @throws std::runtime_error If the number of parameters is incorrect (not 4).
     * @throws std::runtime_error If the specified table does not exist in the catalog.
     * @throws std::runtime_error If the provided column type string is invalid.
     * @throws std::exception Any other exceptions propagated from underlying
     * table/column operations (e.g., memory allocation issues).
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