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
	return content[index];
}


void DoubleColumn::changeValueAtIndex(int index, double val) {
	if (index < 0 || index >= content.size()) {
		throw std::invalid_argument("Invalid index. ");
	}
	content[index] = val;
}
int DoubleColumn::findIndexOfValue(double val) const {
	int index = 0;
	for (auto v : content) {
		if (val == v) {
			return index;
		}
		++index;
	}
	throw std::invalid_argument("No such value found. ");

}

void DoubleColumn::addCell(double cell) {
	content.push_back(cell);
}

void DoubleColumn::deleteCell(int index) {
	content.erase(content.begin() + index);
}

int DoubleColumn::getSize() {
	return content.size();
}

std::string DoubleColumn::returnValueAtGivenIndexAsString(int index) const {
	return std::to_string(content[index]);
}