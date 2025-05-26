#pragma once
#include <fstream>	
#include <string>

class FileUtils {
public:
	static bool fileExists(const std::string& path);
	static std::string getDirectoryPath(const std::string& filepath);
};