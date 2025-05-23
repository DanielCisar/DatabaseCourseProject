#pragma once
#include "Table.hpp"

class Operations {
public:
	static double sum(const std::vector<double>& cells);
	static double product(const std::vector<double>& cells);
	static double max(const std::vector<double>& cells);
	static double min(const std::vector<double>& cells);
};