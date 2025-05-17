#include "StringColumn.hpp"
#include <vector>
#include <string>
#include <stdexcept>

StringColumn::StringColumn(std::string name) : name(name){

}
StringColumn::~StringColumn() {

}

std::string StringColumn::getName() const {
	return name;
}
ColumnType StringColumn::getType() const {
	return ColumnType::STRING;
}
std::vector<std::string> StringColumn::getContent() const {
	return content;
}

std::string StringColumn::getValueAtGivenIndex(int index) const {
	if (index < 0 || index >= content.size()) {
		throw std::invalid_argument("Invalid index. ");
	}
	return content[index];
}


void StringColumn::changeValueAtIndex(int index, std::string val) {
	if (index < 0 || index >= content.size()) {
		throw std::invalid_argument("Invalid index. ");
	}
	content[index] = val;
}
int StringColumn::findIndexOfValue(std::string val) const{
	int index = 0;
	for (auto v : content) {
		if (val == v) {
			return index;
		}
		++index;
	}
	throw std::invalid_argument("No such value found. ");

}

void StringColumn::addCell(std::string cell) {
	content.push_back(cell);
}