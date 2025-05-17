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

InputFileReader::InputFileReader(ColumnFactory cf, CommandParser parser) :
  factory(cf)
, parser(parser)
{
    
}
InputFileReader::~InputFileReader() {
	
}

Table InputFileReader::readFromFile(std::string filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filepath);
    }

    std::string line;

    std::getline(file, line);
    std::string tableName = line;

    line = "";
    std::getline(file, line);
    std::vector<std::string> types = parser.parseCommand(line, ',');

    line = "";
    std::getline(file, line);
    std::vector<std::string> columnNames = parser.parseCommand(line, ',');

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
        std::vector<std::string> values = parser.parseCommand(line, ',');
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