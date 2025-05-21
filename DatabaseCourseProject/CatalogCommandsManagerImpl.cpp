#include "CatalogCommandsManager.hpp"

CatalogCommandManager::CatalogCommandManager(
    InputFileReader fileReader,
    OutputConsoleWritter outputConsoleWriter,
    OutputFileWritter outputFileWritter) :
    loadedCatalog(nullptr),
    fileReader(fileReader),
    outputConsoleWriter(outputConsoleWriter),
    outputFileWritter(outputFileWritter)
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

}

void CatalogCommandManager::select(int numberOfColumn, std::string value, const std::string& name)
{
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
