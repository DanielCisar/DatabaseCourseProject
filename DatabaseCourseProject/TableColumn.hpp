#pragma once
#include <vector>
#include <string>
#include "ColumnType.hpp"

class TableColumn {
public:
	~TableColumn(){}

	virtual std::string getName() const = 0;
	virtual ColumnType getType() const = 0;
	virtual void deleteCell(int index) = 0;
	virtual int getSize() = 0;
	virtual std::string returnValueAtGivenIndexAsString(int index) const = 0;
	virtual void changeValueAtIndex(int index, std::string val) = 0;
	virtual int findIndexOfValue(std::string val) const = 0;
	virtual void addCell(std::string cell) = 0;
	virtual std::string getTypeAsString() const = 0;
};