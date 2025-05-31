#pragma once
#include <iostream>
#include <string>
#include "Table.hpp"
#include "Catalog.hpp"

/**
 * @class OutputFileWritter
 * @brief Handles writing in-memory database structures (Tables and Catalogs) to files.
 *
 * This class provides functionalities to persist `Table` data into structured
 * `.db` files and to save `Catalog` metadata into `.cat` files. It acts as an
 * abstraction layer for file output operations, ensuring that database objects
 * are written in a consistent and readable format.
 */
class OutputFileWritter {
public:

	/**
	* @brief Constructs a new `OutputFileWritter` instance.
	*
	* Initializes the file writer. No specific resources are managed by the constructor itself.
	*/
	OutputFileWritter();

	/**
	* @brief Destroys the `OutputFileWritter` instance.
	*
	* Cleans up any resources held by the writer. As this class currently
	* doesn't manage dynamic memory, the default destructor is sufficient.
	*/
	~OutputFileWritter();

	/**
	* @brief Writes a `Table` object's data to a specified file.
	*
	* The table data is written in a specific format suitable for later reading by `InputFileReader`:
	* 1. First line: Table name.
	* 2. Second line: Comma-separated column types (e.g., "String,Integer,Double").
	* 3. Third line: Comma-separated column names (e.g., "Name,Age,Height").
	* 4. Subsequent lines: Comma-separated row values.
	*
	* @param table A reference to the `Table` object to write.
	* @param filepath The full path to the file where the table data will be saved.
	* @throws std::runtime_error If the file cannot be opened for writing.
	* @note If the table has no columns, an empty file will be created containing only the table name.
	* @warning This method assumes all columns in the table have the same number of rows.
	*/
	void writeTableToFile(Table& table, std::string filepath);

	/**
	* @brief Writes a `Catalog` object's metadata to a specified file.
	*
	* The catalog metadata is written in a comma-separated format, with one
	* table entry per line: "TableName,TableFilePath.db". This file serves
	* as an index for all tables managed by the catalog.
	*
	* @param catalog A reference to the `Catalog` object to write.
	* @param filepath The full path to the file where the catalog metadata will be saved.
	* @throws std::runtime_error If the file cannot be opened for writing.
	*/
	void writeCatalogToFile(Catalog& catalog, std::string filepath);
};