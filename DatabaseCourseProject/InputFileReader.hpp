#pragma once
#include <iostream>      
#include <fstream>       
#include <sstream>       
#include <vector>        
#include <string>        
#include "Table.hpp"     
#include "ColumnFactory.hpp" 
#include "CommandParser.hpp" 
#include "Catalog.hpp"   
#include "OutputConsoleWritter.hpp"

/**
 * @class InputFileReader
 * @brief Handles reading and parsing data from various file formats into in-memory database structures.
 *
 * This class provides functionalities to load `Table` data from `.db` (or similar structured) files
 * and to load `Catalog` metadata from `.cat` files. It acts as an abstraction layer for file I/O,
 * interpreting file content to construct database objects.
 */
class InputFileReader {
    OutputConsoleWritter& outputConsoleWritter;

public:
    /**
     * @brief Constructs a new `InputFileReader` instance.
     *
     * Initializes the file reader. No specific resources are managed by the constructor itself.
     */
    InputFileReader(OutputConsoleWritter& outputConsoleWritter);

    /**
     * @brief Destroys the `InputFileReader` instance.
     *
     * Cleans up any resources held by the reader. As this class currently
     * doesn't manage dynamic memory, the default destructor is sufficient.
     */
    ~InputFileReader();

    /**
     * @brief Reads table data from a specified file and constructs a `Table` object.
     *
     * The file is expected to be in a specific format:
     * 1. First line: Table name.
     * 2. Second line: Comma-separated column types (e.g., "String,Integer,Double").
     * 3. Third line: Comma-separated column names (e.g., "Name,Age,Height").
     * 4. Subsequent lines: Comma-separated row values (e.g., "John Doe,30,1.85").
     * Empty strings for cell values are interpreted as NULL.
     *
     * @param filepath The full path to the `.db` file containing the table data.
     * @return A `Table` object populated with data from the file.
     * @throws std::runtime_error If the file cannot be opened, or if a row's length
     * does not match the number of columns.
     * @throws std::invalid_argument If an unsupported column type is encountered in the file header.
     */
    Table readTableFromFile(const std::string& filepath);

    /**
     * @brief Reads catalog metadata from a specified file and constructs a `Catalog` object.
     *
     * The catalog file is expected to list table names and their corresponding
     * file paths, one table per line, in a comma-separated format:
     * "TableName,TableFilePath.db".
     * This method recursively calls `readTableFromFile` for each table listed in the catalog.
     *
     * @param filepath The full path to the `.cat` file containing the catalog metadata.
     * @return A `Catalog` object populated with tables referenced in the file.
     * @throws std::runtime_error If the catalog file cannot be opened, or if a line
     * in the catalog file has an invalid format.
     */
    Catalog readCatalogFromFile(const std::string& filepath);
};