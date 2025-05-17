#pragma once
#include "TableColumn.hpp"
#include "DoubleColumn.hpp"
#include "IntegerColumn.hpp"
#include "StringColumn.hpp"
#include <string>

class ColumnFactory {
public:
	ColumnFactory();
	~ColumnFactory();

	StringColumn* makeStringColumn(std::string name);
	IntegerColumn* makeIntegerColumn(std::string name);
	DoubleColumn* makeDoubleColumn(std::string name);
};
