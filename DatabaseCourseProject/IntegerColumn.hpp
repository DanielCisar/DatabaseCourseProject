#pragma once
#include "TableColumn.hpp"
#include <vector>
#include <string>

class IntegerColumn : public TableColumn {
private:
	std::vector<int> content;
	std::string name;
	std::string type;

public:
	IntegerColumn(std::string name);
	~IntegerColumn();

	std::string getName() const override;
	std::string getType() const override;
	std::vector<int> getContent() const;

	int getValueAtGivenIndex(int index) const;


	void changeValueAtIndex(int index, int val);
	int findIndexOfValue(int val) const;

	void addCell(int cell);
};