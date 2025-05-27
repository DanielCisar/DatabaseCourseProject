#include "DoubleColumn.hpp"
#include <vector>
#include <string>
#include <stdexcept>

DoubleColumn::DoubleColumn(std::string name) : name(name) {

}
DoubleColumn::DoubleColumn(const DoubleColumn& other)
	:content(other.content), 
	isNull(other.isNull),   
	name(other.name)        
{
}

DoubleColumn& DoubleColumn::operator=(const DoubleColumn& other) {
	if (this != &other) { 
		content = other.content;       
		isNull = other.isNull;
		name = other.name;             
	}
	return *this;
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

void DoubleColumn::changeValueAtIndex(int index, std::string val) {
	if (index < 0 || index >= content.size()) {
		throw std::runtime_error("Invalid index. ");
	}
	if (val == "") {
		content[index] = 0;
		isNull[index] = true;
		return;
	}
	try {
		double doubleVal = std::stod(val);
		content[index] = doubleVal;
	}
	catch (...) {
		throw std::runtime_error("Tried adding value that does not match to column type. ");
	}
}

double DoubleColumn::getValueAtGivenIndex(int index) const {
	if (index < 0 || index >= content.size()) {
		throw std::runtime_error("Invalid index. ");
	}

	if (isNull[index] == true) {
		throw std::runtime_error("Value at given index is NULL. ");
	}


	return content[index];
}

void DoubleColumn::addCell(std::string cell) {
	if (cell == "") {
		content.push_back(0.0);
		isNull.push_back(true);
		return;
	}
	try {
		double doubleVal = std::stod(cell);
		content.push_back(doubleVal);
		isNull.push_back(false);
	}
	catch (...) {
		throw std::runtime_error("Type does not match. ");
	}
}

void DoubleColumn::deleteCell(int index) {
	if (index < 0 || index >= content.size()) {
		throw std::runtime_error("Invalid index. ");
	}

	content.erase(content.begin() + index);
	isNull.erase(isNull.begin() + index);
}

int DoubleColumn::getSize() {
	return content.size();
}

std::string DoubleColumn::returnValueAtGivenIndexAsString(int index) const {
	if (index < 0 || index >= content.size()) {
		throw std::runtime_error("Invalid index. ");
	}

	if (isNull[index] == true) {
		return "";
	}
	return std::to_string(content[index]);
}

std::string DoubleColumn::getTypeAsString() const {
	return "Double";
}

bool DoubleColumn::matchesValues(int rowIndex, const std::string& value) const {
	if (rowIndex < 0 || rowIndex >= content.size()) {
		throw std::runtime_error("Invalid index. ");
	}

	if (isNull[rowIndex] && value == "") {
		return true;
	}

	try {
		double doubleVal = std::stod(value);
		return getValueAtGivenIndex(rowIndex) == doubleVal;
	}
	catch (...) {
		return false;
	}

}

void DoubleColumn::fillColumnWithNULL() {
	this->content = { 0.0 };
	this->isNull = { true };

}

TableColumn* DoubleColumn::clone() const {
	return new DoubleColumn(*this);
}
