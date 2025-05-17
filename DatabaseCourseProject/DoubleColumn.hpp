#pragma once
#include "TableColumn.hpp"
#include <vector>
#include <string>

class DoubleColumn : public TableColumn {
private:
	std::vector<double> content;
	std::string name;
	std::string type;

public:
	DoubleColumn(std::string name);
	~DoubleColumn();

	std::string getName() const override;
	ColumnType getType() const override;
	std::vector<double> getContent() const;

	double getValueAtGivenIndex(int index) const;

	void changeValueAtIndex(int index, double val);
	int findIndexOfValue(double val) const;

	void addCell(double cell);
};