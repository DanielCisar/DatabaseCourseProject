#include "Table.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include "FileUtils.hpp"

/**
 * @brief Constructs a new Table instance.
 *
 * Initializes the table with the provided column pointers, name, and filename.
 * The `Table` takes ownership of the `TableColumn*` pointers passed in the
 * `columns` vector; it is assumed these are newly allocated and will be
 * managed by this `Table` instance's destructor.
 *
 * @param columns A vector of pointers to `TableColumn` objects. Ownership is transferred.
 * @param name The logical name of the table.
 * @param filename The file path associated with this table.
 */
Table::Table(const std::vector<TableColumn*> columns, const std::string name, const std::string filename)
    : columns(columns), 
    name(name),
    filename(filename) {
}

/**
 * @brief Copy constructor for Table.
 *
 * Performs a deep copy of all `TableColumn` objects from the `other` table.
 * For each column in `other.columns`, `TableColumn::clone()` is called to
 * create a new, independent copy of the column, which is then added to `this->columns`.
 * This ensures that changes to the copied table do not affect the original.
 *
 * @param other The Table object to copy from.
 */
Table::Table(const Table& other)
    : name(other.name), filename(other.filename) {
    for (const auto& col : other.columns) {
        this->columns.push_back(col->clone()); 
    }
}

/**
 * @brief Destructor for Table.
 *
 * Iterates through the `columns` vector and `delete`s each `TableColumn` pointer.
 * This is crucial for preventing memory leaks, as the `Table` class owns
 * these dynamically allocated column objects.
 */
Table::~Table() {
    for (TableColumn* column : columns) {
        delete column; 
    }
    columns.clear(); 
}

/**
 * @brief Copy assignment operator for Table.
 *
 * Provides strong exception safety using the copy-and-swap idiom (implicitly, as it uses the copy constructor).
 * It first clears existing columns and then performs a deep copy of the columns from `other`.
 * It also handles self-assignment correctly.
 *
 * @param other The Table object to assign from.
 * @return A reference to this Table object after assignment.
 */
Table& Table::operator=(const Table& other) {
    if (this != &other) { 
        for (auto& col_ptr : this->columns) {
            delete col_ptr;
        }
        this->columns.clear(); 

        for (const auto& col_ptr : other.columns) {
            this->columns.push_back(col_ptr->clone());
        }

        this->name = other.name;
        this->filename = other.filename;
    }
    return *this;
}

// Iterator definitions
/**
 * @brief Provides a non-const iterator to the beginning of the `columns` vector.
 * @return An iterator pointing to the first `TableColumn*`.
 */
Table::iterator Table::begin() { return columns.begin(); }
/**
 * @brief Provides a non-const iterator to the end of the `columns` vector.
 * @return An iterator pointing one past the last `TableColumn*`.
 */
Table::iterator Table::end() { return columns.end(); }

/**
 * @brief Provides a const iterator to the beginning of the `columns` vector.
 * @return A const iterator pointing to the first `TableColumn*`.
 */
Table::const_iterator Table::begin() const { return columns.begin(); }
/**
 * @brief Provides a const iterator to the end of the `columns` vector.
 * @return A const iterator pointing one past the last `TableColumn*`.
 */
Table::const_iterator Table::end() const { return columns.end(); }


/**
 * @brief Retrieves the logical name of the table.
 * @return The table's name as a string.
 */
std::string Table::getName() const {
    return name;
}

/**
 * @brief Retrieves the file path on disk associated with this table.
 * @return The table's filename as a string.
 */
std::string Table::getFilename() const {
    return filename;
}

/**
 * @brief Retrieves the name of the column at a given index.
 * @param index The 0-indexed position of the column.
 * @return The name of the column.
 * @throws std::runtime_error If the `index` is negative or greater than or equal to the number of columns.
 */
std::string Table::getColumnNameAtGivenIndex(int index) const {
    if (index < 0 || index >= columns.size()) {
        throw std::runtime_error("Invalid column index " + std::to_string(index) + ". Table '" + name + "' has " + std::to_string(columns.size()) + " columns.");
    }
    return columns[index]->getName();
}

/**
 * @brief Retrieves a specific row of data as a formatted string.
 *
 * This method concatenates the string representations of all cells in the
 * specified row, typically separated by spaces. It assumes all columns have
 * the same number of rows.
 *
 * @param index The 0-indexed position of the row to retrieve.
 * @return A string representing the entire row.
 * @throws std::runtime_error If the table has no columns.
 * @throws std::runtime_error If the `index` is negative or greater than or equal to the number of rows in the table.
 */
std::string Table::getRowAsString(int index) const {
    if (columns.empty()) {
        throw std::runtime_error("Table '" + name + "' has no columns.");
    }
    if (index < 0 || index >= columns[0]->getSize()) {
        throw std::runtime_error("Invalid row index " + std::to_string(index) + ". Table '" + name + "' has " + std::to_string(columns[0]->getSize()) + " rows.");
    }
    std::string result = "";

    for (const TableColumn* column : columns) {
        result += column->returnValueAtGivenIndexAsString(index) + " ";
    }
    return result;
}

