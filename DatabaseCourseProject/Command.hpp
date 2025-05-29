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
#include "CommandContext.hpp"

/**
 * @class Command
 * @brief Abstract base class for all command operations.
 *
 * This class defines a uniform interface for executing operations such as
 * `open`, `insert`, `save`, etc. All concrete command classes should
 * inherit from this interface and implement the `execute` method.
 */
class Command {
public:
    /**
     * @brief Executes the command with the given parameters.
     *
     * @param params A list of strings representing the arguments passed to the command.
     */
    virtual void execute(const std::vector<std::string>& params) = 0;

    /**
     * @brief Virtual destructor for safe polymorphic cleanup.
     */
    virtual ~Command() = default;
};
