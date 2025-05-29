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
#include "OutputConsoleWritter.hpp"
#include "OutputFileWritter.hpp"
#include "InputConsoleReader.hpp"
#include <memory> 
#include "CommandContext.hpp"

class Command {
public:
    virtual void execute(const std::vector<std::string>& params) = 0;
    virtual ~Command() = default;
};