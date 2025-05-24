#include "CatalogCommandManager.hpp"
#include "IOUtils.hpp"
#include <stdexcept>
#include "Operations.hpp"

CatalogCommandManager::CatalogCommandManager(
    InputFileReader fileReader,
    OutputConsoleWritter outputConsoleWriter,
    OutputFileWritter outputFileWritter,
    InputConsoleReader inputConsoleReader) :
    fileReader(fileReader),
    outputConsoleWriter(outputConsoleWriter),
    outputFileWritter(outputFileWritter),
    inputConsoleReader(inputConsoleReader),
    loadedCatalogExists(false)
{
	this->loadedCatalog = Catalog();
}

CatalogCommandManager::~CatalogCommandManager()
{
}

void CatalogCommandManager::import(const std::string& filepath)
{
    if (!loadedCatalogExists) {
        throw std::runtime_error("There is no file opened! ");
    }

    try {
        Table table = fileReader.readTableFromFile(filepath);

        loadedCatalog.addTable(table);

        outputConsoleWriter.printLine("Succesfuly imported table - " + table.getName() + ". ");
    }
    catch (const std::exception& e) {
        outputConsoleWriter.printLine(e.what());
    }
}

void CatalogCommandManager::showTables()
{
    if (!loadedCatalogExists) {
        throw std::runtime_error("There is no file opened! ");
    }

    outputConsoleWriter.printLine("List of tables: ");

    for (auto& table : loadedCatalog) {
        outputConsoleWriter.printLine(table.getName());
    }
}

void CatalogCommandManager::exportTable(const std::string& name, const std::string& filepath) {
    outputFileWritter.writeTableToFile(loadedCatalog.returnTableByName(name), filepath);
}

void CatalogCommandManager::describe(const std::string& name)
{
    if (!loadedCatalogExists) {
        throw std::runtime_error("There is no file opened! ");
    }

    try {
        Table table = loadedCatalog.returnTableByName(name);
        
        int index = 0;

        for (auto& col : table) {
            outputConsoleWriter.printLine(
                "Type of column " + std::to_string(index) + ": " + col->getTypeAsString()
            );
            index++;
        }
    }
    catch (const std::exception& e) {
        outputConsoleWriter.printLine(e.what());
    }
}

void CatalogCommandManager::print(const std::string& name)
{
    if (!loadedCatalogExists) {
        throw std::runtime_error("There is no file opened! ");
    }

    try {
        Table table = loadedCatalog.returnTableByName(name);

        std::string command;

        outputConsoleWriter.printLine("Table: " + name);

        for (auto& col : table) {
            outputConsoleWriter.print(col->getName() + " ");
        }
		outputConsoleWriter.printLine("");
		for (auto& col : table) {
			outputConsoleWriter.print(col->getTypeAsString() + " ");
		}
		outputConsoleWriter.printLine("");
        std::vector<std::string> rows;

        for (int i = 0; i < table.getNumberOfColumns(); i++) {
            rows.push_back(table.getRowAsString(i));

        }

        IOUtils::printInPageFormat(rows, outputConsoleWriter, inputConsoleReader);

    }
    catch (const std::exception& e) {
        outputConsoleWriter.printLine(e.what());
    }

}

void CatalogCommandManager::select(int numberOfColumn, std::string value, const std::string& name)
{
    if (!loadedCatalogExists) {
        throw std::runtime_error("There is no file opened! ");
    }
    try {
        Table table = loadedCatalog.returnTableByName(name);

        TableColumn* columnToSearch = table.getColumnAtGivenIndex(numberOfColumn);

        if (numberOfColumn < 0 || numberOfColumn >= columnToSearch->getSize()) {
            throw std::out_of_range("Invalid column index");
        }

        std::vector<std::string> rows;

        int size = columnToSearch->getSize();

        for (int i = 0; i < size; i++) {
            if (columnToSearch->matchesValues(i, value)) {
                rows.push_back(table.getRowAsString(i));
       
            }
        }
        
        IOUtils::printInPageFormat(rows, outputConsoleWriter, inputConsoleReader);
    }
    catch (const std::exception& e) {
        outputConsoleWriter.printLine(e.what());
    }

}

