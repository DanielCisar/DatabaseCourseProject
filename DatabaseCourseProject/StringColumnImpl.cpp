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
	if (isNull[index] == true) {
		return "NULL";
	}
	return content[index];
}

void StringColumn::changeValueAtIndex(int index, std::string val) {
	if (index < 0 || index >= content.size()) {
		throw std::invalid_argument("Invalid index. ");
	}
	
	if (val != "NULL") {
		content[index] = val;
		isNull[index] = false;
		return;
	}
	
	content[index] = "";
	isNull[index] = true;
	
}

void StringColumn::addCell(std::string cell) {
	if (cell == "NULL") {
		isNull.push_back(true);
		content.push_back("");
		return;
	}
	content.push_back(cell);
}

void StringColumn::deleteCell(int index) {
	if (index < 0 || index >= content.size()) {
		throw std::invalid_argument("Invalid index. ");
	}

	content.erase(content.begin() + index);
}

int StringColumn::getSize() {
	return content.size();
}

std::string StringColumn::returnValueAtGivenIndexAsString(int index) const {
	if (index < 0 || index >= content.size()) {
		throw std::invalid_argument("Invalid index. ");
	}

	if (isNull[index] == true) {
		return "NULL";
	}
	return content[index];
}

std::string StringColumn::getTypeAsString() const {
	return "String";
}