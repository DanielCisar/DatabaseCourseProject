#pragma once
#include <vector>
#include <string>
#include "ColumnType.hpp"

/**
 * @class TableColumn
 * @brief Abstract base class for all column types in a database table.
 *
 * This abstract class defines the common interface and fundamental operations
 * that all concrete column implementations (e.g., `IntegerColumn`, `DoubleColumn`,
 * `StringColumn`) must provide. It ensures polymorphic behavior, allowing
 * tables to manage columns of various data types uniformly.
 */
class TableColumn {
public:
    /**
     * @brief Virtual destructor.
     *
     * Ensures that memory allocated for derived `TableColumn` objects is
     * properly deallocated when deleted via a `TableColumn` pointer,
     * preventing memory leaks.
     */
    virtual ~TableColumn() = default;

    /**
     * @brief Retrieves the name of the column.
     * @return A constant string reference representing the column's name.
     */
    virtual std::string getName() const = 0;

    /**
     * @brief Retrieves the data type of the column.
     * @return A `ColumnType` enum value indicating the column's data type (e.g., INTEGER, DOUBLE, STRING).
     */
    virtual ColumnType getType() const = 0;

    /**
     * @brief Deletes a cell (row entry) at a specified index from the column.
     *
     * This operation removes the data point at the given `index`, effectively
     * shortening the column's content.
     *
     * @param index The 0-indexed position of the cell to delete.
     * @throws std::out_of_range If the provided `index` is out of the column's bounds.
     */
    virtual void deleteCell(int index) = 0;

    /**
     * @brief Returns the number of cells (rows) currently in the column.
     * @return An integer representing the current size of the column.
     */
    virtual int getSize() = 0;

    /**
     * @brief Retrieves the value of a cell at a specific index, formatted as a string.
     *
     * This method provides a universal way to access column data, regardless of its
     * native type, by converting it to its string representation.
     *
     * @param index The 0-indexed position of the cell whose value is to be retrieved.
     * @return A string representation of the cell's value.
     * @throws std::out_of_range If the provided `index` is out of the column's bounds.
     */
    virtual std::string returnValueAtGivenIndexAsString(int index) const = 0;

    /**
     * @brief Changes the value of a cell at a specific index.
     *
     * The provided string `val` will be converted to the column's native data type
     * before being stored.
     *
     * @param index The 0-indexed position of the cell whose value is to be changed.
     * @param val The new value for the cell, provided as a string.
     * @throws std::out_of_range If the provided `index` is out of the column's bounds.
     * @throws std::invalid_argument If the `val` string cannot be converted to the column's native data type.
     */
    virtual void changeValueAtIndex(int index, std::string val) = 0;

    /**
     * @brief Adds a new cell (row entry) to the end of the column.
     *
     * The provided string `cell` will be converted to the column's native data type
     * before being stored. This operation increases the column's size by one.
     *
     * @param cell The value for the new cell, provided as a string.
     * @throws std::invalid_argument If the `cell` string cannot be converted to the column's native data type.
     */
    virtual void addCell(std::string cell) = 0;

    /**
     * @brief Retrieves the name of the column's data type as a human-readable string.
     * @return A string representing the column's type (e.g., "String", "Integer", "Double").
     */
    virtual std::string getTypeAsString() const = 0;

    /**
     * @brief Checks if the value of a cell at a given row index matches a specified string value.
     *
     * This method performs a comparison, typically after converting the cell's native
     * value to a string, to determine if it matches the provided `value`.
     *
     * @param rowIndex The 0-indexed position of the cell to compare.
     * @param value The string value to match against the cell's content.
     * @return `true` if the cell's value matches the provided string; `false` otherwise.
     * @throws std::out_of_range If the provided `rowIndex` is out of the column's bounds.
     */
    virtual bool matchesValues(int rowIndex, const std::string& value) const = 0;

    /**
     * @brief Fills the column with a specified number of NULL (empty) values.
     *
     * This is typically used when adding a new column to an existing table,
     * ensuring that all existing rows have an entry in the new column.
     *
     * @param size The number of NULL values to add to the column.
     */
    virtual void fillColumnWithNULL(int size) = 0;

    /**
     * @brief Creates a deep copy of the current `TableColumn` object.
     *
     * This method ensures that a new, independent instance of the concrete column type
     * (and all its internal data) is created, allowing for safe copying of tables
     * without shallow copy issues. The caller is responsible for managing the
     * memory of the returned pointer.
     *
     * @return A pointer to a newly allocated `TableColumn` object which is a deep copy of the current instance.
     * @warning The caller is responsible for `delete`ing the returned pointer to prevent memory leaks.
     */
    virtual TableColumn* clone() const = 0;
};
