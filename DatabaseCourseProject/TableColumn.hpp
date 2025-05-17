#pragma once
#include <vector>
#include <string>
#include "ColumnType.hpp"

class TableColumn {
public:
	~TableColumn() {};

	virtual std::string getName() const = 0;
	virtual ColumnType getType() const = 0;

};