#pragma once
#include <fstream>	
#include <string>

class FileUtils {
public:
	static bool fileExists(const std::string& path) {
		std::ifstream file(path);
		return file.good();
	}
};