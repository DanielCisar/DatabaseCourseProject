#pragma once
#include <vector>
#include <string>

class TableColumn {
public:
	~TableColumn() {};

	virtual std::string getName() const = 0;
	virtual std::string getType() const = 0;

};