#pragma once
#include <vector> 
#include <string> 

/**
 * @class Operations
 * @brief A static utility class providing common mathematical operations on collections of numbers.
 *
 * This class offers basic aggregate functions such as sum, product, maximum, and minimum
 * for vectors of double-precision floating-point numbers. It's designed to be a
 * stateless helper for performing calculations on numerical data, typically from table columns.
 */
class Operations {
public:
	/**
	 * @brief Calculates the sum of all elements in a vector of doubles.
	 * @param cells A constant reference to a `std::vector<double>` containing the numbers to sum.
	 * @return The sum of all elements. Returns 0 if the vector is empty.
	 */
	static double sum(const std::vector<double>& cells);

	/**
	 * @brief Calculates the product of all elements in a vector of doubles.
	 * @param cells A constant reference to a `std::vector<double>` containing the numbers to multiply.
	 * @return The product of all elements. Returns 1 if the vector is empty.
	 */
	static double product(const std::vector<double>& cells);

	/**
	 * @brief Finds the maximum value in a vector of doubles.
	 * @param cells A constant reference to a `std::vector<double>` containing the numbers.
	 * @return The largest value in the vector.
	 * @throws std::out_of_range If the input vector `cells` is empty.
	 */
	static double max(const std::vector<double>& cells);

	/**
	 * @brief Finds the minimum value in a vector of doubles.
	 * @param cells A constant reference to a `std::vector<double>` containing the numbers.
	 * @return The smallest value in the vector.
	 * @throws std::out_of_range If the input vector `cells` is empty.
	 */
	static double min(const std::vector<double>& cells);
};