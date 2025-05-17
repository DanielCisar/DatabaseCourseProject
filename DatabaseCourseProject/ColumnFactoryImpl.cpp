#include "ColumnFactory.hpp"
#include "TableColumn.hpp"
#include "DoubleColumn.hpp"
#include "IntegerColumn.hpp"
#include "StringColumn.hpp"
#include <string>

ColumnFactory::ColumnFactory() {

}
ColumnFactory::~ColumnFactory() {

}

StringColumn* ColumnFactory::makeStringColumn(std::string name) {
	return new StringColumn(name);
}
IntegerColumn* ColumnFactory::makeIntegerColumn(std::string name) {
	return new IntegerColumn(name);
}
DoubleColumn* ColumnFactory::makeDoubleColumn(std::string name) {
	return new DoubleColumn(name);
}