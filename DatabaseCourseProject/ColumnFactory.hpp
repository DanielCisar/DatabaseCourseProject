#pragma once
#include "TableColumn.hpp"
#include "DoubleColumn.hpp"
#include "IntegerColumn.hpp"
#include "StringColumn.hpp"
#include <string>

/**
 * @class ColumnFactory
 * @brief A static factory class responsible for creating `TableColumn` instances.
 *
 * The `ColumnFactory` provides a centralized safe way to instantiate
 * different types of columns (String, Integer, Double) without exposing their
 * specific constructors directly to client code. 
 */
class ColumnFactory {
public:
	/**
	 * @brief Creates a new `TableColumn` instance of a specified `type` with the given `name`.
	 * @param name The name for the new column.
	 * @param type The string representation of the column type to create (e.g., "String", "Integer", "Double").
	 * @return A pointer to a newly allocated `TableColumn` object of the requested type.
	 * @throws std::runtime_error If the provided `type` string is unsupported.
	 * @warning The caller is responsible for `delete`ing the returned pointer
	 * to prevent memory leaks.
	 */
	static TableColumn* makeColumn(const std::string& name, const std::string& type);

};


