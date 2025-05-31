#pragma once
#include <vector>
#include "Table.hpp"
#include <string>

/**
 * @class Catalog
 * @brief Manages a collection of database tables and their associated catalog file path.
 *
 * The `Catalog` class represents the in-memory database. It holds a collection
 * of `Table` objects, providing functionalities to add, remove, and retrieve tables
 * by name. It also tracks the file path on disk where the catalog's metadata
 * is or will be stored. The `Catalog` relies on the `Table` class's copy
 * semantics for proper deep copying of table data.
 */
class Catalog {
private:
    /**
     * @brief A collection of `Table` objects.
     *
     * Tables are stored by value, meaning each `Table` object within this vector
     * is a separate, independent copy. The `Table` class's own deep copy
     * constructor and assignment operator ensure that the `TableColumn*`
     * within each `Table` are properly managed.
     */
    std::vector<Table> tableCollection;

    std::string catalogPath; ///< The file path on disk where this catalog's metadata is stored (e.g., "my_database.cat").

public:
    /**
     * @brief Constructs an empty Catalog instance.
     *
     * Initializes the catalog with an empty table collection and no associated file path.
     */
    Catalog();

    /**
     * @brief Constructs a Catalog instance with a specified catalog file path.
     *
     * Initializes the catalog with an empty table collection. The `catalogPath`
     * can be used later for saving and loading the catalog's metadata.
     *
     * @param catalogPath The file path where this catalog is or will be stored.
     */
    Catalog(const std::string catalogPath);

    /**
     * @brief Destructor for Catalog.
     *
     * The default destructor provided by the compiler is sufficient here, as
     * `std::vector<Table>` automatically manages the destruction of `Table` objects,
     * and `Table` objects in turn manage their `TableColumn*` pointers.
     */
    ~Catalog();

    /**
     * @brief Copy constructor for Catalog.
     *
     * Performs a deep copy of the `tableCollection` vector and the `catalogPath`.
     * The deep copy of tables is handled automatically by `std::vector` and
     * the `Table` class's own copy constructor.
     *
     * @param other The Catalog object to copy from.
     */
    Catalog(const Catalog& other);

    /**
     * @brief Copy assignment operator for Catalog.
     *
     * Performs a deep copy of the `tableCollection` and `catalogPath` from
     * another Catalog instance to this object. Handles self-assignment correctly.
     * The deep copy of tables is managed by `std::vector` and `Table::operator=`.
     *
     * @param other The Catalog object to assign from.
     * @return A reference to this Catalog object after assignment.
     */
    Catalog& operator=(const Catalog& other);

    /**
     * @brief Adds a new table to the catalog.
     *
     * Before adding, this method checks if a table with the same name already exists
     * in the catalog to enforce uniqueness. If the name is unique, the table is
     * added as a copy into the internal collection.
     *
     * @param table The `Table` object to add. It is passed by value to ensure a copy.
     * @throws std::runtime_error If a table with the same name already exists in the catalog.
     */
    void addTable(Table table);

    /**
     * @brief Removes a table from the catalog by its index.
     *
     * @param index The 0-indexed position of the table to remove.
     * @throws std::out_of_range If the `index` is out of bounds for the table collection.
     */
    void removeTable(int index);

    /**
     * @brief Retrieves a reference to a table by its name.
     *
     * @param name The name of the table to retrieve.
     * @return A non-constant reference to the `Table` object.
     * @throws std::runtime_error If no table with the specified name is found in the catalog.
     */
    Table& returnTableByName(const std::string& name);

    /**
     * @brief Retrieves the file path associated with this catalog.
     * @return The catalog's file path as a string.
     */
    std::string getPath() const;

    /**
     * @brief Provides a non-const iterator to the beginning of the internal table collection.
     * @return An iterator pointing to the first `Table` object.
     */
    std::vector<Table>::iterator begin();

    /**
     * @brief Provides a non-const iterator to the end of the internal table collection.
     * @return An iterator pointing one past the last `Table` object.
     */
    std::vector<Table>::iterator end();

    /**
     * @brief Sets or updates the file path associated with this catalog.
     * @param catalogPath The new file path for the catalog.
     */
    void setPath(const std::string& catalogPath);
};