void CatalogCommandManager::addColumn(const std::string& tableName,
    const std::string& columnName,
    ColumnType columnType)
{
    if (!loadedCatalogExists) {
        throw std::runtime_error("There is no file opened! ");
    }
    try {
        Table table = loadedCatalog.returnTableByName(tableName);

        int colSize = table.getColumnAtGivenIndex(0)->getSize();

        if (columnType == ColumnType::STRING) {
            table.addColumn(ColumnFactory::makeStringColumn(columnName));
        }
        else if (columnType == ColumnType::INTEGER) {
            table.addColumn(ColumnFactory::makeIntegerColumn(columnName));
        }
        else {
            table.addColumn(ColumnFactory::makeDoubleColumn(columnName));
        }
    }
    catch (const std::exception& e) {
        outputConsoleWriter.printLine(e.what());
    }
}

void CatalogCommandManager::update(const std::string& tableName,
    int searchColumn,
    std::string searchValue,
    int targetColumn,
    std::string targetValue)
{
    if (!loadedCatalogExists) {
        throw std::runtime_error("There is no file opened! ");
    }
    try {
        Table table = loadedCatalog.returnTableByName(tableName);

        int size = table.getColumnAtGivenIndex(0)->getSize();

        for (auto& col : table) {
            for (int i = 0; i < size; ++i) {
                if (col->matchesValues(i, searchValue)) {
                    table.getColumnAtGivenIndex(targetColumn)->changeValueAtIndex(i, targetValue);
                }
            }
        }
    }
    catch (const std::exception& e) {
        outputConsoleWriter.printLine(e.what());
    }
}

void CatalogCommandManager::deleteRows(const std::string& tableName,
    int searchColumn,
    std::string searchValue)
{
    if (!loadedCatalogExists) {
        throw std::runtime_error("There is no file opened! ");
    }
    try {
        Table table = loadedCatalog.returnTableByName(tableName);

        int size = table.getColumnAtGivenIndex(0)->getSize();

        for (auto& col : table) {
            for (int i = 0; i < size; ++i) {
                if (col->matchesValues(i, searchValue)) {
                    table.deleteGivenRow(i);
                }
            }
        }
    }
    catch (const std::exception& e) {
        outputConsoleWriter.printLine(e.what());
    }
}

void CatalogCommandManager::insert(const std::string& tableName, std::vector<std::string> values)
{
    if (!loadedCatalogExists) {
        throw std::runtime_error("There is no file opened! ");
    }
    try {
        Table table = loadedCatalog.returnTableByName(tableName);

        if (values.size() != table.getNumberOfColumns()) {
            throw std::invalid_argument("Number of value is not equal to number of column. ");
        }
        int i = 0;
        for (auto& col : table) {
            col->addCell(values[i]);
            ++i;
        }
    }
    catch (const std::exception& e) {
        outputConsoleWriter.printLine(e.what());
    }
}

void CatalogCommandManager::innerJoin(const std::string& tableName1,
    int column1,
    const std::string& tableName2,
    int column2)
{
    if (!loadedCatalogExists) {
        throw std::runtime_error("There is no file opened! ");
    }
    try {
        Table table1 = loadedCatalog.returnTableByName(tableName1);
        Table table2 = loadedCatalog.returnTableByName(tableName2);

        if (column1 >= table1.getColumnAtGivenIndex(0)->getSize() ||
            column2 >= table1.getColumnAtGivenIndex(0)->getSize()) {

            throw std::runtime_error("Invalid column index. ");
        }

        TableColumn* col1 = table1.getColumnAtGivenIndex(column1);
        TableColumn* col2 = table2.getColumnAtGivenIndex(column1);

        if (col1->getType() != col2->getType()) {
            throw std::runtime_error("Incompatible column types. ");
        }

        std::vector<TableColumn*> resultCols;

        for (auto& col : table1) {
            resultCols.push_back(col->clone());
        }

        for (auto& col : table2) {
            if (col = col2) {
                continue;
            }
            resultCols.push_back(col->clone());
        }

        for (int i = 0; i < col1->getSize(); ++i) {
            for (int j = 0; j < col2->getSize(); ++j) {
                if (col1->returnValueAtGivenIndexAsString(i) == col2->returnValueAtGivenIndexAsString(j)) {
                    int i = 0;
                    for (auto& col : table1) {
                        resultCols[i]->addCell(col->returnValueAtGivenIndexAsString(i));
                    }

                    for (int k = 0; k < table2.getNumberOfColumns(); ++k) {
                        if (k == column2) {
                            continue;
                        }
                        resultCols[table1.getNumberOfColumns() + k - 1]->
                            addCell(table2.getColumnAtGivenIndex(k)->
                                returnValueAtGivenIndexAsString(j));
                      
                    }
                }
            }
        }
        //TODO think of file path
        Table resTable(resultCols, "Inner join result", "");
        outputFileWritter.writeTableToFile(resTable, "");
    }
    catch (const std::exception& e) {
        outputConsoleWriter.printLine(e.what());
    }

}

