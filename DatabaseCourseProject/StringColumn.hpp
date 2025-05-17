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


	void changeValueAtIndex(int index, std::string val) override;
	int findIndexOfValue(std::string val) const override;

	void addCell(std::string cell) override;

	void deleteCell(int index) override;

	int getSize() override;

	std::string returnValueAtGivenIndexAsString(int index) const override;
};