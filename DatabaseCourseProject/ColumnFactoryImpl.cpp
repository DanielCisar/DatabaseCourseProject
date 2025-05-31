#include "ColumnFactory.hpp"

/**
 * @brief Creates a new `StringColumn` instance.
 * @param name The name for the new string column.
 * @return A dynamically allocated `StringColumn` pointer. Caller takes ownership.
 */
StringColumn* ColumnFactory::makeStringColumn(const std::string& name) {
	return new StringColumn(name);
}

/**
 * @brief Creates a new `IntegerColumn` instance.
 * @param name The name for the new integer column.
 * @return A dynamically allocated `IntegerColumn` pointer. Caller takes ownership.
 */
IntegerColumn* ColumnFactory::makeIntegerColumn(const std::string& name) {
	return new IntegerColumn(name);
}

/**
 * @brief Creates a new `DoubleColumn` instance.
 * @param name The name for the new double column.
 * @return A dynamically allocated `DoubleColumn` pointer. Caller takes ownership.
 */
DoubleColumn* ColumnFactory::makeDoubleColumn(const std::string& name) {
	return new DoubleColumn(name);
}