void CatalogCommandManager::rename(const std::string& oldName, const std::string& newName)
{
    if (!loadedCatalogExists) {
        throw std::runtime_error("There is no file opened! ");
    }
    try {
        Table table = loadedCatalog.returnTableByName(oldName);
        table.setName(newName);
    }
    catch (const std::exception& e) {
        outputConsoleWriter.printLine(e.what());
    }
}

void CatalogCommandManager::count(const std::string& tableName, int searchColumn, std::string searchValue)
{
    if (!loadedCatalogExists) {
        throw std::runtime_error("There is no file opened! ");
    }
    try {
        Table table = loadedCatalog.returnTableByName(tableName);

        int counter = 0;

        for (auto& col : table) {
            if (col->matchesValues(searchColumn, searchValue)) {
                counter++;
            }
        }
        outputConsoleWriter.printLine("Column number " + std::to_string(searchColumn)
            + " of table " + tableName + " contains " + searchValue + std::to_string(counter) 
            + " amount of times. ");
    }
    catch (const std::exception& e) {
        outputConsoleWriter.printLine(e.what());
    }
}

void CatalogCommandManager::agregate(const std::string& tableName,
    int searchColumn,
    std::string seacrhValue,
    int targetColumn,
    std::string operation)
{
    if (!loadedCatalogExists) {
        throw std::runtime_error("There is no file opened! ");
    }
    try {
        Table table = loadedCatalog.returnTableByName(tableName);
        if (searchColumn > table.getColumnAtGivenIndex(0)->getSize() && searchColumn < 0) {
            throw std::out_of_range("Invalid search column index. ");
        }

        if (targetColumn > table.getColumnAtGivenIndex(0)->getSize() && targetColumn < 0) {
            throw std::out_of_range("Invalid target column index. ");
        }

        TableColumn* col1 = table.getColumnAtGivenIndex(searchColumn);
        TableColumn* col2 = table.getColumnAtGivenIndex(targetColumn);

        if ((col1->getType() != ColumnType::INTEGER || col2->getType() != ColumnType::INTEGER) &&
            (col1->getType() != ColumnType::DOUBLE || col2->getType() != ColumnType::DOUBLE)) {
            throw std::runtime_error("Incompatible column types. ");
        }

        std::vector<double> cells;

        for (int i = 0; i < table.getColumnAtGivenIndex(0)->getSize(); i++) {
            if (col1->matchesValues(i, seacrhValue)) {
                std::string valStr = col1->returnValueAtGivenIndexAsString(i);
                double val = std::stod(valStr);
                cells.push_back(val);
            }
        }

        if (cells.size() == 0) {
            throw std::runtime_error("No matching rows found.");

        }
        if (operation == "sum") {
            double val = Operations::sum(cells);

            outputConsoleWriter.printLine(std::to_string(val));
        }
        else if (operation == "product") {
            double val = Operations::product(cells);

            outputConsoleWriter.printLine(std::to_string(val));
        }
        else if (operation == "maximum") {
         
            double val = Operations::max(cells);

            outputConsoleWriter.printLine(std::to_string(val));
        }
        else if (operation == "minimum") {
            double val = Operations::min(cells);

            outputConsoleWriter.printLine(std::to_string(val));
        }
        else {
            throw std::invalid_argument("Unknown aggregate operation: " + operation);
        }

    }
    catch (const std::exception& e) {
        outputConsoleWriter.printLine(e.what());
    }

}

void CatalogCommandManager::setLoadedCatalog(Catalog catalog) {
	this->loadedCatalog = catalog;
	this->loadedCatalogExists = true;
}

void CatalogCommandManager::closeLoadedCatalog() {
    this->loadedCatalogExists = false;
}