#pragma once
#include "TableColumn.hpp"
#include <vector>
#include <string>

class StringColumn : public TableColumn {
private:
	std::vector<std::string> content;
	std::vector<bool> isNull;
	std::string name;

public:
	StringColumn(std::string name);
	~StringColumn();

	std::string getName() const override;
	ColumnType getType() const override;
	std::vector<std::string> getContent() const;

	std::string getValueAtGivenIndex(int index) const;


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