/**
 * @brief Deletes a row at a specified index from all columns in the table.
 *
 * This operation iterates through all `TableColumn` objects and calls
 * `TableColumn::deleteCell()` on each at the given `index`, effectively
 * removing a full row from the table. It assumes all columns have the same
 * number of rows.
 *
 * @param index The 0-indexed position of the row to delete.
 * @throws std::runtime_error If the table has no columns.
 * @throws std::runtime_error If the `index` is negative or greater than or equal to the number of rows in the table.
 */
void Table::deleteGivenRow(int index) {
    if (columns.empty()) {
        throw std::runtime_error("Table '" + name + "' has no columns.");
    }
    if (index < 0 || index >= columns[0]->getSize()) {
        throw std::runtime_error("Invalid row index " + std::to_string(index) + ". Table '" + name + "' has " + std::to_string(columns[0]->getSize()) + " rows.");
    }
    for (TableColumn* column : columns) {
        column->deleteCell(index); 
    }
}

/**
 * @brief Adds a new column to the table.
 *
 * The `Table` takes ownership of the provided `TableColumn*`. It is expected
 * that the new column's size matches the existing number of rows in the table
 * (i.e., `col->getSize()` should be equal to `this->columns[0]->getSize()`
 * if the table is not empty), or that `fillColumnWithNULL` has been appropriately
 * called on it prior to addition to match the row count.
 *
 * @param col A pointer to the `TableColumn` object to add. The `Table` assumes ownership.
 * @note It is the caller's responsibility to ensure that the new column's size is consistent
 * with the existing columns if the table is not empty.
 */
void Table::addColumn(TableColumn* col) {
    columns.push_back(col);
}

/**
 * @brief Returns the total number of columns in the table.
 * @return An integer representing the count of columns.
 */
int Table::getNumberOfColumns() const {
    return columns.size();
}

/**
 * @brief Sets or updates the file path associated with this table.
 * @param filename The new file path for the table.
 */
void Table::setTablePath(const std::string& filename) {
    this->filename = filename;
}

/**
 * @brief Retrieves a pointer to the `TableColumn` object at a given index.
 * @param index The 0-indexed position of the column to retrieve.
 * @return A pointer to the `TableColumn` object.
 * @throws std::runtime_error If the `index` is negative or greater than or equal to the number of columns.
 */
TableColumn* Table::getColumnAtGivenIndex(int index) const {
    if (index < 0 || index >= columns.size()) {
        throw std::runtime_error("Invalid column index " + std::to_string(index) + ".Table '" + name + "' has " + std::to_string(columns.size()) + " columns.");
    }
    return columns[index];
}

/**
 * @brief Sets or updates the logical name of the table.
 * @param name The new name for the table.
 * @note This directly changes the `Table` object's name. If the `Catalog`
 * class relies on unique table names as keys in an internal map,
 * the `Catalog`'s internal mapping may need to be updated separately.
 */
void Table::setName(const std::string& name) {
    this->name = name;
}

/**
 * @brief Generates a string representation of the entire table's data.
 *
 * This method constructs a multi-line string where each line represents a row.
 * It first prints a header (column names and types - this part is actually handled by CatalogPrintCommand
 * but the toString just returns raw data). Cell values within a row are separated by spaces.
 *
 * @return A string containing all rows of the table, or an empty string if the table has no columns or no rows.
 * @throws std::runtime_error If the table has columns but they have inconsistent sizes (though `getSize()` assumes column 0).
 * @note This method assumes all columns have the same number of rows.
 */
std::string Table::toString() const {
    if (columns.empty()) {
        return ""; 
    }
    if (columns[0]->getSize() == 0) {
        return ""; 
    }

    std::string result = "";
    int numRows = columns[0]->getSize(); 

    for (int i = 0; i < numRows; ++i) {
        for (const TableColumn* column : columns) {
            result += column->returnValueAtGivenIndexAsString(i) + " ";
        }
        result += '\n'; 
    }
    return result;
}

/**
 * @brief Creates a deep copy of the current Table object with a new name and path.
 *
 * This method is essential for operations like "saveas" where the table
 * structure and data need to be duplicated to a new location without
 * affecting the original table in memory. It performs a deep copy of all
 * `TableColumn` objects by calling `TableColumn::clone()` for each, ensuring
 * that the new table has independent copies of all data.
 *
 * @param newName The name to assign to the cloned table.
 * @param newPath The file path to associate with the cloned table.
 * @return A new `Table` object that is a deep copy of the current instance,
 * but with the specified new name and file path.
 */
Table Table::cloneWithNewNameAndPath(const std::string& newName, const std::string& newPath) const {
    std::vector<TableColumn*> clonedCols;
    for (TableColumn* col : this->columns) {
        clonedCols.push_back(col->clone()); 
    }
    return Table(clonedCols, newName, newPath);
}

