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

	void changeValueAtIndex(int index, std::string val) override;
	int findIndexOfValue(std::string val) const override;

	void addCell(std::string cell) override;

	void deleteCell(int index) override;

	int getSize() override;

	std::string returnValueAtGivenIndexAsString(int index) const override;

};