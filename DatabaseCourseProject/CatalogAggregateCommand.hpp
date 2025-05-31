#pragma once
#include "Command.hpp"
#include "CommandContext.hpp"

/**
 * @class CatalogAggregateCommand
 * @brief Performs aggregate calculations (sum, product, minimum, maximum) on numeric column values in a table.
 *
 * This command allows users to perform aggregate operations on a specified
 * target column within a table. The aggregation is conditionally applied
 * only to rows that meet a defined search criterion on a different (or the same) column.
 * The result of the aggregation is then printed to the console.
 */
class CatalogAggregateCommand : public Command {
private:
    /// Reference to the shared command execution context
    CommandContext& context;

public:
    /**
     * @brief Constructs a CatalogAggregateCommand instance.
     *
     * @param context A reference to the `CommandContext` object, which encapsulates
     * the application's shared database catalog and I/O utility handlers.
     */
    CatalogAggregateCommand(CommandContext& context);

    /**
    * @brief Executes the aggregate command, performing calculations on matching rows.
    *
    * This method takes a table name, a search column index, a search value, a target
    * column index (for aggregation), and the desired operation. It filters rows
    * based on the search condition and then applies the aggregate operation
    * (sum, product, minimum, or maximum) to the values in the specified target column
    * of those matching rows. The final result is printed to the console.
    *
    * @param params A constant reference to a vector of strings representing command-line parameters.
    * Expected format:
    * - `params[0]`: "aggregate" (command name)
    * - `params[1]`: Name of the table to perform aggregation on.
    * - `params[2]`: Index of the column to use for the search condition (0-indexed).
    * - `params[3]`: Value to match in the search column.
    * - `params[4]`: Index of the column on which the aggregation will be performed (0-indexed).
    * - `params[5]`: The aggregation operation to perform ("sum", "product", "minimum", or "maximum").
    *
    * @throws std::runtime_error If no catalog is currently loaded.
    * @throws std::runtime_error If the number of parameters is incorrect (not 6).
    * @throws std::runtime_error If the specified table does not exist.
    * @throws std::out_of_range If the search column index or target column index is invalid (out of bounds).
    * @throws std::runtime_error If the target column is not of a numeric type (Integer or Double).
    * @throws std::runtime_error If a non-numeric value is found in the target column during aggregation.
    * @throws std::runtime_error If no rows match the search criterion.
    * @throws std::invalid_argument If an unknown aggregation operation is specified.
    * @throws std::exception Any other exceptions propagated from underlying operations (e.g., `std::stoi`).
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