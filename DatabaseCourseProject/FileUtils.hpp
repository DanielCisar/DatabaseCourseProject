#pragma once
#include <fstream>	
#include <string>

/**
 * @class FileUtils
 * @brief A static utility class for common file system operations.
 *
 * `FileUtils` provides convenient methods to check for file existence and
 * extract directory paths from full file paths. It's designed to offer
 * cross-platform basic file system utilities.
 */
class FileUtils {
public:
    /**
	* @brief Checks if a file or directory exists at the specified path.
	*
	* This method attempts to open the file at the given `path` to determine
	* its existence and accessibility. It returns true if the file exists and
	* is in a "good" state (e.g., can be opened), and false otherwise.
	*
	* @param path The file system path to check.
	* @return `true` if the file exists and is accessible; `false` otherwise.
	*/
	static bool fileExists(const std::string& path);

    /**
     * @brief Extracts the directory path from a full file path.
     *
     * This method finds the last occurrence of a path separator (`/` or `\`)
     * in the given `filepath` and returns the substring up to that point,
     * effectively giving you the directory where the file resides.
     * If no path separator is found, it assumes the file is in the current
     * directory and returns ".".
     *
     * @param filepath The full path to a file (e.g., "C:/data/documents/file.txt" or "data/file.txt").
     * @return A `std::string` representing the directory path. Returns "." if no directory is specified.
     */
	static std::string getDirectoryPath(const std::string& filepath);
};