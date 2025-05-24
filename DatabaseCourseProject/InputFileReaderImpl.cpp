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

InputFileReader::InputFileReader()
{
}
InputFileReader::~InputFileReader() {

}

Table InputFileReader::readTableFromFile(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filepath);
    }

    std::string line;


    std::getline(file, line);
    std::string tableName = line;

    line = "";
    std::getline(file, line);
    std::vector<std::string> types = CommandParser::parseCommand(line, ',');

    line = "";
    std::getline(file, line);
    std::vector<std::string> columnNames = CommandParser::parseCommand(line, ',');

    std::vector<TableColumn*> columns;

    for (int i = 0; i < types.size(); ++i) {
        if (types[i] == "String") {
            columns.push_back(ColumnFactory::makeStringColumn(columnNames[i]));
        }
        else if (types[i] == "Integer") {
            columns.push_back(ColumnFactory::makeIntegerColumn(columnNames[i]));
        }
        else if (types[i] == "Double") {
            columns.push_back(ColumnFactory::makeDoubleColumn(columnNames[i]));
        }
        else {
            throw std::invalid_argument("Unsupported type. ");
        }
    }

    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        std::vector<std::string> values = CommandParser::parseCommand(line, ',');
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

    Table resTable(columns, tableName, filepath);

    return resTable;
}

Catalog InputFileReader::readCatalogFromFile(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filepath);
    }

    Catalog catalog(filepath);

    std::string line;

    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }
        std::vector<std::string> tokens = CommandParser::parseCommand(line, ',');

        if (tokens.size() != 2) {
            throw std::runtime_error("Invalid line in catalog CSV file: " + line);
        }
        
        std::string tableFilePath = tokens[1];

        try {
            catalog.addTable(readTableFromFile(tableFilePath));
        }
        catch(const std::runtime_error& e){
            continue;
        }
    }
    
    return catalog;
}
