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

std::vector<std::string> Table::describe() const {
	std::vector<std::string> columnNames;

	for (const TableColumn column : columns) {
		columnNames.push_back(column.name);
	}

	return columnNames;
}

std::string Table::toString() const {

	std::string result = "";
	 
	int size = columns[0].content.size();

	for (int i = 0; i < size; i++) {
		for (const TableColumn column : columns) {
			result += column.content[i] + " ";
		}
		result += '\n';
	}
	return result;
}

template<typename T>
std::string Table::select(int numberOfColumn, T value) const {

	//Add to resources

	if (numberOfColumn > columns.size() && numberOfColumn < 0) {
		throw std::out_of_range("Invalid search column index: " + std::to_string(numberOfColumn));
	}

	std::string result = "";

	int size = columns[0].content.size();


	for (int i = 0; i < size; i++) {

		//https://stackoverflow.com/questions/13636540/how-to-check-for-the-type-of-a-template-parameter
		//Add to resources

		const std::string& cell = columns[numberOfColumn].content[i];
		if (std::is_same<T, std::string>::value) {
			if (cell = value) {
				for (const TableColumn column : columns) {
					result += column.content[i] + " ";
				}
				result += '\n';

			}
		}
		else {
			// Add to resources
			std::stringstream ss(cell);
			T cellValue;
			ss >> cellValue;

			if (!ss.fail() && ss.eof() && cellValue == value) {
				for (const TableColumn column : columns) {
					result += column.content[i] + " ";
				}
				result += '\n';

			}
		}
	}

	return result;
}
void Table::addColumn(std::string name, std::string type) {

	if (type != "Integer", "Double", "String") {
		throw std::invalid_argument("Invalid type: " + type);
	}

	std::vector<std::string> newCloumnContent;

	for (int i = 0; i < columns[0].content.size(); i++) {
		newCloumnContent.push_back("NULL");
	}

	TableColumn newColumn;
	newColumn.type = type;
	newColumn.content = newCloumnContent;
	newColumn.name = name;

	columns.push_back(newColumn);	
}

template<typename T, typename U>
void Table::update(int searchColumn, T searchValue, int targetColumn, U targetValue) {

	int size = columns[0].content.size();

	if (searchColumn > columns.size() && searchColumn < 0) {
		throw std::out_of_range("Invalid search column index: " + std::to_string(numberOfColumn));
	}

	if (targetColumn > columns.size() && targetColumn < 0) {
		throw std::out_of_range("Invalid target column index: " + std::to_string(numberOfColumn));
	}

	if (!checkValidityOfTemplateParameters(searchValue)) {
		throw std::invalid_argument("Unsupported value type. ");
	}
	
	if (!checkValidityOfTemplateParameters(targetValue)) {
		throw std::invalid_argument("Unsupported value type. ");
	}
	
	if (!checkEquivelenceBetweenColumnAndType(targetColumn, targetValue)) {
		throw std::invalid_argument("Column doesn't accept this value type. ");
	}
	for (int i = 0; i < size; i++) {

		const std::string& cell = columns[numberOfColumn].content[i];

		if (std::is_same<T, std::string>::value) {
			if (cell = searchValue) {
				columns[targetColumn].content[i] = targetValue;
			}
		}
		else {
			std::stringstream ss(cell);
			T cellValue;
			ss >> cellValue;

			if (!ss.fail() && ss.eof() && cellValue == searchValue) {
				//Add to resources 
				columns[targetColumn].content[i] = std::to_string(targetValue);
				
			}
		}
	}
}
template<typename T>
void Table::deleteRow(int searchColumn, T searchValue) {
	int size = columns[0].content.size();

	if (searchColumn > columns.size() && searchColumn < 0) {
		throw std::out_of_range("Invalid search column index: " + std::to_string(numberOfColumn));
	}

	if (!checkValidityOfTemplateParameters(searchValue)) {
		throw std::invalid_argument("Unsupported value type. ");
	}
	bool foundValue = false;

	for (int i = 0; i < size; i++) {
		const std::string& cell = columns[numberOfColumn].content[i];

		if (std::is_same<T, std::string>::value) {
			if (cell = searchValue) {
				deleteGivenRow(i);
				foundValue = true;
			}
		}
		else {

			std::stringstream ss(cell);
			T cellValue;
			ss >> cellValue;

			if (!ss.fail() && ss.eof() && cellValue == searchValue) {
				deleteGivenRow(i);
				foundValue = true;
			}
		}
	 }
	if (!foundValue) {
		throw std::invalid_argument("No such values exist in the table. ");

	}
}

void Table::insert(std::vector<std::string> values) {
	int i = 0;
	for (TableColumn column : columns) {
		column.content.push_back(values.at(i));
		i++;
	}
}

void Table::changeName(std::string newName) {
	this->name = newName;
}

template<typename T>
int Table::count(int searchColumn, T value) const {
	int count = 0;

	if (searchColumn > columns.size() && searchColumn < 0) {
		throw std::out_of_range("Invalid search column index: " + std::to_string(numberOfColumn));
	}

	if (!checkValidityOfTemplateParameters(value)) {
		throw std::invalid_argument("Unsupported value type. ");
	}

	int size = columns[0].content.size();

	for (int i = 0; i < size; i++) {

		for (TableColumn column : columns) {
			if (std::is_same<T, std::string>::value) {
				if (column.content[i] = value) {
					count++;
					continue;
				}
			}
			else {
				std::stringstream ss(column.content[i]);
				T cellValue;
				ss >> cellValue;

				if (!ss.fail() && ss.eof() && cellValue == value) {
					count++;
					continue;
				}
			}
		}
	}
	return count;
}

template<typename T>
double Table::agregate(int searchColumn, T searchValue, int targetColumn, std::string operation) {
	int size = columns[0].content.size();
	
	if (searchColumn > columns.size() && searchColumn < 0) {
		throw std::out_of_range("Invalid search column index: " + std::to_string(numberOfColumn));
	}

	if (targetColumn > columns.size() && targetColumn < 0) {
		throw std::out_of_range("Invalid target column index: " + std::to_string(numberOfColumn));
	}

	if (!checkValidityOfTemplateParameters(searchValue)) {
		throw std::invalid_argument("Unsupported value type. ");
	}

	if (!checkValidityOfTemplateParameters(targetValue)) {
		throw std::invalid_argument("Unsupported value type. ");
	}

	std::vector<double> cells;

	if (columns[targetColumn].type != "Integer" 
		|| columns[targetColumn].type != "Double") {

		throw std::invalid_argument("Specified column doesn't contain numbers. ");

	}
	
	for (int i = 0; i < size; i++) {

		const std::string& cell = columns[numberOfColumn].content[i];

		std::stringstream ss(cell);
		T cellValue;
		ss >> cellValue;

		if (!ss.fail() && ss.eof() && cellValue == searchValue) { 
			
			cells.push_back(columns[targetColumn].content[i]);
		}
	}

	if (operation == "sum") {
		double sum = 0;
		for (double cell : cells) {
			sum += cell;
		}
		return sum;
	}
	else if (operation == "product") {
		double product = 1;
		for (double cell : cells) {
			product *= cell;
		}
		return product;
	}
	else if(operation ==  "maximum") {
		double max = cells[0];

		for (double cell : cells) {
			if (cell > max) {
				max = cell;
			}
		}
		return max;
	}
	else if(operation == "minimum") {
		double min = cells[0];

		for (double cell : cells) {
			if (cell < min) {
				min = cell; 
			}
		}
		return min;
	}
	else {
		throw std::invalid_argument("Requested unsupported operation. ");
	}
}
