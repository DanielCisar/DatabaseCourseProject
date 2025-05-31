#include "Catalog.hpp"
#include <vector>
#include <stdexcept>
#include <string>

/**
 * @brief Constructs an empty Catalog instance.
 *
 * Initializes `tableCollection` as an empty vector and `catalogPath` as an empty string.
 */
Catalog::Catalog() {

}

/**
 * @brief Constructs a Catalog instance with a specified catalog file path.
 *
 * Initializes `tableCollection` as an empty vector. The `catalogPath` is set
 * to the provided value, which will be used for saving and loading the catalog.
 *
 * @param catalogPath The file path where this catalog is or will be stored.
 */
Catalog::Catalog(const std::string catalogPath) : catalogPath(catalogPath) {

}

/**
 * @brief Destructor for Catalog.
 *
 * The default destructor is sufficient because `std::vector<Table>` automatically
 * handles the destruction of all `Table` objects it contains. Each `Table` object,
 * in turn, correctly manages the memory of its `TableColumn` pointers.
 */
Catalog::~Catalog() {
    

}

/**
 * @brief Copy constructor for Catalog.
 *
 * Performs a member-wise copy of `tableCollection` and `catalogPath`.
 * Since `std::vector` performs element-wise copy and `Table` has a deep
 * copy constructor, this results in a deep copy of all tables and their columns.
 *
 * @param other The Catalog object to copy from.
 */
Catalog::Catalog(const Catalog& other)
    : tableCollection(other.tableCollection), 
    catalogPath(other.catalogPath) {
}

/**
 * @brief Copy assignment operator for Catalog.
 *
 * Ensures proper deep copying from `other` to this object.
 * It prevents self-assignment to avoid accidental data corruption.
 * The assignment operation for `std::vector<Table>` handles
 * deleting old `Table` objects and copying new ones, utilizing
 * `Table::operator=` for each element.
 *
 * @param other The Catalog object to assign from.
 * @return A reference to this Catalog object, allowing for chaining assignments.
 */
Catalog& Catalog::operator=(const Catalog& other) {
    if (this != &other) { 
        this->tableCollection = other.tableCollection; 
        this->catalogPath = other.catalogPath;
    }
    return *this;
}

/**
 * @brief Adds a new table to the catalog.
 *
 * Before adding, this method iterates through the existing tables to ensure
 * that no other table with the same name already exists. If a duplicate name
 * is found, an exception is thrown. Otherwise, the provided `Table` object
 * (which is a copy of the original passed by value) is moved into the
 * `tableCollection`.
 *
 * @param table The `Table` object to add to the catalog. Passed by value to ensure a copy.
 * @throws std::runtime_error If a table with the same name (`table.getName()`)
 * already exists in the `tableCollection`.
 */
void Catalog::addTable(Table table) { 
    for (const auto& t : tableCollection) {
        if (table.getName() == t.getName()) {
            throw std::runtime_error("Duplicate table name in catalog: '" + table.getName() + "'. A table with this name already exists.");
        }
    }
    tableCollection.push_back(std::move(table)); 
}

/**
 * @brief Removes a table from the catalog by its index.
 *
 * This function erases the `Table` object at the specified `index` from the
 * `tableCollection`. The `Table` object's destructor will be called automatically,
 * ensuring proper memory cleanup of its columns.
 *
 * @param index The 0-indexed position of the table to remove.
 * @throws std::out_of_range If the `index` is negative or greater than or equal to the
 * number of tables in the collection.
 */
void Catalog::removeTable(int index) {
    if (index < 0 || index >= tableCollection.size()) {
        throw std::out_of_range("Invalid index " + std::to_string(index) + ".Catalog has " + std::to_string(tableCollection.size()) + " tables.");
    }
    tableCollection.erase(tableCollection.begin() + index);
}

/**
 * @brief Retrieves a non-constant reference to a table by its name.
 *
 * This method searches the `tableCollection` for a table whose name matches the
 * provided `name`. If found, a reference to that `Table` object is returned,
 * allowing for direct modification of the table's contents.
 *
 * @param name The name of the table to retrieve.
 * @return A non-constant reference to the `Table` object with the matching name.
 * @throws std::runtime_error If no table with the specified `name` is found in the catalog.
 */
Table& Catalog::returnTableByName(const std::string& name) {
    for (auto& table : tableCollection) {
        if (table.getName() == name) {
            return table;
        }
    }
    throw std::runtime_error("No table with the name '" + name + "' found in the catalog.");
}

/**
 * @brief Retrieves the file path associated with this catalog.
 * @return The catalog's file path as a constant string reference.
 */
std::string Catalog::getPath() const {
    return this->catalogPath;
}

/**
 * @brief Provides a non-const iterator to the beginning of the internal table collection.
 * @return An iterator pointing to the first `Table` object in the catalog.
 */
std::vector<Table>::iterator Catalog::begin() {
    return tableCollection.begin();
}

/**
 * @brief Provides a non-const iterator to the end of the internal table collection.
 * @return An iterator pointing one past the last `Table` object in the catalog.
 */
std::vector<Table>::iterator Catalog::end() {
    return tableCollection.end();
}

/**
 * @brief Sets or updates the file path associated with this catalog.
 * @param catalogPath The new file path for the catalog.
 */
void Catalog::setPath(const std::string& catalogPath) {
    this->catalogPath = catalogPath;
}