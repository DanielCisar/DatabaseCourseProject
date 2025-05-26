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
#include <memory> 

class CommandLineManager {
private:
	bool loadedFileExists;
	std::shared_ptr<Catalog> currentLoadedFile; 
	InputFileReader fileReader;
	OutputConsoleWritter outputConsoleWriter;
	OutputFileWritter outputFileWritter;
public:
	CommandLineManager(InputFileReader fileReader
		, OutputConsoleWritter outputConsoleWriter
		, OutputFileWritter outputFileWritter
	);

	~CommandLineManager();

	std::shared_ptr<Catalog> getCurrentLoadedFile();
	void setCurrentLoadedFile(std::shared_ptr<Catalog> catalog);

	void open(const std::string& filepath);
	void close();
	void save();
	void saveAs(const std::string& filepath);
	void help();
	void exit();
};