#include "OutputFileWritter.hpp"
#include <iostream>
#include <fstream>
#include <string>

/**
 * @brief Constructs a new `OutputFileWritter` instance.
 *
 * This constructor performs no specific initialization.
 */
OutputFileWritter::OutputFileWritter() {

}

/**
 * @brief Destroys the `OutputFileWritter` instance.
 *
 * As `OutputFileWritter` does not manage any dynamically allocated resources,
 * the default destructor is sufficient for proper cleanup.
 */
OutputFileWritter::~OutputFileWritter() {

}

/**
 * @brief Writes a `Table` object's data to a specified file.
 *
 * This function opens the specified file and writes the table's structure
 * (name, column types, column names) and all its data rows in a CSV-like format.
 * Each piece of data (type, name, cell value) is separated by commas.
 *
 * @param table A reference to the `Table` object to be written.
 * @param filepath The path to the output file.
 * @throws std::runtime_error If the file cannot be opened for writing.
 */
void OutputFileWritter::writeTableToFile(Table& table, std::string filepath) {
	std::ofstream out(filepath);
	if (!out.is_open()) {
		throw std::runtime_error("Unable to open file: " + filepath);
	}

	int numCols = table.getNumberOfColumns();
	if (numCols == 0) {
		out.close();
		return;
	}

	out << table.getName() << "\n";

	for (int i = 0; i < numCols; ++i) {
		out << table.getColumnAtGivenIndex(i)->getTypeAsString();
		if (i < numCols - 1) {
			out << ",";
		}
	}

	out << "\n";
	
	for (int i = 0; i < numCols; ++i) {
		out << table.getColumnNameAtGivenIndex(i);
		if (i < numCols - 1) {
			out << ",";
		}
	}
	out << "\n"; 

	int numRows = 0;
	if (numCols > 0) {
		numRows = table.getColumnAtGivenIndex(0)->getSize();
	}

	for (int i = 0; i < numRows; ++i) { 
		for (int j = 0; j < numCols; ++j) { 
			out << table.getColumnAtGivenIndex(j)->returnValueAtGivenIndexAsString(i);
			if (j < numCols - 1) {
				out << ","; 
			}
		}
		out << "\n"; 
	}
	out.close();

}

/**
 * @brief Writes a `Catalog` object's metadata to a specified file.
 *
 * This function iterates through all tables in the provided catalog and writes
 * their name and associated file path to the output file, separated by commas.
 * Each table occupies one line in the catalog file.
 *
 * @param catalog A reference to the `Catalog` object to be written.
 * @param filepath The path to the output file.
 * @throws std::runtime_error If the file cannot be opened for writing.
 */
void OutputFileWritter::writeCatalogToFile(Catalog& catalog, std::string filepath) {
	std::ofstream out(filepath);
	if (!out.is_open()) {
		throw std::runtime_error("Unable to open file: " + filepath);
	}
	for (const Table& table : catalog) {
		out << table.getName() << "," << table.getFilename() << "\n";
	}

	out.close();

}