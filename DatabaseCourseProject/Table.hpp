#pragma once
#include <string>
#include <vector>
#include "TableColumn.hpp"

/**
 * @class Table
 * @brief Represents a single table within the database catalog, holding a collection of columns.
 *
 * The `Table` class manages the structure and data of a database table. It
 * internally holds a collection of polymorphic `TableColumn` pointers,
 * effectively owning the column objects and being responsible for their
 * memory management (deep copying on copy/assignment, deletion on destruction).
 * It provides functionalities for accessing column and row data, modifying
 * the table structure, and iterating over its columns.
 */
class Table {
private:
	/**
	* @brief A vector of pointers to `TableColumn` objects.
	*
	* This vector stores the actual columns of the table. The `Table` class
	* takes ownership of these pointers and is responsible for their memory
	* management (allocation and deallocation).
	*/
	std::vector<TableColumn*> columns;

	std::string name;  ///< The logical name of the table within the catalog.
	std::string filename; ///< The file path on disk where this table's data is or will be stored (e.g., "my_table.csv").

    /**
    * @brief Helper function to clean up dynamically allocated column pointers.
    * Iterates through `columns` and `delete`s each `TableColumn*`, then clears the vector.
    */
    void clearColumnsMemory();
public:
	/**
	* @brief Constructs a new Table instance.
	*
	* This constructor takes a vector of `TableColumn*` and takes ownership of them.
	* It is expected that these column pointers are newly allocated.
	*
	* @param columns A vector of pointers to `TableColumn` objects that will form this table's structure.
	* The `Table` assumes ownership of these pointers.
	* @param name The logical name of the table.
	* @param filename The file path on disk associated with this table.
	*/
	Table(const std::vector<TableColumn*> columns, const std::string name, const std::string filename);

	/**
	* @brief Copy constructor for Table.
	*
	* Performs a deep copy of all `TableColumn` objects contained in the `other` table's
	* `columns` vector by calling `TableColumn::clone()` for each, ensuring
	* independent copies.
	*
	* @param other The Table object to copy from.
	*/
	Table(const Table& other);

	/**
	* @brief Destructor for Table.
	*
	* Iterates through the `columns` vector and `delete`s each `TableColumn` pointer
	* to prevent memory leaks, as the `Table` class owns these dynamically allocated objects.
	*/

    /**
    * @brief Move constructor for Table.
    *
    * Constructs a new Table object by efficiently transferring ownership of
    * `TableColumn` pointers and `name`/`filename` data from a temporary
    * or expiring `other` Table object. This avoids expensive deep copies.
    * The `other` object is left in a valid, but unspecified (typically empty),
    * state suitable for destruction.
    *
    * @param other The Table object to be moved from (an rvalue reference).
    */
    Table(Table&& other) noexcept;

    /**
    * @brief Destructor for Table.
    *
    * Calls `clearColumnsMemory()` to iterate through the `columns` vector and
    * `delete`s each `TableColumn` pointer to prevent memory leaks, as the `Table`
    * class owns these dynamically allocated objects.
    */
	~Table();

	/**
	 * @brief Copy assignment operator for Table.
	 *
	 * Handles deep copying of the `columns` vector and updates the `name` and `filename`.
	 * It correctly manages existing column memory (deletes old columns before copying new ones)
	 * and protects against self-assignment.
	 *
	 * @param other The Table object to assign from.
	 * @return A reference to this Table object after assignment.
	 */
	Table& operator=(const Table& other);

	using iterator = std::vector<TableColumn*>::iterator;
	using const_iterator = std::vector<TableColumn*>::const_iterator;

    /**
     * @brief Move assignment operator for Table.
     *
     * Efficiently transfers ownership of `TableColumn` pointers and `name`/`filename`
     * data from a temporary or expiring `other` Table object to the current
     * Table object. This operation frees any resources currently held by `*this`,
     * then moves resources from `other`. Self-assignment is handled.
     * The `other` object is left in a valid, but unspecified (typically empty),
     * state suitable for destruction.
     *
     * @param other The Table object to be moved from (an rvalue reference).
     * @return A reference to the current Table object (`*this`) after the move.
     */
    Table& operator=(Table&& other) noexcept;

	/**
	 * @brief Provides a non-const iterator to the beginning of the `columns` vector.
	 * @return An iterator pointing to the first `TableColumn*`.
	 */
    iterator begin();

