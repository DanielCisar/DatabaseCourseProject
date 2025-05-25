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

class CommandLineManager {
private:
	bool loadedFileExists;
	Catalog currentLoadedFile;
	InputFileReader fileReader;
	OutputConsoleWritter outputConsoleWriter;
	OutputFileWritter outputFileWritter;
public:
	CommandLineManager(InputFileReader fileReader
		, OutputConsoleWritter outputConsoleWriter
		, OutputFileWritter outputFileWritter
	);

	~CommandLineManager();

	Catalog& getCurrentLoadedFile();
	void setCurrentLoadedFile(Catalog& catalog);

	void open(const std::string& filepath);
	void close();
	void save();
	void saveAs(std::string filepath);
	void help();
	void exit();
};