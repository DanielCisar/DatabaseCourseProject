#include "StringColumn.hpp"
#include <vector>
#include <string>
#include <stdexcept>

/**
 * @brief Constructs a new StringColumn with a specified name.
 *
 * Initializes the column with an empty content vector and an empty `isNull` vector,
 * indicating that it contains no rows initially.
 *
 * @param name The name to assign to this column.
 */
StringColumn::StringColumn(std::string name) : name(name) {
}

/**
 * @brief Copy constructor for StringColumn.
 *
 * Performs a member-wise copy of the `content`, `isNull` vectors, and the `name` string.
 * This results in a deep copy because `std::vector` and `std::string` handle their
 * memory dynamically and have their own deep copy semantics.
 *
 * @param other The StringColumn object to copy from.
 */
StringColumn::StringColumn(const StringColumn& other)
    : content(other.content), 
    isNull(other.isNull),   
    name(other.name)        
{
}

/**
 * @brief Destructor for StringColumn.
 *
 * The default destructor provided by the compiler is sufficient here, as `std::vector`
 * and `std::string` automatically manage their own memory.
 */
StringColumn::~StringColumn() {
    // No manual memory deallocation is needed here, as 'content' and 'isNull'
    // are std::vector and std::string, which manage their own memory.
}

/**
 * @brief Copy assignment operator for StringColumn.
 *
 * Ensures proper deep copying from `other` to this object.
 * It prevents self-assignment to avoid accidental data corruption.
 *
 * @param other The StringColumn object to assign from.
 * @return A reference to this StringColumn object, allowing for chaining assignments.
 */
StringColumn& StringColumn::operator=(const StringColumn& other) {
    if (this != &other) { 
        content = other.content; 
        isNull = other.isNull;   
        name = other.name;       
    }
    return *this;
}

/**
 * @brief Retrieves the name of the column.
 * @return The name of the column as a string.
 */
std::string StringColumn::getName() const {
    return name;
}

/**
 * @brief Retrieves the data type of the column.
 * @return `ColumnType::STRING`, indicating this column holds string values.
 */
ColumnType StringColumn::getType() const {
    return ColumnType::STRING;
}

/**
 * @brief Retrieves a constant reference to the internal content vector.
 * @return A constant reference to the `std::vector<std::string>` that stores the column's data.
 * @note This method exposes the internal data structure and is not part of the `TableColumn` interface.
 */
const std::vector<std::string>& StringColumn::getContent() const {
    return content;
}

/**
 * @brief Retrieves the value of a cell at a specific index.
 *
 * This method directly returns the string value if the cell is not NULL.
 * If the cell is marked as NULL, it returns an empty string `""`.
 *
 * @param index The 0-indexed position of the cell.
 * @return The string value of the cell, or `""` if NULL.
 * @throws std::runtime_error If the `index` is negative or greater than or equal to the column's size.
 * @note This method is not part of the `TableColumn` interface, and is a concrete implementation detail.
 */
std::string StringColumn::getValueAtGivenIndex(int index) const {
    if (index < 0 || index >= content.size()) {
        throw std::runtime_error("Invalid index " + std::to_string(index) + " for StringColumn '" + name + "'. Column size is " + std::to_string(content.size()) + ".");
    }
    if (isNull[index]) { 
        return "";
    }
    return content[index];
}

/**
 * @brief Changes the value of a cell at a specific index.
 *
 * If the provided `val` is an empty string `""`, the cell is marked as NULL.
 * Otherwise, the `val` is stored directly, and the cell is marked as not NULL.
 *
 * @param index The 0-indexed position of the cell to modify.
 * @param val The new string value for the cell. An empty string sets the cell to NULL.
 * @throws std::runtime_error If the `index` is negative or greater than or equal to the column's size.
 */
void StringColumn::changeValueAtIndex(int index, std::string val) {
    if (index < 0 || index >= content.size()) {
        throw std::runtime_error("Invalid index " + std::to_string(index) + " for StringColumn '" + name + "'. Column size is " + std::to_string(content.size()) + ".");
    }

    if (val.empty()) { 
        content[index] = "";
        isNull[index] = true;
    }
    else {
        content[index] = val;
        isNull[index] = false;
    }
}

