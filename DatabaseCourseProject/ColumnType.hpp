#pragma once

/**
 * @enum ColumnType
 * @brief Enumerates the supported data types for columns within a database table.
 *
 * This enum class provides a type-safe way to specify and identify the data
 * type of a `TableColumn`, allowing for polymorphic handling of different
 * underlying data storage mechanisms (e.g., `std::string`, `int`, `double`).
 */
enum class ColumnType {
    /**
     * @brief Represents a column that stores text or character data.
     * Values are typically handled as `std::string`.
     */
    STRING,

    /**
    * @brief Represents a column that stores whole numbers.
    * Values are typically handled as `int`.
    */
    INTEGER,

    /**
     * @brief Represents a column that stores floating-point numbers.
     * Values are typically handled as `double`.
     */
    DOUBLE
};
