#include "ColumnFactory.hpp"
#include "TableColumn.hpp"
#include "DoubleColumn.hpp"
#include "IntegerColumn.hpp"
#include "StringColumn.hpp"
#include <string>


StringColumn* ColumnFactory::makeStringColumn(const std::string& name) {
	return new StringColumn(name);
}
IntegerColumn* ColumnFactory::makeIntegerColumn(const std::string& name) {
	return new IntegerColumn(name);
}
DoubleColumn* ColumnFactory::makeDoubleColumn(const std::string& name) {
	return new DoubleColumn(name);
}
