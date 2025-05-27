#include "CatalogCommandManager.hpp"
#include "IOUtils.hpp"
#include <stdexcept>
#include "Operations.hpp"
#include "FileUtils.hpp"

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
}

CatalogCommandManager::~CatalogCommandManager()
{
}

void CatalogCommandManager::import(const std::string& filepath)
{
    if (!loadedCatalog) {
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
    if (!loadedCatalog) {
        throw std::runtime_error("There is no file opened! ");
    }

    outputConsoleWriter.printLine("List of tables: ");

    for (auto& table : *loadedCatalog) {
        outputConsoleWriter.printLine(table.getName());
    }
}

void CatalogCommandManager::exportTable(const std::string& name, const std::string& filepath) {
    Table table = loadedCatalog->returnTableByName(name);

    outputFileWritter.writeTableToFile(table, filepath);
    outputConsoleWriter.printLine("Table exported to: " + filepath);
}

void CatalogCommandManager::describe(const std::string& name)
{
    if (!loadedCatalog) {
        throw std::runtime_error("There is no file opened! ");
    }

    try {
        Table table = loadedCatalog->returnTableByName(name);

        int index = 1;

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
    if (!loadedCatalog) {
        throw std::runtime_error("There is no file opened! ");
    }

    try {
        Table table = loadedCatalog->returnTableByName(name);

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

        int size = table.getColumnAtGivenIndex(0)->getSize();

        for (int i = 0; i < size; i++) {
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
    if (!loadedCatalog) {
        throw std::runtime_error("There is no file opened! ");
    }
    try {
        Table table = loadedCatalog->returnTableByName(name);

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
    if (!loadedCatalog) {
        throw std::runtime_error("There is no file opened! ");
    }

    try {
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
        outputConsoleWriter.printLine("New empty column created. ");
    }
    catch (const std::exception& e) {
        outputConsoleWriter.printLine(e.what());
    }
}

void CatalogCommandManager::update(const std::string& tableName,
    int searchColumnIndex,
    std::string searchValue,
    int targetColumnIndex,
    std::string targetValue)
{
    if (!loadedCatalog) {
        throw std::runtime_error("There is no file opened! ");
    }
    try {
        Table& table = loadedCatalog->returnTableByName(tableName);

        TableColumn* searchCol = table.getColumnAtGivenIndex(searchColumnIndex);
        TableColumn* targetCol = table.getColumnAtGivenIndex(targetColumnIndex);

        int size = searchCol->getSize();

        for (int i = 0; i < size; ++i) {
            if (searchCol->matchesValues(i, searchValue)) {
                targetCol->changeValueAtIndex(i, targetValue);
            }
        }
        outputConsoleWriter.printLine("Update was successful. ");
    }
    catch (const std::exception& e) {
        outputConsoleWriter.printLine(e.what());
    }
}

void CatalogCommandManager::deleteRows(const std::string& tableName,
    int searchColumnIndex,
    std::string searchValue)
{
    if (!loadedCatalog) {
        throw std::runtime_error("There is no file opened! ");
    }

    try {
        Table& table = loadedCatalog->returnTableByName(tableName);

        TableColumn* searchCol = table.getColumnAtGivenIndex(searchColumnIndex);

        int size = searchCol->getSize();
        int deletedCount = 0;

        for (int i = size - 1; i >= 0; --i) {
            if (searchCol->matchesValues(i, searchValue)) {
                table.deleteGivenRow(i);
                deletedCount++;
            }
        }

        outputConsoleWriter.printLine("Deleted " + std::to_string(deletedCount) + " row(s).");

    }
    catch (const std::exception& e) {
        outputConsoleWriter.printLine(e.what());
    }
}

void CatalogCommandManager::insert(const std::string& tableName, std::vector<std::string> values)
{
    if (!loadedCatalog) {
        throw std::runtime_error("There is no file opened! ");
    }

    try {
        Table& table = loadedCatalog->returnTableByName(tableName);

        if (values.size() != table.getNumberOfColumns()) {
            throw std::runtime_error("Number of values is not equal to number of column. ");
        }
        int i = 0;
        for (auto& col : table) { 
            col->addCell(values[i]);
            ++i;
        }
        outputConsoleWriter.printLine("New row added successfuly. ");
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
    if (!loadedCatalog) {
        throw std::runtime_error("There is no file opened! ");
    }

    try {
        Table& table1 = loadedCatalog->returnTableByName(tableName1);
        Table& table2 = loadedCatalog->returnTableByName(tableName2);

        if (column1 >= table1.getColumnAtGivenIndex(0)->getSize() ||
            column2 >= table1.getColumnAtGivenIndex(0)->getSize()) {

            throw std::runtime_error("Invalid column index. ");
        }

        TableColumn* col1 = table1.getColumnAtGivenIndex(column1);
        TableColumn* col2 = table2.getColumnAtGivenIndex(column2);

        if (col1->getType() != col2->getType()) {
            throw std::runtime_error("Incompatible column types. ");
        }

        std::vector<TableColumn*> resultCols;

        for (auto& col : table1) {
            resultCols.push_back(col->clone());
        }

        for (auto& col : table2) {
            if (col == col2) {
                continue;
            }
            resultCols.push_back(col->clone());
        }

        for (int i = 0; i < col1->getSize(); ++i) {
            for (int j = 0; j < col2->getSize(); ++j) {
                if (col1->returnValueAtGivenIndexAsString(i) == col2->returnValueAtGivenIndexAsString(j)) {
                    int m = 0;
                    for (auto& col : table1) {
                        resultCols[m]->addCell(col->returnValueAtGivenIndexAsString(i));
                        ++m;
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
        std::string targetFolder = FileUtils::getDirectoryPath(table1.getFilename());
        std::string newName = "inner_join_of_" + table1.getName() + "_and_" + table2.getName();

        std::string newTablePath = targetFolder + "/" + newName + ".csv";

        Table resTable(resultCols, "Inner_join_result", newTablePath);
        outputFileWritter.writeTableToFile(resTable, newTablePath);
        outputConsoleWriter.printLine("The result of the operation was saved at: " + newTablePath);
    }
    catch (const std::exception& e) {
        outputConsoleWriter.printLine(e.what());
    }

}

void CatalogCommandManager::rename(const std::string& oldName, const std::string& newName)
{
    if (!loadedCatalog) {
        throw std::runtime_error("There is no file opened! ");
    }

    try {
        Table& table = loadedCatalog->returnTableByName(oldName);
        table.setName(newName);
        outputConsoleWriter.printLine("Table " + oldName + " has been renamed to " + newName);
    }
    catch (const std::exception& e) {
        outputConsoleWriter.printLine(e.what());
    }
}

void CatalogCommandManager::count(const std::string& tableName, int searchColumnIndex, std::string searchValue)
{
    if (!loadedCatalog) {
        throw std::runtime_error("There is no file opened! ");
    }

    try {
        Table& table = loadedCatalog->returnTableByName(tableName);

        int counter = 0;

        TableColumn* searchCol = table.getColumnAtGivenIndex(searchColumnIndex);
        int size = searchCol->getSize();

        for (int i = 0; i < size; i++) {
            if (searchCol->matchesValues(i, searchValue)) {
                counter++;
            }
        }

        outputConsoleWriter.printLine("Column number " + std::to_string(searchColumnIndex)
            + " of table " + tableName + " contains " + searchValue + " " + std::to_string(counter)
            + " time/times. ");
    }
    catch (const std::exception& e) {
        outputConsoleWriter.printLine(e.what());
    }
}

void CatalogCommandManager::aggregate(const std::string& tableName,
    int searchColumn,
    std::string seacrhValue,
    int targetColumn,
    std::string operation) 
{
    if (!loadedCatalog) {
        throw std::runtime_error("There is no file opened! ");
    }

    try {
        Table& table = loadedCatalog->returnTableByName(tableName);
        if (searchColumn >= table.getNumberOfColumns() || searchColumn < 0) {
            throw std::out_of_range("Invalid search column index. ");
        }

        if (targetColumn >= table.getNumberOfColumns() || targetColumn < 0) {
            throw std::out_of_range("Invalid target column index. ");
        }

        TableColumn* col1 = table.getColumnAtGivenIndex(searchColumn);
        TableColumn* col2 = table.getColumnAtGivenIndex(targetColumn);

        if (col2->getType() != ColumnType::INTEGER && col2->getType() != ColumnType::DOUBLE) {
            throw std::runtime_error("Incompatible column types. ");
        }

        std::vector<double> cells;

        for (int i = 0; i < table.getColumnAtGivenIndex(0)->getSize(); i++) {
            if (col1->matchesValues(i, seacrhValue)) {
                std::string valStr = col2->returnValueAtGivenIndexAsString(i);
                try {
                    double val = std::stod(valStr);
                    cells.push_back(val);
                }
                catch (...) {
                    throw std::runtime_error("Non-numeric value found in aggregation target column.");
                }

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

void CatalogCommandManager::setLoadedCatalog(std::shared_ptr<Catalog> catalog) {
    this->loadedCatalog = catalog;
}

void CatalogCommandManager::closeLoadedCatalog() {
    this->loadedCatalog.reset();
}

std::shared_ptr<Catalog> CatalogCommandManager::getCurrentLoadedFile() {
    return this->loadedCatalog;
}