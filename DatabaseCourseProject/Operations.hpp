#pragma once
#include "Table.hpp"

class Operations {
public:
	static int sum(const std::vector<int>& cells) {
		int sum = 0;
		for (int cell : cells) {
			sum += cell;
		}
		return sum;
	}
	static double sum(const std::vector<double>& cells) {
		double sum = 0;
		for (double cell : cells) {
			sum += cell;
		}
		return sum;
	}
	static int product(const std::vector<int>& cells) {
		int product = 1;
		for (int cell : cells) {
			product *= cell;
		}
		return product;
	}
	static double product(const std::vector<double>& cells) {
		double product = 1;
		for (double cell : cells) {
			product *= cell;
		}
		return product;
	}
	static int max(const std::vector<int>& cells) {
		int max = cells[0];

		for (int cell : cells) {
			if (cell > max) {
				max = cell;
			}
		}
		return max;
	}
	static double max(const std::vector<double>& cells) {
		double max = cells[0];

		for (double cell : cells) {
			if (cell > max) {
				max = cell;
			}
		}
		return max;
	}
	static int min(const std::vector<int>& cells) {
		int min = cells[0];

		for (int cell : cells) {
			if (cell < min) {
				min = cell;
			}
		}
		return min;
	}
	static double min(const std::vector<double>& cells) {
		double min = cells[0];

		for (double cell : cells) {
			if (cell < min) {
				min = cell;
			}
		}
		return min;
	}
};