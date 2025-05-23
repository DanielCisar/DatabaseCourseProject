#include "Operations.hpp" 

double Operations::sum(const std::vector<double>& cells) {
	double sum = 0;
	for (double cell : cells) {
		sum += cell;
	}
	return sum;
}

double Operations::product(const std::vector<double>& cells) {
	double product = 1;
	for (double cell : cells) {
		product *= cell;
	}
	return product;
}

double Operations::max(const std::vector<double>& cells) {
	double max = cells[0];

	for (double cell : cells) {
		if (cell > max) {
			max = cell;
		}
	}
	return max;
}

double Operations::min(const std::vector<double>& cells) {
	double min = cells[0];

	for (double cell : cells) {
		if (cell < min) {
			min = cell;
		}
	}
	return min;
}