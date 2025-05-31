#include "DoubleColumn.hpp"
#include <vector>
#include <string>
#include <stdexcept>

/**
 * @brief Constructs a new DoubleColumn with a specified name.
 *
 * Initializes the column with an empty content vector and an empty `isNull` vector,
 * indicating that it contains no rows initially.
 *
 * @param name The name to assign to this column.
 */
DoubleColumn::DoubleColumn(std::string name) : name(name) {

}

/**
 * @brief Copy constructor for DoubleColumn.
 *
 * Performs a member-wise copy of the `content`, `isNull` vectors, and the `name` string.
 * This results in a deep copy because `std::vector` and `std::string` handle their
 * memory dynamically and have their own deep copy semantics.
 *
 * @param other The DoubleColumn object to copy from.
 */
DoubleColumn::DoubleColumn(const DoubleColumn& other)
    : content(other.content), 
    isNull(other.isNull),   
    name(other.name)        
{
}

/**
 * @brief Destructor for DoubleColumn.
 *
 * The default destructor provided by the compiler is sufficient here, as `std::vector`
 * and `std::string` automatically manage their own memory.
 */
DoubleColumn::~DoubleColumn() {

}

/**
 * @brief Copy assignment operator for DoubleColumn.
 *
 * Ensures proper deep copying from `other` to this object.
 * It prevents self-assignment to avoid accidental data corruption.
 *
 * @param other The DoubleColumn object to assign from.
 * @return A reference to this DoubleColumn object, allowing for chaining assignments.
 */
