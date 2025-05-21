#include "Table.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

Table::Table(const std::vector<TableColumn*> columns, const std::string name, const std::string filename)
	: columns(columns), name(name), filename(filename) {
}

Table::~Table() {
	for (TableColumn* column : columns) {
		delete column;
	}
}

void Table::deleteGivenRow(int index) {
	
	for (TableColumn* column : columns) {
		column->deleteCell(index);
	}
}

std::string Table::getName() const {
	return name;
}

std::string Table::getFilename() const {
	return filename;
}

std::string Table::getColumnNameAtGivenIndex(int index) const {
	if (index < 0 || index >= columns.size()) {
		throw std::invalid_argument("Invalid index. ");
	}

	return columns[index]->getName();
}

std::string Table::printRow(int index) const {
	std::string result = "";
	
	const TableColumn* column = columns[index];

	result += column->returnValueAtGivenIndexAsString(index) + " ";

	return result;
}

int Table::getNumberOfColumns() const {
	return columns.size();
}

void Table::addColumn(TableColumn* col) {
	columns.push_back(col);
}
Table& Table::operator=(const Table& other) {
	if (this != &other) {
		this->columns = other.columns;
		this->filename = other.filename;
		this->name = other.name;
	}
	return *this;
}

void Table::setTablePath(std::string filename) {
	this->filename = filename;
}