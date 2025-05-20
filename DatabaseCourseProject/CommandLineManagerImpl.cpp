#include "CommandLineManager.hpp"
#include "Table.hpp"
#include "TableColumn.hpp"
#include "DoubleColumn.hpp"
#include "IntegerColumn.hpp"
#include "StringColumn.hpp"
#include "ColumnType.hpp"
#include "ColumnFactory.hpp"
#include <vector>
#include <string>
#include "Catalog.hpp"
#include <filesystem>
#include <stdexcept>
#include <fstream>
#include "FileUtils.hpp"
#include <ostream>
#include <iostream>

CommandLineManager::CommandLineManager(CatalogRepository repo) : 
repo(repo),
loadedFileExists(false), 
currentLoadedFile(nullptr) {
	
}

CommandLineManager::~CommandLineManager() {

}

Table CommandLineManager::open(const std::string& filepath) {
	if (!FileUtils::fileExists(filepath)) {
		std::ofstream newFile(filepath);
		if (!newFile) {
			throw std::runtime_error("Error creating file at: " + filepath);
		}
		newFile.close();
		std::cout << "Created new empty file: " << filepath << "\n";
	}
	//TODO implement open logic
}