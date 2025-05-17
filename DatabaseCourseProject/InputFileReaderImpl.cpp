#include "InputFileReader.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "TableColumn.hpp"
#include "StringColumn.hpp"
#include "DoubleColumn.hpp"
#include "IntegerColumn.hpp"
#include "ColumnFactory.hpp"
#include <stdexcept>
#include "ColumnType.hpp"

InputFileReader::InputFileReader(std::string filepath, ColumnFactory cf) : filepath(filepath), factory(cf){
    
}
InputFileReader::~InputFileReader() {
	//impl if neccesary 
}
std::vector<std::string> InputFileReader::split(const std::string& line, char delimiter) {
    std::vector<std::string> tokens;
    int pos = 0;
    int prevPos = 0;

    for (char el : line) {
        if (el == delimiter) {
            std::string subStr = line.substr(prevPos + 1, pos + 1);

            tokens.push_back(subStr);

            prevPos = pos;
        }
        ++pos;
    }

    return tokens;
}

Table InputFileReader::readFromFile() {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filepath);
    }

    std::string line;

    std::getline(file, line);
    std::string tableName = line;

    line = "";
    std::getline(file, line);
    std::vector<std::string> types = split(line, ',');

    line = "";
    std::getline(file, line);
    std::vector<std::string> columnNames = split(line, ',');

    std::vector<TableColumn*> columns;

    for (int i = 0; i < types.size(); ++i) {
        if (types[i] == "String") {
            columns.push_back(factory.makeStringColumn(columnNames[i]));
        }
        else if (types[i] == "Integer") {
            columns.push_back(factory.makeIntegerColumn(columnNames[i]));
        }
        else if (types[i] == "Double") {
            columns.push_back(factory.makeDoubleColumn(columnNames[i]));
        }
        else {
            throw std::invalid_argument("Unsupported type. ");
        }
    }

    while (std::getline(file, line)) {
        std::vector<std::string> values = split(line, ',');
        if (values.size() != columns.size()) {
            throw std::runtime_error("Row length does not match number of columns. ");
        }

        for (int i = 0; i < values.size(); ++i) {
            const std::string& currentVal = values[i];
            TableColumn* currentCol = columns[i];

            currentCol->addCell(currentVal);
        }


    }
    file.close();

    return Table(columns, tableName, filepath);
}