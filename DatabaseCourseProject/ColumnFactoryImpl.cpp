#include "ColumnFactory.hpp"
#include <stdexcept>

/**
 * @brief Creates a new `StringColumn` instance.
 * @param name The name for the new string column.
 * @return A dynamically allocated `StringColumn` pointer. Caller takes ownership.
 */
TableColumn* ColumnFactory::makeColumn(const std::string& name, const std::string& type) {
	if (type == "String") return new StringColumn(name);
	if (type == "Integer") return new IntegerColumn(name);
	if (type == "Double") return new DoubleColumn(name);
	throw std::runtime_error("Unsupported column type: " + type);
}

