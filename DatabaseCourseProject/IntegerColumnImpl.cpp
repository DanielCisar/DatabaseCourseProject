#include "IntegerColumn.hpp"
#include <vector>
#include <string>
#include <stdexcept>

IntegerColumn::IntegerColumn(std::string name) : name(name) {

}
IntegerColumn::~IntegerColumn() {

}

std::string IntegerColumn::getName() const {
	return name;
}
ColumnType IntegerColumn::getType() const {
	return ColumnType::INTEGER;
}
std::vector<int> IntegerColumn::getContent() const {
	return content;
}

int IntegerColumn::getValueAtGivenIndex(int index) const {
	if (index < 0 || index >= content.size()) {
		throw std::invalid_argument("Invalid index. ");
	}
	if (isNull[index] == true) {
		throw std::invalid_argument("Value at given index is NULL. ");
	}

	return content[index];
}


void IntegerColumn::changeValueAtIndex(int index, std::string val) {
	if (index < 0 || index >= content.size()) {
		throw std::invalid_argument("Invalid index. ");
	}

	if (val == "NULL") {
		content[index] = 0;
		isNull[index] = true;
		return;
	}
	int value = std::stoi(val);

	content[index] = value;
}

void IntegerColumn::addCell(std::string cell) {
	if (cell == "NULL") {
		content.push_back(0);
		isNull.push_back(true);
		return;
	}
	content.push_back(std::stoi(cell));
}

void IntegerColumn::deleteCell(int index) {
	content.erase(content.begin() + index);
}

int IntegerColumn::getSize() {
	return content.size();
}

std::string IntegerColumn::returnValueAtGivenIndexAsString(int index) const {
	if (isNull[index] == true) {
		return "NULL";
	}
	return std::to_string(content[index]);
}

std::string IntegerColumn::getTypeAsString() const {
	return "Integer";
}