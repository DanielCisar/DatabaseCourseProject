#include "StringColumn.hpp"
#include <vector>
#include <string>
#include <stdexcept>

StringColumn::StringColumn(std::string name) : name(name){

}
StringColumn::StringColumn(const StringColumn& other)
	: content(other.content),
	isNull(other.isNull),
	name(other.name)
{
}

StringColumn::~StringColumn() {

}
StringColumn& StringColumn::operator=(const StringColumn& other) {
	if (this != &other) {
		content = other.content;
		isNull = other.isNull;
		name = other.name;
	}
	return *this;
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
		throw std::runtime_error("Invalid index. ");
	}
	if (isNull[index] == true) {
		return "NULL";
	}
	return content[index];
}

void StringColumn::changeValueAtIndex(int index, std::string val) {
	if (index < 0 || index >= content.size()) {
		throw std::runtime_error("Invalid index. ");
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
	isNull.push_back(false);

}

void StringColumn::deleteCell(int index) {
	if (index < 0 || index >= content.size()) {
		throw std::runtime_error("Invalid index. ");
	}

	content.erase(content.begin() + index);
}

int StringColumn::getSize() {
	return content.size();
}

std::string StringColumn::returnValueAtGivenIndexAsString(int index) const {
	if (index < 0 || index >= content.size()) {
		throw std::runtime_error("Invalid index. ");
	}

	if (isNull[index] == true) {
		return "NULL";
	}
	return content[index];
}

std::string StringColumn::getTypeAsString() const {
	return "String";
}

bool StringColumn::matchesValues(int rowIndex, const std::string& value) const {
	if (rowIndex < 0 || rowIndex >= content.size()) {
		throw std::runtime_error("Invalid index. ");
	}

	if (isNull[rowIndex] && value == "NULL") {
		return true;
	}

	return getValueAtGivenIndex(rowIndex) == value;
}

void StringColumn::fillColumnWithNULL() {
	this->content = { "" };
	this->isNull = { true };

}

TableColumn* StringColumn::clone() const {
	return new StringColumn(*this);
}
