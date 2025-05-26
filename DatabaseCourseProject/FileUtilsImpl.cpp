#include "FileUtils.hpp"

bool FileUtils::fileExists(const std::string& path) {
	std::ifstream file(path);
	return file.good();
}

std::string FileUtils::getDirectoryPath(const std::string& filepath) {
	int lastSlash = filepath.find_last_of("/\\");
	if (lastSlash == std::string::npos) {
		return ".";
	}
	return filepath.substr(0, lastSlash);
}