DoubleColumn& DoubleColumn::operator=(const DoubleColumn& other) {
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
std::string DoubleColumn::getName() const {
    return name;
}

/**
 * @brief Retrieves the data type of the column.
 * @return `ColumnType::DOUBLE`, indicating this column holds double values.
 */
ColumnType DoubleColumn::getType() const {
    return ColumnType::DOUBLE;
}

/**
 * @brief Retrieves a constant reference to the internal content vector.
 * @return A constant reference to the `std::vector<double>` that stores the column's data.
 * @note This method exposes the internal data structure and is not part of the `TableColumn` interface.
 */
const std::vector<double>& DoubleColumn::getContent() const {
    return content;
}

/**
 * @brief Retrieves the double value of a cell at a specific index.
 *
 * @param index The 0-indexed position of the cell.
 * @return The double value of the cell.
 * @throws std::runtime_error If the `index` is negative or greater than or equal to the column's size.
 * @throws std::runtime_error If the value at the given `index` is NULL. This method does not return a default value for NULLs.
 * @note This method is not part of the `TableColumn` interface, and is a concrete implementation detail.
 */
double DoubleColumn::getValueAtGivenIndex(int index) const {
    if (index < 0 || index >= content.size()) {
        throw std::runtime_error("Invalid index " + std::to_string(index) + " for DoubleColumn '" + name + "'. Column size is " + std::to_string(content.size()) + ".");
    }
    if (isNull[index]) {
        throw std::runtime_error("Value at index " + std::to_string(index) + " in DoubleColumn '" + name + "' is NULL.");
    }

    return content[index];
}

/**
 * @brief Changes the value of a cell at a specific index.
 *
 * The provided string `val` is converted to a `double` using `std::stod`.
 * If `val` is an empty string `""`, the cell is marked as NULL (its double content is set to 0.0).
 * Otherwise, the converted double value is stored, and the cell is marked as not NULL.
 *
 * @param index The 0-indexed position of the cell to modify.
 * @param val The new value for the cell, provided as a string. An empty string `""` implies NULL.
 * @throws std::runtime_error If the provided `index` is out of the column's bounds.
 * @throws std::invalid_argument If the `val` string cannot be converted to a valid double (e.g., "abc").
 * @throws std::out_of_range If the converted double value is too large or too small to fit in a `double`.
 */
void DoubleColumn::changeValueAtIndex(int index, std::string val) {
    if (index < 0 || index >= content.size()) {
        throw std::runtime_error("Invalid index " + std::to_string(index) + " for DoubleColumn '" + name + "'. Column size is " + std::to_string(content.size()) + ".");
    }

    if (val.empty()) { 
        content[index] = 0.0; 
        isNull[index] = true;
    }
    else {
        try {
            double doubleVal = std::stod(val); 
            content[index] = doubleVal;
            isNull[index] = false;
        }
        catch (const std::exception& e) {
            throw std::runtime_error("Error changing value at index " + std::to_string(index) + " in DoubleColumn '" + name + "': Provided value '" + val + "' is not a valid double. Original error: " + e.what());
        }
    }
}

/**
 * @brief Adds a new cell to the end of the column.
 *
 * The provided string `cell` is converted to a `double` using `std::stod`.
 * If `cell` is an empty string `""`, the new cell is added as NULL (its double content is set to 0.0).
 * Otherwise, the converted double value is added, and the cell is marked as not NULL.
 * This operation increases the column's size by one.
 *
 * @param cell The value for the new cell, provided as a string. An empty string `""` implies NULL.
 * @throws std::invalid_argument If the `cell` string cannot be converted to a valid double.
 * @throws std::out_of_range If the converted double value is out of the range of `double`.
 */
void DoubleColumn::addCell(std::string cell) {
    if (cell.empty()) { 
        content.push_back(0.0); 
        isNull.push_back(true);
    }
    else {
        try {
            double doubleVal = std::stod(cell); 
            content.push_back(doubleVal);
            isNull.push_back(false);
        }
        catch (const std::exception& e) {
            throw std::runtime_error("Error adding cell to DoubleColumn '" + name + "': Provided value '" + cell + "' is not a valid double. Original error: " + e.what());
        }
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
void DoubleColumn::deleteCell(int index) {
    if (index < 0 || index >= content.size()) {
        throw std::runtime_error("Invalid index " + std::to_string(index) + " for DoubleColumn '" + name + "'.Column size is " + std::to_string(content.size()) + ".");
    }

    content.erase(content.begin() + index);
    isNull.erase(isNull.begin() + index);
}

/**
 * @brief Returns the current number of elements (rows) in the column.
 * @return The size of the column.
 */
int DoubleColumn::getSize() {
    return content.size();
}

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
std::string DoubleColumn::returnValueAtGivenIndexAsString(int index) const {
    if (index < 0 || index >= content.size()) {
        throw std::runtime_error("Invalid index " + std::to_string(index) + " for DoubleColumn '" + name + "'. Column size is " + std::to_string(content.size()) + ".");
    }

    if (isNull[index]) { 
        return "";
    }
    return std::to_string(content[index]);
}

/**
 * @brief Retrieves the string representation of the column's type.
 * @return The string "Double".
 */
std::string DoubleColumn::getTypeAsString() const {
    return "Double";
}

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
bool DoubleColumn::matchesValues(int rowIndex, const std::string& value) const {
    if (rowIndex < 0 || rowIndex >= content.size()) {
        throw std::runtime_error("Invalid index " + std::to_string(rowIndex) + " for DoubleColumn '" + name + "'. Column size is " + std::to_string(content.size()) + ".");
    }

    if (isNull[rowIndex] && value.empty()) {
        return true; 
    }

    if (!isNull[rowIndex]) { 
        try {
            double doubleVal = std::stod(value); 
            return content[rowIndex] == doubleVal; 
        }
        catch (const std::exception& e) {
            return false;
        }
    }
    return false; 
}

/**
 * @brief Fills the column with a specified number of NULL (default double 0.0) values.
 *
 * This method appends `size` number of new cells to the column. Each new cell
 * will have a default double value (0.0) as its content and its `isNull` flag set to `true`.
 * This is useful for initializing new columns in existing tables.
 *
 * @param size The number of NULL values to add to the column.
 */
void DoubleColumn::fillColumnWithNULL(int size) {
    for (int i = 0; i < size; ++i) {
        content.push_back(0.0); 
        isNull.push_back(true);
    }
}

/**
 * @brief Creates a deep copy of the current DoubleColumn object.
 *
 * This method ensures that a new, independent `DoubleColumn` instance,
 * containing a full copy of its content and null flags, is created.
 *
 * @return A pointer to a newly allocated `DoubleColumn` object, which is a deep copy of this instance.
 * @warning The caller is responsible for `delete`ing the returned pointer to prevent memory leaks.
 */
TableColumn* DoubleColumn::clone() const {
    return new DoubleColumn(*this); 
}
