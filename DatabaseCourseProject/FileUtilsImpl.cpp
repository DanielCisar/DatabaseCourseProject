#include "FileUtils.hpp"

/**
 * @brief Checks if a file or directory exists at the specified path.
 *
 * This implementation uses `std::ifstream` to attempt opening the file.
 * The `file.good()` method then checks if the stream is in a good state,
 * which implies the file exists and can be accessed.
 *
 * @param path The file system path to check.
 * @return `true` if the file exists and is accessible; `false` otherwise.
 */
bool FileUtils::fileExists(const std::string& path) {
	std::ifstream file(path);
	return file.good();
}

/**
 * @brief Extracts the directory path from a full file path.
 *
 * This function finds the last occurrence of either a forward slash (`/`)
 * or a backslash (`\`) to determine the directory separator. If no separator
 * is found, it assumes the file is in the current directory and returns ".".
 *
 * @param filepath The full path to a file.
 * @return A `std::string` representing the directory path.
 */
std::string FileUtils::getDirectoryPath(const std::string& filepath) {
	int lastSlash = filepath.find_last_of("/\\");
	if (lastSlash == std::string::npos) {
		return ".";
	}
	return filepath.substr(0, lastSlash);
}