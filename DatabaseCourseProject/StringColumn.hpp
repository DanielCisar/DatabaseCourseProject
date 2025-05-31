#pragma once
#include "TableColumn.hpp"
#include <vector>
#include <string>

/**
 * @class StringColumn
 * @brief Concrete implementation of `TableColumn` for storing string data.
 *
 * This class manages a column of string values, including support for NULL values.
 * It provides methods for accessing, modifying, adding, and deleting string cells,
 * and adheres to the polymorphic interface defined by the `TableColumn` base class.
 * NULL values are represented internally by an empty string in `content` and
 * a corresponding `true` in the `isNull` boolean vector.
 */
class StringColumn : public TableColumn {
private:
    std::vector<std::string> content; ///< Stores the actual string values of the column. Empty string for NULL.
    std::vector<bool> isNull;        ///< Stores a boolean flag for each cell, indicating if it's a NULL value.
    std::string name;                ///< The name of this column.

public:
    /**
     * @brief Constructs a new StringColumn with a specified name.
     *
     * The column is initialized as empty (containing no rows).
     *
     * @param name The name to assign to this column.
     */
    StringColumn(std::string name);

    /**
     * @brief Copy constructor for StringColumn.
     *
     * Performs a deep copy of the `content`, `isNull`, and `name` from another StringColumn instance.
     *
     * @param other The StringColumn object to copy from.
     */
    StringColumn(const StringColumn& other);

    /**
     * @brief Destructor for StringColumn.
     *
     * Manages the deallocation of resources (vectors) used by the column.
     * (Default implementation is sufficient for `std::vector`).
     */
    ~StringColumn() override; // Mark as override

    /**
     * @brief Copy assignment operator for StringColumn.
     *
     * Performs a deep copy of the `content`, `isNull`, and `name` from another
     * StringColumn instance to this object. Handles self-assignment correctly.
     *
     * @param other The StringColumn object to assign from.
     * @return A reference to this StringColumn object after assignment.
     */
    StringColumn& operator=(const StringColumn& other);

    /**
     * @brief Retrieves the name of the column.
     * @return The name of the column.
     */
    std::string getName() const override;

    /**
     * @brief Retrieves the data type of the column.
     * @return `ColumnType::STRING`, indicating this is a string column.
     */
    ColumnType getType() const override;

    /**
     * @brief Retrieves a constant reference to the underlying vector of string content.
     * @return A constant reference to the `std::vector<std::string>` containing the column's data.
     * @note This method is specific to `StringColumn` and not part of the `TableColumn` interface.
     */
    const std::vector<std::string>& getContent() const; // Changed return to const& for efficiency

    /**
     * @brief Retrieves the value of a cell at a specific index.
     *
     * If the cell at the given index is NULL, an empty string is returned.
     *
     * @param index The 0-indexed position of the cell whose value is to be retrieved.
     * @return The string value of the cell. Returns an empty string `""` if the value is NULL.
     * @throws std::runtime_error If the provided `index` is out of the column's bounds.
     * @note This method is specific to `StringColumn` and not part of the `TableColumn` interface.
     */
    std::string getValueAtGivenIndex(int index) const; // Added const

    /**
     * @brief Changes the value of a cell at a specific index.
     *
     * If `val` is an empty string `""`, the cell is marked as NULL.
     * Otherwise, the `val` is stored as a regular string.
     *
     * @param index The 0-indexed position of the cell whose value is to be changed.
     * @param val The new value for the cell, provided as a string. An empty string `""` implies NULL.
     * @throws std::runtime_error If the provided `index` is out of the column's bounds.
     */
    void changeValueAtIndex(int index, std::string val) override;

    /**
     * @brief Adds a new cell (row entry) to the end of the column.
     *
     * If the provided `cell` string is empty `""`, the new cell is added as NULL.
     * Otherwise, the string is added as a regular value.
     * This operation increases the column's size by one.
     *
     * @param cell The value for the new cell, provided as a string. An empty string `""` implies NULL.
     */
    void addCell(std::string cell) override;

    /**
     * @brief Deletes a cell (row entry) at a specified index from the column.
     *
     * This operation removes the string content and its corresponding NULL flag
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
     * given `index` is NULL, an empty string `""` is returned.
     *
     * @param index The 0-indexed position of the cell whose value is to be retrieved.
     * @return The string representation of the cell's value. Returns `""` if the value is NULL.
     * @throws std::runtime_error If the provided `index` is out of the column's bounds.
     */
    std::string returnValueAtGivenIndexAsString(int index) const override;

    /**
     * @brief Retrieves the name of the column's data type as a human-readable string.
     * @return The string "String".
     */
    std::string getTypeAsString() const override;

    /**
     * @brief Checks if the value of a cell at a given row index matches a specified string value.
     *
     * This method correctly handles NULL values: a NULL cell matches an empty string `""` value.
     *
     * @param rowIndex The 0-indexed position of the cell to compare.
     * @param value The string value to match against the cell's content.
     * @return `true` if the cell's value (or its NULL status matching an empty string) matches the provided `value`; `false` otherwise.
     * @throws std::runtime_error If the provided `rowIndex` is out of the column's bounds.
     */
    bool matchesValues(int rowIndex, const std::string& value) const override;

    /**
     * @brief Fills the column with a specified number of NULL (empty) values.
     *
     * This is typically used when adding a new column to an existing table,
     * ensuring that all existing rows have an entry in the new column.
     * Each added cell will have an empty string content and its `isNull` flag set to `true`.
     *
     * @param size The number of NULL values to add to the column.
     */
    void fillColumnWithNULL(int size) override;

    /**
     * @brief Creates a deep copy of the current `StringColumn` object.
     *
     * This method ensures that a new, independent `StringColumn` instance,
     * containing a full copy of its content and null flags, is created.
     *
     * @return A pointer to a newly allocated `StringColumn` object, which is a deep copy of this instance.
     * @warning The caller is responsible for `delete`ing the returned pointer to prevent memory leaks.
     */
    TableColumn* clone() const override;
};