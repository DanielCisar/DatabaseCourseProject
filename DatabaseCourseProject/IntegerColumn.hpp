#pragma once
#include "TableColumn.hpp"
#include <vector>
#include <string>

class IntegerColumn : public TableColumn {
private:
	std::vector<int> content;
	std::vector<bool> isNull;
	std::string name;

public:
	IntegerColumn(std::string name);
	~IntegerColumn();

	std::string getName() const override;
	ColumnType getType() const override;
	std::vector<int> getContent() const;

	int getValueAtGivenIndex(int index) const;


	void changeValueAtIndex(int index, std::string val) override;

	void addCell(std::string cell) override;

	void deleteCell(int index) override;

	int getSize() override;

	std::string returnValueAtGivenIndexAsString(int index) const override;

	std::string getTypeAsString() const override;

	bool matchesValues(int rowIndex, const std::string& value) const override;

	void fillColumnWithNULL() override;

	TableColumn* clone() const override;

};