#pragma once
#include <string>
#include <vector>

/**
 * @class SupportedCommands
 * @brief A static utility class that provides lists of recognized commands.
 *
 * This class serves as a central repository for defining and retrieving
 * the names of commands supported by the application, categorized by their
 * functional area (e.g., file operations, catalog operations).
 * It's useful for displaying help menus and for validating user input.
 */
class SupportedCommands {
public:
    /**
	* @brief Returns a list of supported file-related commands.
	*
	* These commands typically deal with file system operations like opening,
	* saving, and closing database files or the application itself.
	*
	* @return A `std::vector<std::string>` containing the names of file commands.
	*/
	static std::vector<std::string> returnSupportedFileCommands();

	/**
	 * @brief Returns a list of supported catalog-related commands.
	 *
	 * These commands primarily interact with the in-memory database catalog and
	 * its tables, allowing operations such as inserting data, selecting rows,
	 * describing tables, and performing aggregates.
	 *
	 * @return A `std::vector<std::string>` containing the names of catalog commands.
	 */
	static std::vector<std::string> returnSupportedCatalogCommands();
};