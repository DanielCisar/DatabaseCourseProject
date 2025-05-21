#pragma once
#include <iostream>
#include "Table.hpp"
#include "Catalog.hpp"

class OutputFileWritter {
public:
	OutputFileWritter();
	~OutputFileWritter();

	void writeTableToFile(Table table, std::string filepath);
	void writeCatalogToFile(Catalog catalog, std::string filepath);
};