#include "FileUtils.hpp"

bool FileUtils::fileExists(const std::string& path) {
	std::ifstream file(path);
	return file.good();
}