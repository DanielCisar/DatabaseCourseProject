#include "CatalogCommandsManager.hpp"
#include "IOUtils.hpp"
#include <stdexcept>
#include "Operations.hpp"

CatalogCommandManager::CatalogCommandManager(
    InputFileReader fileReader,
    OutputConsoleWritter outputConsoleWriter,
    OutputFileWritter outputFileWritter,
    InputConsoleReader inputConsoleReader) :
    loadedCatalog(nullptr),
    fileReader(fileReader),
    outputConsoleWriter(outputConsoleWriter),
    outputFileWritter(outputFileWritter),
    inputConsoleReader(inputConsoleReader)
{
}

CatalogCommandManager::~CatalogCommandManager()
{
    delete this->loadedCatalog;
}

bool CatalogCommandManager::loadedCatalogExists() {
    if (loadedCatalog == nullptr) {
        return false;
    }
    return true;
}

void CatalogCommandManager::import(const std::string& filepath)
{
    if (!loadedCatalogExists) {
        throw std::runtime_error("There is no file opened! ");
    }

    try {
        Table table = fileReader.readTableFromFile(filepath);

        loadedCatalog->addTable(table);

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

    for (auto& table : *loadedCatalog) {
        outputConsoleWriter.printLine(table.getName());
    }
}

void CatalogCommandManager::describe(const std::string& name)
{
    if (!loadedCatalogExists) {
        throw std::runtime_error("There is no file opened! ");
    }

    try {
        Table table = loadedCatalog->returnTableByName(name);
        
        int index = 0;

        for (auto& col : table) {
            outputConsoleWriter.printLine(
                "Type of column " + std::to_string(index) + ": " + col->getTypeAsString()
            );
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
        Table table = loadedCatalog->returnTableByName(name);
        const int pageSize = 10;
        int currentPage = 0;

        int totalRows = table.getNumberOfColumns();
        int totalPages = (totalRows + pageSize - 1) / pageSize;

        std::string command;

        outputConsoleWriter.printLine("Table: " + name);

        std::vector<std::string> rows;

        for (int i = 0; i < table.getNumberOfColumns(); i++) {
            for (auto& col : table) {
                rows.push_back(col->returnValueAtGivenIndexAsString(i));
            }

        }

        IOUtils::printInPageFormat(rows, outputConsoleWriter, inputConsoleReader);

    }
    catch (const std::exception& e) {
        outputConsoleWriter.printLine(e.what());
    }

}

void CatalogCommandManager::select(int numberOfColumn, std::string value, const std::string& name)
{
    try {
        Table table = loadedCatalog->returnTableByName(name);

        if (!loadedCatalogExists) {
            throw std::runtime_error("There is no file opened! ");
        }

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
    Table table = loadedCatalog->returnTableByName(tableName);

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

void CatalogCommandManager::update(const std::string& tableName,
    int searchColumn,
    std::string searchValue,
    int targetColumn,
    std::string targetValue)
{
    try {
        Table table = loadedCatalog->returnTableByName(tableName);

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
    try {
        Table table = loadedCatalog->returnTableByName(tableName);

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
    try {
        Table table = loadedCatalog->returnTableByName(tableName);

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

Table CatalogCommandManager::innerJoin(const std::string& tableName1,
    int column1,
    const std::string& tableName2,
    int column2)
{
    try {
        Table table1 = loadedCatalog->returnTableByName(tableName1);
        Table table2 = loadedCatalog->returnTableByName(tableName2);

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
        return Table(resultCols, "Inner join result", "");
    }
    catch (const std::exception& e) {
        outputConsoleWriter.printLine(e.what());
    }

}

void CatalogCommandManager::rename(const std::string& oldName, const std::string& newName)
{
    try {
        Table table = loadedCatalog->returnTableByName(oldName);
        table.setName(newName);
    }
    catch (const std::exception& e) {
        outputConsoleWriter.printLine(e.what());
    }
}

int CatalogCommandManager::count(const std::string& tableName, int searchColumn, std::string searchValue)
{
    try {
        Table table = loadedCatalog->returnTableByName(tableName);

        int counter = 0;

        for (auto& col : table) {
            if (col->matchesValues(searchColumn, searchValue)) {
                counter++;
            }
        }
        return counter;
    }
    catch (const std::exception& e) {
        outputConsoleWriter.printLine(e.what());
    }
}

double CatalogCommandManager::agregate(const std::string& tableName,
    int searchColumn,
    std::string seacrhValue,
    int targetColumn,
    std::string operation)
{
    try {
        Table table = loadedCatalog->returnTableByName(tableName);
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
            return Operations::sum(cells);
        }
        else if (operation == "product") {
            return Operations::product(cells);
        }
        else if (operation == "maximum") {
            return Operations::max(cells);
        }
        else if (operation == "minimum") {
            return Operations::min(cells);
        }
        else {
            throw std::invalid_argument("Unknown aggregate operation: " + operation);
        }

    }
    catch (const std::exception& e) {
        outputConsoleWriter.printLine(e.what());
    }

}
