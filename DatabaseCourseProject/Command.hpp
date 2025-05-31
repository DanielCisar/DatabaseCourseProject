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
     * @brief Virtual destructor for safe cleanup.
     */
    virtual ~Command() = default;

    /**
    * @brief Creates a deep copy of the current Command object.
    *
    * This pure virtual method enables polymorphic cloning. Each derived class
    * must implement this to return a new, dynamically allocated copy of itself.
    * The `newContext` parameter is provided to allow the cloned command to
    * be associated with a potentially different (or the same) `CommandContext`
    * if the cloning operation is part of copying the entire application state.
    *
    * @param newContext A reference to the `CommandContext` that the new cloned command should use.
    * @return A pointer to a newly allocated `Command` object, which is a deep copy of the current instance.
    * @warning The caller is responsible for `delete`ing the returned pointer to prevent memory leaks.
    */
    virtual Command* clone(CommandContext& newContext) const = 0;
};
