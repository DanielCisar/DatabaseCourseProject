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


/**
 * @brief Constructs a new `InputFileReader` instance.
 *
 * This constructor performs no specific initialization beyond default-constructing
 * member variables (of which there are none in this class).
 */
InputFileReader::InputFileReader(OutputConsoleWritter& outputConsoleWritter) : 
    outputConsoleWritter(outputConsoleWritter)
{
}

/**
 * @brief Destroys the `InputFileReader` instance.
 *
 * As `InputFileReader` does not own any dynamically allocated resources,
 * the default destructor behavior is sufficient for proper cleanup.
 */
InputFileReader::~InputFileReader() {

}

/**
 * @brief Reads table data from a specified file and constructs a `Table` object.
 *
 * This function parses a `.db` file line by line to reconstruct a `Table`.
 * It reads the table name, column types, column names, and then iterates
 * through subsequent lines to add rows of data to the respective columns.
 * It uses `ColumnFactory` to create column instances and `CommandParser` to tokenize lines.
 *
 * @param filepath The full path to the table data file.
 * @return A `Table` object populated with data from the file.
 * @throws std::runtime_error If the file cannot be opened.
 * @throws std::runtime_error If a row's length does not match the number of columns.
 * @throws std::invalid_argument If an unsupported column type string (e.g., "unknown")
 * is found in the file's header.
 */
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
        try {
            columns.push_back(ColumnFactory::makeColumn(columnNames[i], types[i]));
        }
        catch (const std::exception& e) {
            throw std::runtime_error("Table: " + tableName + " could not be loaded. It will skipped. ");
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
            TableColumn* currentCol = columns[i];

            currentCol->addCell(values[i]);
        }


    }
    file.close();

    Table resTable(columns, tableName, filepath);

    return resTable;
}

/**
 * @brief Reads catalog metadata from a specified file and constructs a `Catalog` object.
 *
 * This function parses a `.cat` file, which is expected to contain a list of
 * table names and their corresponding file paths. For each table entry, it
 * attempts to read the actual table data using `readTableFromFile` and adds
 * the resulting `Table` object to the `Catalog`.
 * Invalid or unreadable table files will cause a `continue` (skipping that table),
 * indicating a resilient loading process for the catalog.
 *
 * @param filepath The full path to the catalog metadata file.
 * @return A `Catalog` object populated with tables referenced in the file.
 * @throws std::runtime_error If the catalog file cannot be opened.
 * @throws std::runtime_error If a line in the catalog file has an invalid format (not 2 tokens).
 */
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
        catch(const std::exception& e){
            outputConsoleWritter.printLine(e.what());
            continue;
        }
    }
    
    return catalog;
}
