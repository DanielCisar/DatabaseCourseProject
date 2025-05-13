#include "Table.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

Table::Table(const std::vector<TableColumn> columns, const std::string name, const std::string filename)
	: columns(columns), name(name), filename(filename) {
}

Table::~Table() {
	// Destructor implementation (if needed)
}

void Table::deleteGivenRow(int index) {
	
	for (TableColumn column : columns) {
		column.content.erase(column.content.begin() + index);
	}
}

template <typename T>
//cite source
bool Table::checkValidityOfTemplateParameters(const T& value) {
	if (std::is_integral<T>::value){
		return true;
	}
	else if(std::is_floating_point<T>::value){
		return true;
	}
	else if (std::is_same<T, std::string>::value) {
		return true;
	}
	return false;
}

template <typename T>
bool Table::checkEquivelenceBetweenColumnAndType(int column, const T& value) {
	if (std::is_integral<T>::value && columns[column].type == "Integer") {
		return true;
	}
	else if (std::is_floating_point<T>::value && columns[column].type == "Double") {
		return true;
	}
	else if (std::is_same<T, std::string>::value && columns[column].type == "String") {
		return true;
	}
	return false;
}

std::string Table::getName() const {
	return name;
}

std::string Table::getFilename() const {
	return filename;
}

std::string Table::getColumnNameAtGivenIndex(int index) const {
	return columns[index].getName();
}

std::string Table::toString() const {

	std::string result = "";
	 
	int size = columns[0].getContent().size();

	for (int i = 0; i < size; i++) {
		for (const TableColumn column : columns) {
			result += column.returnValueAtGivenIndex(i) + " ";
		}
		result += '\n';
	}
	return result;
}

int Table::getNumberOfColumns() const {
	return columns.size();
}