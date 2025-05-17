#pragma once
#include "TableColumn.hpp"
#include <vector>
#include <string>

class StringColumn : public TableColumn {
private:
	std::vector<std::string> content;
	std::string name;
	std::string type;

public:
	StringColumn(std::string name);
	~StringColumn();

	std::string getName() const override;
	ColumnType getType() const override;
	std::vector<std::string> getContent() const;

	std::string getValueAtGivenIndex(int index) const;


	void changeValueAtIndex(int index, std::string val);
	int findIndexOfValue(std::string val) const;

	void addCell(std::string cell);
};