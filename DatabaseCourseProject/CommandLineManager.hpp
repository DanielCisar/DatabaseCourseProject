#pragma once
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
#include "CatalogRepository.hpp"
class CommandLineManager {
private:
	CatalogRepository repo;
	bool loadedFileExists;
	Catalog* currentLoadedFile;

public:
	CommandLineManager(CatalogRepository repo);
	~CommandLineManager();

	Table open(const std::string& filepath);
	void close();
	void save();
	void saveAs(std::string filepath);
	void help();
};