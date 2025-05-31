#include "Operations.hpp"
#include <vector>    
#include <numeric>   
#include <algorithm> 
#include <stdexcept> 

/**
 * @brief Calculates the sum of all elements in a vector of doubles.
 * @param cells The vector of numbers to sum.
 * @return The sum of the elements.
 */
double Operations::sum(const std::vector<double>& cells) {
    double totalSum = 0;
    for (double cell : cells) {
        totalSum += cell;
    }
    return totalSum;
}

/**
 * @brief Calculates the product of all elements in a vector of doubles.
 * @param cells The vector of numbers to multiply.
 * @return The product of the elements.
 */
double Operations::product(const std::vector<double>& cells) {
    double totalProduct = 1;
    for (double cell : cells) {
        totalProduct *= cell;
    }
    return totalProduct;
}

/**
 * @brief Finds the maximum value in a vector of doubles.
 * @param cells The vector of numbers.
 * @return The largest value.
 * @throws std::out_of_range If the input vector is empty.
 */
double Operations::max(const std::vector<double>& cells) {
    if (cells.empty()) {
        throw std::out_of_range("Cannot find maximum of an empty vector.");
    }
    double maxValue = cells[0];
    for (size_t i = 1; i < cells.size(); ++i) { 
        if (cells[i] > maxValue) {
            maxValue = cells[i];
        }
    }
    return maxValue;
}

/**
 * @brief Finds the minimum value in a vector of doubles.
 * @param cells The vector of numbers.
 * @return The smallest value.
 * @throws std::out_of_range If the input vector is empty.
 */
double Operations::min(const std::vector<double>& cells) {
    if (cells.empty()) {
        throw std::out_of_range("Cannot find minimum of an empty vector.");
    }
    double minValue = cells[0];
    for (size_t i = 1; i < cells.size(); ++i) { 
        if (cells[i] < minValue) {
            minValue = cells[i];
        }
    }
    return minValue;
}