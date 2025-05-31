#pragma once
#include "TableColumn.hpp"
#include <vector>
#include <string>

/**
 * @class IntegerColumn
 * @brief Concrete implementation of `TableColumn` for storing integer data.
 *
 * This class manages a column of integer values, including support for NULL values.
 * It provides methods for accessing, modifying, adding, and deleting integer cells,
 * performing necessary string-to-integer conversions. It strictly adheres to the
 * polymorphic interface defined by the `TableColumn` base class.
 * NULL values are typically represented internally by a default value (e.g., 0)
 * in `content` and a corresponding `true` in the `isNull` boolean vector.
 */
class IntegerColumn : public TableColumn {
private:
	std::vector<int> content;     ///< Stores the actual integer values of the column. Default value (0) for NULL.
	std::vector<bool> isNull;     ///< Stores a boolean flag for each cell, indicating if it's a NULL value.
	std::string name;             ///< The name of this column.

public:
    /**
     * @brief Constructs a new IntegerColumn with a specified name.
     *
     * The column is initialized as empty (containing no rows).
     *
     * @param name The name to assign to this column.
     */
    IntegerColumn(std::string name);

    /**
     * @brief Copy constructor for IntegerColumn.
     *
     * Performs a deep copy of the `content`, `isNull`, and `name` from another IntegerColumn instance.
     *
     * @param other The IntegerColumn object to copy from.
     */
    IntegerColumn(const IntegerColumn& other);

    /**
     * @brief Destructor for IntegerColumn.
     *
     * Manages the deallocation of resources (vectors) used by the column.
     * (Default implementation is sufficient for `std::vector`).
     */
    ~IntegerColumn() override; // Mark as override

    /**
     * @brief Copy assignment operator for IntegerColumn.
     *
     * Performs a deep copy of the `content`, `isNull`, and `name` from another
     * IntegerColumn instance to this object. Handles self-assignment correctly.
     *
     * @param other The IntegerColumn object to assign from.
     * @return A reference to this IntegerColumn object after assignment.
     */
    IntegerColumn& operator=(const IntegerColumn& other);

    /**
     * @brief Retrieves the name of the column.
     * @return The name of the column.
     */
    std::string getName() const override;

    /**
     * @brief Retrieves the data type of the column.
     * @return `ColumnType::INTEGER`, indicating this is an integer column.
     */
    ColumnType getType() const override;

    /**
     * @brief Retrieves a constant reference to the underlying vector of integer content.
     * @return A constant reference to the `std::vector<int>` containing the column's data.
     * @note This method is specific to `IntegerColumn` and not part of the `TableColumn` interface.
     */
    const std::vector<int>& getContent() const; // Added const

    /**
     * @brief Retrieves the integer value of a cell at a specific index.
     *
     * @param index The 0-indexed position of the cell whose value is to be retrieved.
     * @return The integer value of the cell.
     * @throws std::runtime_error If the provided `index` is out of the column's bounds.
     * @throws std::runtime_error If the value at the given `index` is NULL.
     * @note This method is specific to `IntegerColumn` and not part of the `TableColumn` interface.
     */
    int getValueAtGivenIndex(int index) const; // Added const

    /**
     * @brief Changes the value of a cell at a specific index.
     *
     * The provided string `val` is converted to an integer. If `val` is an empty
     * string `""`, the cell is marked as NULL (internally stored as 0).
     * Otherwise, the converted integer value is stored.
     *
     * @param index The 0-indexed position of the cell whose value is to be changed.
     * @param val The new value for the cell, provided as a string. An empty string `""` implies NULL.
     * @throws std::runtime_error If the provided `index` is out of the column's bounds.
     * @throws std::invalid_argument If the `val` string cannot be converted to a valid integer.
     * @throws std::out_of_range If the converted integer value is out of the range of `int`.
     */
    void changeValueAtIndex(int index, std::string val) override;

    /**
     * @brief Adds a new cell (row entry) to the end of the column.
     *
     * The provided string `cell` is converted to an integer. If `cell` is an empty
     * string `""`, the new cell is added as NULL (internally stored as 0).
     * Otherwise, the converted integer value is added. This operation increases
     * the column's size by one.
     *
     * @param cell The value for the new cell, provided as a string. An empty string `""` implies NULL.
     * @throws std::invalid_argument If the `cell` string cannot be converted to a valid integer.
     * @throws std::out_of_range If the converted integer value is out of the range of `int`.
     */
    void addCell(std::string cell) override;

    /**
     * @brief Deletes a cell (row entry) at a specified index from the column.
     *
     * This operation removes the integer content and its corresponding NULL flag
     * at the given `index`, effectively shortening the column's content.
     *
     * @param index The 0-indexed position of the cell to delete.
     * @throws std::runtime_error If the provided `index` is out of the column's bounds.
     */
    void deleteCell(int index) override;

    /**
     * @brief Returns the number of cells (rows) currently in the column.
     * @return An integer representing the current size of the column.
     */
    int getSize() override;

    /**
     * @brief Retrieves the value of a cell at a specific index, formatted as a string.
     *
     * If the cell at the given `index` is NULL, an empty string `""` is returned.
     * Otherwise, the integer value is converted to its string representation.
     *
     * @param index The 0-indexed position of the cell whose value is to be retrieved.
     * @return The string representation of the cell's value. Returns `""` if the value is NULL.
     * @throws std::runtime_error If the provided `index` is out of the column's bounds.
     */
    std::string returnValueAtGivenIndexAsString(int index) const override;

    /**
     * @brief Retrieves the name of the column's data type as a human-readable string.
     * @return The string "Integer".
     */
    std::string getTypeAsString() const override;

    /**
     * @brief Checks if the value of a cell at a given row index matches a specified string value.
     *
     * This method correctly handles NULL values: a NULL cell matches an empty string `""` value.
     * If the value is not NULL, the provided `value` string is converted to an integer for comparison.
     *
     * @param rowIndex The 0-indexed position of the cell to compare.
     * @param value The string value to match against the cell's content. An empty string `""` matches NULL.
     * @return `true` if the cell's value matches (including NULL-to-empty-string match) or conversion/comparison succeeds; `false` otherwise (e.g., on conversion failure).
     * @throws std::runtime_error If the provided `rowIndex` is out of the column's bounds.
     */
    bool matchesValues(int rowIndex, const std::string& value) const override;

    /**
     * @brief Fills the column with a specified number of NULL (default integer 0) values.
     *
     * This method appends `size` number of new cells to the column. Each new cell
     * will have a default integer value (0) as its content and its `isNull` flag set to `true`.
     * This is useful for initializing new columns in existing tables.
     *
     * @param size The number of NULL values to add to the column.
     */
    void fillColumnWithNULL(int size) override;

    /**
     * @brief Creates a deep copy of the current `IntegerColumn` object.
     *
     * This method ensures that a new, independent `IntegerColumn` instance,
     * containing a full copy of its content and null flags, is created.
     *
     * @return A pointer to a newly allocated `IntegerColumn` object, which is a deep copy of this instance.
     * @warning The caller is responsible for `delete`ing the returned pointer to prevent memory leaks.
     */
    TableColumn* clone() const override;

};