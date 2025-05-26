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
#include "InputFileReader.hpp"
#include "OutputConsoleWriter.hpp"
#include "OutputFileWritter.hpp"
#include "InputConsoleReader.hpp"
#include <memory> 

class CatalogCommandManager {
private:
	std::shared_ptr<Catalog> loadedCatalog; 
	InputFileReader fileReader;
	OutputConsoleWritter outputConsoleWriter;
	OutputFileWritter outputFileWritter;
	InputConsoleReader inputConsoleReader;
	bool loadedCatalogExists;

public:
	CatalogCommandManager(InputFileReader fileReader,
		OutputConsoleWritter outputConsoleWriter,
		OutputFileWritter outputFileWritter,
		InputConsoleReader inputConsoleReader);
	~CatalogCommandManager();

	void setLoadedCatalog(std::shared_ptr<Catalog> catalog);
	std::shared_ptr<Catalog> getCurrentLoadedFile();

	void closeLoadedCatalog();

	void import(const std::string& filepath);
	void showTables();
	void describe(const std::string& name);
	void print(const std::string& name);
	void exportTable(const std::string& name, const std::string& filepath);
	void select(int numberOfColumn, std::string value, const std::string& name);
	void addColumn(const std::string& tableName, const std::string& columnName, ColumnType columnType);
	void update(const std::string& tableName,
		int searchColumn,
		std::string searchValue,
		int targetColumn,
		std::string targetValue);
	void deleteRows(const std::string& tableName, int searchColumn, std::string searchValue);
	void insert(const std::string& tableName, std::vector<std::string> values);
	void innerJoin(const std::string& tableName1, int column1, const std::string& tableName2, int column2);
	void rename(const std::string& oldName, const std::string& newName);
	void count(const std::string& tableName, int searchColumn, std::string searchValue);
	void agregate(const std::string& tableName,
		int searchColumn,
		std::string seacrhValue,
		int targetColumn,
		std::string operation);

};