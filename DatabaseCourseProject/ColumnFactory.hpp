#pragma once
#include "TableColumn.hpp"
#include "DoubleColumn.hpp"
#include "IntegerColumn.hpp"
#include "StringColumn.hpp"
#include <string>

/**
 * @class ColumnFactory
 * @brief A static factory class responsible for creating concrete `TableColumn` instances.
 *
 * The `ColumnFactory` provides a centralized and type-safe way to instantiate
 * different types of columns (String, Integer, Double) without exposing their
 * specific constructors directly to client code. This promotes decoupling and
 * simplifies the creation process for `TableColumn` objects.
 */
class ColumnFactory {
public:
    /**
     * @brief Creates a new `StringColumn` with the specified name.
     * @param name The name for the new string column.
     * @return A pointer to a newly allocated `StringColumn` object.
     * @warning The caller is responsible for `delete`ing the returned pointer
     * to prevent memory leaks, as it is dynamically allocated using `new`.
     * Consider using smart pointers (e.g., `std::unique_ptr<StringColumn>`)
     * for automatic memory management.
     */
	static TableColumn* makeColumn(const std::string& name, const std::string& type);

};


