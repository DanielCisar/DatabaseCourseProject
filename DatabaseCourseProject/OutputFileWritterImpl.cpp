#include "OutputFileWritter.hpp"
#include <iostream>
#include <fstream>
#include <string>

OutputFileWritter::OutputFileWritter() {

}
OutputFileWritter::~OutputFileWritter() {

}

void OutputFileWritter::writeTableToFile(Table table, std::string filepath) {
	std::ofstream out(filepath);
	if (!out.is_open()) {
		throw std::runtime_error("Unable to open file: " + filepath);
	}

	int numCols = table.getNumberOfColumns();
	if (numCols == 0) {
		out.close();
		return;
	}

	out << table.getName();
	out << "\n";

	for (auto& col : table) {
		out << col->getTypeAsString();
	}
	out << "\n";
	
	for (int i = 0; i < numCols; ++i) {
		out << table.getColumnNameAtGivenIndex(i);
		if (i < numCols - 1) {
			out << ",";
		}
	}

	out << table.toString();
	out << "\n";

	out.close();

}

void OutputFileWritter::writeCatalogToFile(Catalog catalog, std::string filepath) {
	std::ofstream out(filepath);
	if (!out.is_open()) {
		throw std::runtime_error("Unable to open file: " + filepath);
	}
	for (const Table& table : catalog) {
		out << table.getName() << "," << table.getFilename() << "\n";
	}

	out.close();

}