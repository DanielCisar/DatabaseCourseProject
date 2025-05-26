#include "Table.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include "FileUtils.hpp"

Table::Table(const std::vector<TableColumn*> columns, const std::string name, const std::string filename)
	: columns(columns), name(name), filename(filename) {
}

Table::Table(const Table& other)
	: name(other.name), filename(other.filename) {
	for (const auto& col : other.columns) {
		this->columns.push_back(col->clone()); 
	}
}

Table::~Table() {
	for (TableColumn* column : columns) {
		delete column;
	}
}

void Table::deleteGivenRow(int index) {
	if (index < 0 || index >= columns[0]->getSize()) {
		throw std::runtime_error("Invalid index. ");
	}
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
		throw std::runtime_error("Invalid index. ");
	}

	return columns[index]->getName();
}

std::string Table::getRowAsString(int index) const {
	if (index < 0 || index >= columns[0]->getSize()) {
		throw std::runtime_error("Invalid index. ");
	}
	std::string result = "";
	
	for (const TableColumn* column : columns) {
		result += column->returnValueAtGivenIndexAsString(index) + " ";
	}

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

		for (auto& col_ptr : this->columns) {
			delete col_ptr;
		}
		this->columns.clear();

		for (const auto& col_ptr : other.columns) {
			this->columns.push_back(col_ptr->clone());
		}

		this->name = other.name;
		this->filename = other.filename;

	}
	return *this;
}

void Table::setTablePath(const std::string& filename) {
	
	this->filename = filename;
}

TableColumn* Table::getColumnAtGivenIndex(int index) const {
	if (index < 0 || index >= columns.size()) {
		throw std::runtime_error("Invalid index. ");
	}
	return columns[index];
}

void Table::setName(const std::string& name) {
	this->name = name;
}

std::string Table::toString() const {

	if (columns.empty()) { 
		return "";
	}

	std::string result = "";

	int size = columns[0]->getSize();

	for (int i = 0; i < size; i++) {
		for (const TableColumn* column : columns) {
			result += column->returnValueAtGivenIndexAsString(i) + " ";
		}
		result += '\n';
	}
	return result;
}

Table Table::cloneWithNewNameAndPath(const std::string& newName, const std::string& newPath) const {
	std::vector<TableColumn*> clonedCols;
	for (TableColumn* col : this->columns) {
		clonedCols.push_back(col->clone());
	}
	return Table(clonedCols, newName, newPath);
}
