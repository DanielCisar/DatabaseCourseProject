#pragma once
#include "TableColumn.hpp"
#include "DoubleColumn.hpp"
#include "IntegerColumn.hpp"
#include "StringColumn.hpp"
#include <string>

class ColumnFactory {
public:
	static StringColumn* makeStringColumn(const std::string& name);
	static IntegerColumn* makeIntegerColumn(const std::string& name);
	static DoubleColumn* makeDoubleColumn(const std::string& name);
};
