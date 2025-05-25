#include "OutputFileWritter.hpp"
#include <iostream>
#include <fstream>
#include <string>

OutputFileWritter::OutputFileWritter() {

}
OutputFileWritter::~OutputFileWritter() {

}

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