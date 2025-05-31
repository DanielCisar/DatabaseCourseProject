#pragma once
#include "TableColumn.hpp"
#include <vector>
#include <string>

/**
 * @class DoubleColumn
 * @brief Concrete implementation of `TableColumn` for storing double-precision floating-point data.
 *
 * This class manages a column of `double` values, including support for NULL values.
 * It provides methods for accessing, modifying, adding, and deleting cells,
 * performing necessary string-to-double conversions. It strictly adheres to the
 * polymorphic interface defined by the `TableColumn` base class.
 * NULL values are typically represented internally by a default value (e.g., 0.0)
 * in `content` and a corresponding `true` in the `isNull` boolean vector.
 */
class DoubleColumn : public TableColumn {
private:
	std::vector<double> content;  ///< Stores the actual double values of the column. Default value (0.0) for NULL.
	std::vector<bool> isNull;     ///< Stores a boolean flag for each cell, indicating if it's a NULL value.
	std::string name;             ///< The name of this column.

public:
    /**
     * @brief Constructs a new DoubleColumn with a specified name.
     *
     * The column is initialized as empty (containing no rows).
     *
     * @param name The name to assign to this column.
     */
    DoubleColumn(std::string name);

    /**
     * @brief Copy constructor for DoubleColumn.
     *
     * Performs a deep copy of the `content`, `isNull`, and `name` from another DoubleColumn instance.
     *
     * @param other The DoubleColumn object to copy from.
     */
    DoubleColumn(const DoubleColumn& other);

    /**
     * @brief Destructor for DoubleColumn.
     *
     * Manages the deallocation of resources (vectors) used by the column.
     * (Default implementation is sufficient for `std::vector`).
     */
    ~DoubleColumn() override; // Mark as override

    /**
     * @brief Copy assignment operator for DoubleColumn.
     *
     * Performs a deep copy of the `content`, `isNull`, and `name` from another
     * DoubleColumn instance to this object. Handles self-assignment correctly.
     *
     * @param other The DoubleColumn object to assign from.
     * @return A reference to this DoubleColumn object after assignment.
     */
    DoubleColumn& operator=(const DoubleColumn& other);

    /**
     * @brief Retrieves the name of the column.
     * @return The name of the column.
     */
    std::string getName() const override;

    /**
     * @brief Retrieves the data type of the column.
     * @return `ColumnType::DOUBLE`, indicating this is a double-precision floating-point column.
     */
    ColumnType getType() const override;

    /**
     * @brief Retrieves a constant reference to the underlying vector of double content.
     * @return A constant reference to the `std::vector<double>` containing the column's data.
     * @note This method is specific to `DoubleColumn` and not part of the `TableColumn` interface.
     */
    const std::vector<double>& getContent() const; // Added const

    /**
     * @brief Retrieves the double value of a cell at a specific index.
     *
     * @param index The 0-indexed position of the cell whose value is to be retrieved.
     * @return The double value of the cell.
     * @throws std::runtime_error If the provided `index` is out of the column's bounds.
     * @throws std::runtime_error If the value at the given `index` is NULL. This method does not return a default value for NULLs.
     * @note This method is specific to `DoubleColumn` and not part of the `TableColumn` interface.
     */
    double getValueAtGivenIndex(int index) const; // Added const

    /**
     * @brief Changes the value of a cell at a specific index.
     *
     * The provided string `val` is converted to a `double` using `std::stod`.
     * If `val` is an empty string `""`, the cell is marked as NULL (internally stored as 0.0).
     * Otherwise, the converted double value is stored.
     *
     * @param index The 0-indexed position of the cell whose value is to be changed.
     * @param val The new value for the cell, provided as a string. An empty string `""` implies NULL.
     * @throws std::runtime_error If the provided `index` is out of the column's bounds.
     * @throws std::invalid_argument If the `val` string cannot be converted to a valid double.
     * @throws std::out_of_range If the converted double value is out of the range of `double`.
     */
    void changeValueAtIndex(int index, std::string val) override;

    /**
     * @brief Adds a new cell (row entry) to the end of the column.
     *
     * The provided string `cell` is converted to a `double` using `std::stod`.
     * If `cell` is an empty string `""`, the new cell is added as NULL (internally stored as 0.0).
     * Otherwise, the converted double value is added. This operation increases
     * the column's size by one.
     *
     * @param cell The value for the new cell, provided as a string. An empty string `""` implies NULL.
     * @throws std::invalid_argument If the `cell` string cannot be converted to a valid double.
     * @throws std::out_of_range If the converted double value is out of the range of `double`.
     */
    void addCell(std::string cell) override;

    /**
     * @brief Deletes a cell (row entry) at a specified index from the column.
     *
     * This operation removes the double content and its corresponding NULL flag
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
     * This method fulfills the `TableColumn` interface contract. If the cell at the
     * given `index` is NULL, an empty string `""` is returned. Otherwise, the double
     * value is converted to its string representation.
     *
     * @param index The 0-indexed position of the cell whose value is to be retrieved.
     * @return The string representation of the cell's value. Returns `""` if the value is NULL.
     * @throws std::runtime_error If the provided `index` is out of the column's bounds.
     */
    std::string returnValueAtGivenIndexAsString(int index) const override;

    /**
     * @brief Retrieves the name of the column's data type as a human-readable string.
     * @return The string "Double".
     */
    std::string getTypeAsString() const override;

    /**
     * @brief Checks if the value of a cell at a given row index matches a specified string value.
     *
     * This method handles NULL values: a NULL cell in the column is considered a match
     * if the provided `value` is also an empty string `""`.
     * For non-NULL cells, the provided `value` string is attempted to be converted to a `double`.
     * If conversion is successful, a numeric comparison is performed. If conversion fails,
     * it is considered a non-match.
     *
     * @param rowIndex The 0-indexed position of the cell to compare.
     * @param value The string value to match against. An empty string `""` matches NULL.
     * @return `true` if the cell's value matches (including NULL-to-empty-string match) or
     * if the numeric conversion and comparison succeed; `false` otherwise (e.g., on conversion failure).
     * @throws std::runtime_error If the provided `rowIndex` is out of the column's bounds.
     */
    bool matchesValues(int rowIndex, const std::string& value) const override;

    /**
     * @brief Fills the column with a specified number of NULL (default double 0.0) values.
     *
     * This method appends `size` number of new cells to the column. Each new cell
     * will have a default double value (0.0) as its content and its `isNull` flag set to `true`.
     * This is useful for initializing new columns in existing tables.
     *
     * @param size The number of NULL values to add to the column.
     */
    void fillColumnWithNULL(int size) override;

    /**
     * @brief Creates a deep copy of the current `DoubleColumn` object.
     *
     * This method ensures that a new, independent `DoubleColumn` instance,
     * containing a full copy of its content and null flags, is created.
     *
     * @return A pointer to a newly allocated `DoubleColumn` object, which is a deep copy of this instance.
     * @warning The caller is responsible for `delete`ing the returned pointer to prevent memory leaks.
     */
    TableColumn* clone() const override;

};