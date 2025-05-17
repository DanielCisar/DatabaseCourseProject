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
std::string IntegerColumn::getType() const {
	return "String";
}
std::vector<int> IntegerColumn::getContent() const {
	return content;
}

int IntegerColumn::getValueAtGivenIndex(int index) const {
	if (index < 0 || index >= content.size()) {
		throw std::invalid_argument("Invalid index. ");
	}
	return content[index];
}


void IntegerColumn::changeValueAtIndex(int index, int val) {
	if (index < 0 || index >= content.size()) {
		throw std::invalid_argument("Invalid index. ");
	}
	content[index] = val;
}
int IntegerColumn::findIndexOfValue(int val) const{
	int index = 0;
	for (auto v : content) {
		if (val == v) {
			return index;
		}
		++index;
	}
	throw std::invalid_argument("No such value found. ");

}

void IntegerColumn::addCell(int cell) {
	content.push_back(cell);
}
