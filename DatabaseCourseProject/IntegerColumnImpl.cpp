#include "IntegerColumn.hpp"
#include <vector>
#include <string>
#include <stdexcept>

IntegerColumn::IntegerColumn(std::string name) : name(name) {

}
IntegerColumn::IntegerColumn(const IntegerColumn& other)
	: content(other.content),
	isNull(other.isNull),
	name(other.name)
{
}
IntegerColumn::~IntegerColumn() {

}
IntegerColumn& IntegerColumn::operator=(const IntegerColumn& other) {
	if (this != &other) {
		content = other.content;
		isNull = other.isNull;
		name = other.name;
	}
	return *this;
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
		throw std::runtime_error("Invalid index. ");
	}
	if (isNull[index] == true) {
		throw std::runtime_error("Value at given index is NULL. ");
	}

	return content[index];
}


void IntegerColumn::changeValueAtIndex(int index, std::string val) {
	if (index < 0 || index >= content.size()) {
		throw std::runtime_error("Invalid index. ");
	}

	if (val == "") {
		content[index] = 0;
		isNull[index] = true;
		return;
	}
	try {
		int value = std::stoi(val);

		content[index] = value;
	}
	catch (...) {
		throw std::runtime_error("Tried adding value that does not match to column type. ");
	}
}

void IntegerColumn::addCell(std::string cell) {
	if (cell == "") {
		content.push_back(0);
		isNull.push_back(true);
		return;
	}
	try {
		int intVal = std::stoi(cell);
		content.push_back(intVal);
		isNull.push_back(false);
	}
	catch (...) {
		throw std::runtime_error("Type does not match. ");
	}
}

void IntegerColumn::deleteCell(int index) {
	if (index < 0 || index >= content.size()) {
		throw std::runtime_error("Invalid index. ");
	}

	content.erase(content.begin() + index);
	isNull.erase(isNull.begin() + index);
}

int IntegerColumn::getSize() {
	return content.size();
}

std::string IntegerColumn::returnValueAtGivenIndexAsString(int index) const {
	if (index < 0 || index >= content.size()) {
		throw std::runtime_error("Invalid index. ");
	}

	if (isNull[index] == true) {
		return "";
	}
	return std::to_string(content[index]);
}

std::string IntegerColumn::getTypeAsString() const {
	return "Integer";
}

bool IntegerColumn::matchesValues(int rowIndex, const std::string& value) const {
	if (rowIndex < 0 || rowIndex >= content.size()) {
		throw std::runtime_error("Invalid index. ");
	}

	if (isNull[rowIndex] && value == "") {
		return true;
	}
	try {
		int intVal = std::stoi(value);
		return getValueAtGivenIndex(rowIndex) == intVal;
	}
	catch (...) {
		return false;
	}
}

void IntegerColumn::fillColumnWithNULL(int size) {
	for (int i = 0; i < size; ++i) {
		content.push_back(0);
		isNull.push_back(true);
	}
}

TableColumn* IntegerColumn::clone() const {
	return new IntegerColumn(*this);
}
