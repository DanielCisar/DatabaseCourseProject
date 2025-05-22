#include "CatalogCommandsManager.hpp"

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

        while (true) {
            outputConsoleWriter.printLine("Table: " + name);
            outputConsoleWriter.printLine("Page " + std::to_string(currentPage + 1) + " of " + std::to_string(totalPages));

            for (auto& col : table) {
                outputConsoleWriter.printLine(col->getName() + "\t");
            }
            std::cout << "\n";

            int start = currentPage * pageSize;
            int end = std::min(start + pageSize, totalRows);
            
            for (int i = start; i < end; i++) {
                std::vector<std::string> row;
                for (auto& col : table) {
                    outputConsoleWriter.printLine(col->returnValueAtGivenIndexAsString(i) + "\t");
                }
                std::cout << "\n";

            }

            outputConsoleWriter.printLine("\nCommands: next, prev, exit\n");
            inputConsoleReader.readLine();

            if (command == "next") {
                if (currentPage + 1 < totalPages) {
                    ++currentPage;
                }
                else {
                    outputConsoleWriter.printLine("Already on last page. ");
                }
            }
            else if (command == "prev") {
                if (currentPage > 0) {
                    --currentPage;
                }
                else {
                    outputConsoleWriter.printLine("Already on first page. ");
                }
            }
            else if (command == "exit") {
                break;
            }
            else {
                outputConsoleWriter.printLine("Unknown command. Use next, prev, or exit. ");
            }
        }

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

    TableColumn* columnToSearch = loadedCatalog->returnTableByName(name).getColumnAtGivenIndex(numberOfColumn);

    if (numberOfColumn < 0 || numberOfColumn >= columnToSearch->getSize()) {
        throw std::out_of_range("Invalid column index");
    }

    int size = columnToSearch->getSize();

    for (int i = 0; i < size; i++) {
        if (columnToSearch->matchesValues(i, value)) {
            
        }
    }
}

void CatalogCommandManager::addColumn(const std::string& tableName,
    const std::string& columnName,
    std::string columnType)
{
}

void CatalogCommandManager::update(const std::string& tableName,
    int searchColumn,
    std::string searchValue,
    int targetColumn,
    std::string targetValue)
{
}

void CatalogCommandManager::deleteRows(const std::string& tableName,
    int searchColumn,
    std::string searchValue)
{
}

void CatalogCommandManager::insert(const std::string& tableName, std::vector<std::string> values)
{
}

void CatalogCommandManager::innerJoin(const std::string& tableName1,
    int column1,
    const std::string& tableName2,
    int column2)
{
}

void CatalogCommandManager::rename(const std::string& oldName, const std::string& newName)
{
}

int CatalogCommandManager::count(const std::string& tableName, int searchColumn, std::string searchValue)
{
    return 0;
}

void CatalogCommandManager::agregate(const std::string& tableName,
    int searchColumn,
    std::string seacrhValue,
    int targetColumn,
    std::string operation)
{
}
