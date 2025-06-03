#pragma once
#include "CommandContext.hpp"
#include "Command.hpp"
#include "OutputConsoleWritter.hpp"
#include "InputConsoleReader.hpp"
#include <unordered_map>
#include <vector>
#include <string>

/**
 * @class Engine
 * @brief Orchestrates the command-line database execution.
 *
 * The `Engine` class is the central controller responsible for
 * managing user input and output, and dispatching commands
 * It sets up the shared `CommandContext` which provides access to
 * the most important applicaton data and I/O handlers for all commands.
 * Commands are registered during initialization and executed based on user input.
 */
class Engine {
public:
    /**
     * @brief Constructs the Engine, initializes shared resources, and registers supported commands.
     *
     * This constructor sets up the `CommandContext` which contains the `Catalog`
     * and all necessary I/O handlers. It then uses `FileCommandFactory` and
     * `CatalogCommandFactory` to create and register all recognized commands.
     *
     * @param outputConsoleWritter A reference to the console output handler.
     * @param inputConsoleReader A reference to the console input handler.
     * @param outputFileWritter A reference to the file output handler for saving data.
     * @param inputFileReader A reference to the file input handler for loading data.
     */
    Engine(
        OutputConsoleWritter& outputConsoleWritter,
        InputConsoleReader& inputConsoleReader,
        OutputFileWritter& outputFileWritter,
        InputFileReader& inputFileReader
    );

    /**
     * @brief Copy constructor for the Engine class.
     *
     * Performs a deep copy of the `other` Engine object. 
     *
     * @param other The Engine object to be copied.
     */
    Engine(const Engine& other);

    /**
    * @brief Copy assignment operator for the Engine class.
    *
    * Enables deep copying of one Engine object's state to another. It first
    * cleans up any dynamically allocated `Command` objects currently held by
    * the left-hand side object, then performs a deep copy of the `loadedCatalog`
    * and all `Command` objects from the `other` (right-hand side) Engine.
    * Self-assignment is handled to prevent self-destruction.
    *
    * @param other The Engine object from which to copy.
    * @return A reference to the current Engine object (`*this`) after the copy.
    */
    Engine& operator=(const Engine& other);

    /**
     * @brief Destructor.
     *
     * Calls `clearMemory()` to clean up dynamically allocated `Command` objects
     * stored in the `commands` map, preventing memory leaks when an Engine object
     * is destroyed.
     */
    ~Engine();

    /**
    * @brief Move constructor for the Engine class.
    *
    * Constructs a new Engine object by efficiently transferring resources
    * from a temporary or expiring `other` Engine object.
    *
    * @param other The Engine object to be moved from.
    */
    Engine(Engine&& other) noexcept;

    /**
     * @brief Move assignment operator for the Engine class.
     *
     * Transfers resources from a temporary or expiring `other` Engine object
     * to the current Engine object. Self-assignment is handled.
     * The `other` object is left in a valid, but unspecified, state suitable for destruction.
     *
     * @param other The Engine object to be moved from (an rvalue reference).
     * @return A reference to the current Engine object (`*this`) after the move.
     */
    Engine& operator=(Engine&& other) noexcept;


    /**
    * @brief Starts the main application loop, continuously processing user commands.
    *
    * This method displays a welcome message and then enters a loop to:
    * 1. Prompt the user for input.
    * 2. Parse the raw input into command arguments.
    * 3. Dispatch the command.
    * 4. Continues until the "exit" command is entered, at which point the loop terminates.
    */
    void run();

private:
    /**
     * @brief Frees all dynamically allocated `Command` objects and clears the map.
     *
     * This private helper method iterates through the `commands` map, `delete`s
     * each `Command` object pointed to by the raw pointers, and then clears the map.
     * It is used by the destructor and the copy assignment operator to ensure
     * proper memory cleanup.
     */
    void clearMemory();

    /**
     * @brief Dispatches a command based on the provided arguments.
     *
     * This private helper method looks up the command name (the first argument)
     * in the `commands` map. If found, it attempts to execute the corresponding
     * `Command` object with the given arguments. If the command is not found,
     * an "Unknown command" message is printed to the console.
     * All exceptions thrown during command execution are caught and their
     * messages are displayed to the user.
     *
     * @param args A constant reference to a vector of strings representing
     * the parsed command name and its parameters. The first element
     * (`args[0]`) is the command name.
     */
    void dispatchCommand(const std::vector<std::string>& params);

    /// Currently loaded catalog used by commands.
    Catalog loadedCatalog; 

    /// Shared context passed to commands.
    CommandContext context;

    /// Map of supported command names to their corresponding Command objects.
    std::unordered_map<std::string, Command*> commands;
};