/**
 * @brief Adds a new cell to the end of the column.
 *
 * If the `cell` string is empty, the new cell is added as a NULL value.
 * Otherwise, the string is added directly, and the cell is marked as not NULL.
 *
 * @param cell The string value to add. An empty string sets the cell to NULL.
 */
void StringColumn::addCell(std::string cell) {
    if (cell.empty()) { 
        content.push_back("");
        isNull.push_back(true);
    }
    else {
        content.push_back(cell);
        isNull.push_back(false);
    }
}

/**
 * @brief Deletes a cell at the specified index.
 *
 * This function removes the element at `index` from both the `content` vector
 * and the `isNull` vector, effectively removing a row entry from this column.
 *
 * @param index The 0-indexed position of the cell to delete.
 * @throws std::runtime_error If the `index` is negative or greater than or equal to the column's size.
 */
void StringColumn::deleteCell(int index) {
    if (index < 0 || index >= content.size()) {
        throw std::runtime_error("Invalid index " + std::to_string(index) + " for StringColumn '" + name + "'. Column size is " + std::to_string(content.size()) + ".");
    }

    content.erase(content.begin() + index);
    isNull.erase(isNull.begin() + index);
}

/**
 * @brief Returns the current number of elements (rows) in the column.
 * @return The size of the column.
 */
int StringColumn::getSize() {
    return content.size();
}

/**
 * @brief Retrieves the value of a cell at a specific index as a string.
 *
 * This method directly calls `getValueAtGivenIndex` to retrieve the value.
 * If the cell is NULL, it returns an empty string `""`.
 *
 * @param index The 0-indexed position of the cell.
 * @return The string representation of the cell's value, or `""` if NULL.
 * @throws std::runtime_error If the `index` is negative or greater than or equal to the column's size.
 */
std::string StringColumn::returnValueAtGivenIndexAsString(int index) const {
    return getValueAtGivenIndex(index);
}

/**
 * @brief Retrieves the string representation of the column's type.
 * @return The string "String".
 */
std::string StringColumn::getTypeAsString() const {
    return "String";
}

/**
 * @brief Checks if the value at a given row index matches a specified string value.
 *
 * Handles NULL values: a NULL cell in the column is considered a match if the
 * provided `value` is also an empty string `""`. Otherwise, a direct string
 * comparison is performed on the cell's actual content.
 *
 * @param rowIndex The 0-indexed position of the cell to compare.
 * @param value The string value to match against.
 * @return `true` if the cell's value matches (including NULL-to-empty-string match), `false` otherwise.
 * @throws std::runtime_error If the `rowIndex` is negative or greater than or equal to the column's size.
 */
bool StringColumn::matchesValues(int rowIndex, const std::string& value) const {
    if (rowIndex < 0 || rowIndex >= content.size()) {
        throw std::runtime_error("Invalid index " + std::to_string(rowIndex) + " for StringColumn '" + name + "'. Column size is " + std::to_string(content.size()) + ".");
    }

    if (isNull[rowIndex] && value.empty()) {
        return true;
    }
    if (!isNull[rowIndex]) {
        return content[rowIndex] == value;
    }
    return false;
}

/**
 * @brief Fills the column with a specified number of NULL (empty string) values.
 *
 * This method appends `size` number of new cells to the column. Each new cell
 * will have an empty string `""` as its content and its `isNull` flag set to `true`.
 * This is useful for initializing new columns in existing tables.
 *
 * @param size The number of NULL values to add to the column.
 */
void StringColumn::fillColumnWithNULL(int size) {
    for (int i = 0; i < size; ++i) {
        content.push_back("");
        isNull.push_back(true);
    }
}

/**
 * @brief Creates a deep copy of the current StringColumn object.
 *
 * This method ensures that a new, independent `StringColumn` instance is created,
 * copying all its internal data (content vector, isNull vector, and name).
 *
 * @return A pointer to a newly allocated `StringColumn` object, which is a deep copy of this instance.
 * @warning The caller is responsible for `delete`ing the returned pointer to prevent memory leaks.
 */
TableColumn* StringColumn::clone() const {
    return new StringColumn(*this); 
}