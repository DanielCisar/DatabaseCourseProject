#include "DoubleColumn.hpp"
#include <vector>
#include <string>
#include <stdexcept>

DoubleColumn::DoubleColumn(std::string name) : name(name) {

}
DoubleColumn::~DoubleColumn() {

}

std::string DoubleColumn::getName() const {
	return name;
}
ColumnType DoubleColumn::getType() const {
	return ColumnType::DOUBLE;
}

std::vector<double> DoubleColumn::getContent() const {
	return content;
}

double DoubleColumn::getValueAtGivenIndex(int index) const {
	if (index < 0 || index >= content.size()) {
		throw std::invalid_argument("Invalid index. ");
	}

	if (isNull[index] == true) {
		throw std::invalid_argument("Value at given index is NULL. ");
	}


	return content[index];
}

void DoubleColumn::addCell(std::string cell) {
	if (cell == "NULL") {
		content.push_back(0.0);
		isNull.push_back(true);
		return;
	}

	content.push_back(std::stod(cell));
}

void DoubleColumn::deleteCell(int index) {
	content.erase(content.begin() + index);
}

int DoubleColumn::getSize() {
	return content.size();
}

std::string DoubleColumn::returnValueAtGivenIndexAsString(int index) const {
	if (isNull[index] == true) {
		return "NULL";
	}
	return std::to_string(content[index]);
}

std::string DoubleColumn::getTypeAsString() const {
	return "Double";
}

bool DoubleColumn::matchesValues(int rowIndex, const std::string& value) const {
	try {
		double doubleVal = std::stod(value);
		return getValueAtGivenIndex(rowIndex) == doubleVal;
	}
	catch (...) {
		return false;
	}

}