	/**
	* @brief Provides a non-const iterator to the end of the `columns` vector.
	* @return An iterator pointing one past the last `TableColumn*`.
	*/
    iterator end();

	/**
	 * @brief Provides a const iterator to the beginning of the `columns` vector.
	 * @return A const iterator pointing to the first `TableColumn*`.
	 */
    const_iterator begin() const;

	/**
	 * @brief Provides a const iterator to the end of the `columns` vector.
	 * @return A const iterator pointing one past the last `TableColumn*`.
	 */
    const_iterator end() const;

	/**
	* @brief Retrieves the logical name of the table.
	* @return The table's name as a string.
	*/
	std::string getName() const;

	/**
	 * @brief Retrieves the file path on disk associated with this table.
	 * @return The table's filename as a string.
	 */
	std::string getFilename() const;

    /**
         * @brief Retrieves the name of the column at a given index.
         * @param index The 0-indexed position of the column.
         * @return The name of the column.
         * @throws std::runtime_error If the `index` is out of bounds for the `columns` vector.
         */
    std::string getColumnNameAtGivenIndex(int index) const;

    /**
     * @brief Retrieves a specific row of data as a formatted string.
     *
     * This method concatenates the string representations of all cells in the
     * specified row, typically separated by spaces.
     *
     * @param index The 0-indexed position of the row to retrieve.
     * @return A string representing the entire row.
     * @throws std::runtime_error If the `index` is out of bounds for the table's rows (based on column size).
     * @throws std::runtime_error If the table has no columns when attempting to determine row size.
     */
    std::string getRowAsString(int index) const;

    /**
     * @brief Deletes a row at a specified index from all columns in the table.
     *
     * This operation iterates through all `TableColumn` objects and calls
     * `TableColumn::deleteCell()` on each at the given `index`, effectively
     * removing a full row from the table.
     *
     * @param index The 0-indexed position of the row to delete.
     * @throws std::runtime_error If the `index` is out of bounds for the table's rows.
     * @throws std::runtime_error If the table has no columns.
     */
    void deleteGivenRow(int index);

    /**
     * @brief Adds a new column to the table.
     *
     * The `Table` takes ownership of the provided `TableColumn*`. It is expected
     * that the new column's size matches the existing number of rows in the table,
     * or that `fillColumnWithNULL` has been appropriately called on it prior to addition.
     *
     * @param col A pointer to the `TableColumn` object to add. The `Table` assumes ownership.
     */
    void addColumn(TableColumn* col);

    /**
     * @brief Returns the total number of columns in the table.
     * @return An integer representing the count of columns.
     */
    int getNumberOfColumns() const;

    /**
     * @brief Sets or updates the file path associated with this table.
     * @param filename The new file path for the table.
     */
    void setTablePath(const std::string& filename);

    /**
     * @brief Retrieves a pointer to the `TableColumn` object at a given index.
     * @param index The 0-indexed position of the column to retrieve.
     * @return A pointer to the `TableColumn` object.
     * @throws std::runtime_error If the `index` is out of bounds for the `columns` vector.
     */
    TableColumn* getColumnAtGivenIndex(int index) const;

    /**
     * @brief Sets or updates the logical name of the table.
     * @param name The new name for the table.
     * @note This directly changes the `Table` object's name. If the `Catalog`
     * class relies on unique table names as keys in an internal map,
     * an external mechanism in `Catalog` might be required to update
     * its internal mapping for full consistency (e.g., a `Catalog::renameTable` method).
     */
    void setName(const std::string& name);

    /**
     * @brief Generates a string representation of the entire table's data.
     *
     * This method constructs a multi-line string where each line represents a row.
     * Cell values within a row are separated by spaces.
     *
     * @return A string containing all rows of the table, or an empty string if the table has no columns or no rows.
     * @note It assumes all columns have the same number of rows.
     */
    std::string toString() const;

    /**
     * @brief Creates a deep copy of the current Table object with a new name and path.
     *
     * This method is essential for operations like "saveas" where the table
     * structure and data need to be duplicated to a new location without
     * affecting the original table in memory. It performs a deep copy of all
     * `TableColumn` objects by calling `TableColumn::clone()` for each.
     *
     * @param newName The name to assign to the cloned table.
     * @param newPath The file path to associate with the cloned table.
     * @return A new `Table` object that is a deep copy of the current instance,
     * but with the specified new name and file path.
     */
    Table cloneWithNewNameAndPath(const std::string& newName, const std::string& newPath) const;
};
