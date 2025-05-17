#pragma once
#include <iostream>
#include "Table.hpp"

class OutputFileWritter {
public:
	OutputFileWritter();
	~OutputFileWritter();

	void writeTableToFile(Table table, std::string filepath);
};