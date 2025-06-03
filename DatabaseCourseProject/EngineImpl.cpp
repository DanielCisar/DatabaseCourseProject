#include "Engine.hpp"
#include "CommandContext.hpp"
#include "Catalog.hpp"
#include "OutputConsoleWritter.hpp"
#include "InputConsoleReader.hpp"
#include "OutputFileWritter.hpp"
#include "InputFileReader.hpp"
#include "Command.hpp" 
#include "FileCommandFactory.hpp"
#include "CatalogCommandFactory.hpp"
#include "CommandParser.hpp"
#include "SupportedCommands.hpp"
#include <stdexcept> 

/**
 * @brief Constructs the `Engine` and initializes its core components.
 *
 * This constructor takes references to necessary I/O and file handling
 * utilities, along with the `Catalog` itself, to construct the `CommandContext`.
 * It then populates the `commands` map using `FileCommandFactory`
 * and `CatalogCommandFactory` to create all supported `Command` objects.
 * Any errors during command creation (e.g., if a factory fails to produce a command)
 * are caught and printed to the console, but the engine initialization will still
 * attempt to complete for other commands.
 * 
 * @param outputConsoleWritter A reference to the console output writer.
 * @param inputConsoleReader A reference to the console input reader.
 * @param outputFileWritter A reference to the file output writer.
 * @param inputFileReader A reference to the file input reader.
 */
Engine::Engine(OutputConsoleWritter& outputConsoleWritter,
    InputConsoleReader& inputConsoleReader,
    OutputFileWritter& outputFileWritter,
    InputFileReader& inputFileReader)
    : loadedCatalog(Catalog()),
    context(loadedCatalog, outputConsoleWritter, inputConsoleReader, outputFileWritter, inputFileReader)
{

    for (const auto& name : SupportedCommands::returnSupportedFileCommands()) {
        try {
            commands[name] = FileCommandFactory::createCommand(name, context);
        }
        catch (const std::exception& e) {
            context.outputConsoleWritter.printLine(e.what());
        }
    }
    for (const auto& name : SupportedCommands::returnSupportedCatalogCommands()) {
        try {
            commands[name] = CatalogCommandFactory::createCommand(name, context);
        }
        catch (const std::exception& e) {
            context.outputConsoleWritter.printLine(e.what());
        }
    }
}

/**
 * @brief Starts the main application loop, continuously processing user commands.
 *
 * It begins by displaying a friendly welcome message and instructions. It then enters an
 * infinite loop:
 * 1.  It prompts the user for input (`>> `) and reads an entire line.
 * 2.  The raw input is then parsed into a vector of arguments using `CommandParser::parseRawCommand`,
 * which handles spaces and quoted strings.
 * 3.  The parsed arguments are passed to `dispatchCommand` for execution.
 * 4.  The loop continues until the user explicitly enters the "exit" command.
 * Upon receiving "exit", a goodbye message is printed, and the loop breaks,
 * terminating the application.
 */
void Engine::run() {

    context.outputConsoleWritter.printLine("===========================================");
    context.outputConsoleWritter.printLine("  Welcome to Database Course Project");
    context.outputConsoleWritter.printLine("  Type 'help' to see a list of commands.");
    context.outputConsoleWritter.printLine("  Type 'exit' to quit the program.");
    context.outputConsoleWritter.printLine("===========================================\n");

    while (true) {
        context.outputConsoleWritter.print(">> ");

        std::string rawInput = context.inputConsoleReader.readLineAsString();
        std::vector<std::string> args = CommandParser::parseRawCommand(rawInput);

        if (args.empty()) {
            context.outputConsoleWritter.printLine("No command entered.");
            continue;
        }

        dispatchCommand(args);

        if (args[0] == "exit") { 
            context.outputConsoleWritter.printLine("Goodbye!");
            break; 
        }

        context.outputConsoleWritter.printLine(""); 

    }
}

/**
 * @brief Dispatches a parsed command for execution.
 *
 * The method extracts the `commandName` from the `args` vector (which is always the
 * first element). It then attempts to find a matching `Command` object in the
 * `commands` `std::unordered_map`.
 *
 * If a command is found, its `execute` method is called with the provided arguments.
 * A `try-catch` block wraps the execution to catch any `std::exception` thrown
 * by the command, allowing the `Engine` to print the error message
 * to the console without crashing.
 *
 * If the `commandName` is not found in the `commands` map, an "Unknown command"
 * message is displayed  to the user, guiding them to available commands.
 *
 * @param params A constant reference to a `std::vector<std::string>` containing
 * the command name (at index 0) and its subsequent parameters.
 */
void Engine::dispatchCommand(const std::vector<std::string>& params) {
    const std::string& commandName = params[0];

    auto command = commands.find(commandName);
    if (command != commands.end()) {
        try {
            command->second->execute(params);
        }
        catch (const std::exception& e) {
            context.outputConsoleWritter.printLine(e.what());
        }
    }
    else {
        context.outputConsoleWritter.printLine("Unknown command: " + commandName);
    }
}

/**
 * @brief Destroys the `Engine` instance.
 *
 * This destructor calls the `clearMemory()` helper method to release all
 * dynamically allocated `Command` objects managed by this Engine instance,
 * preventing memory leaks.
 */
Engine::~Engine() {
    this->clearMemory();
}

/**
 * @brief Copy constructor for the Engine class.
 *
 * Performs a deep copy of the `other` Engine object.
 *
 * 1.  It first copies the `loadedCatalog` from `other.loadedCatalog`.
 * 2.  Then, it initializes the `context` of the new Engine instance. 
 * The new `context` is bound to *this* object's newly copied `loadedCatalog`,
 * while maintaining references to the same external I/O utilities
 * (console, file readers/writers) as the source `other` Engine.
 * 3.  Finally, it iterates through `other.commands` and performs a deep copy
 * of each `Command` object using its `clone()` method. Each cloned command
 * is then associated with the `context` of the *newly constructed* Engine.
 *
 * @param other The Engine object to be copied.
 */
Engine::Engine(const Engine& other)
    : loadedCatalog(other.loadedCatalog), 
    context(loadedCatalog, 
        other.context.outputConsoleWritter,
        other.context.inputConsoleReader,
        other.context.outputFileWritter,
        other.context.inputFileReader)
{
    for (const auto& pair : other.commands) {
        commands[pair.first] = pair.second->clone(context); 
    }
}

/**
 * @brief Copy assignment operator for the Engine class.
 *
 * Enables deep copying of one Engine object's state to another.
 *
 * 1.  It first checks for self-assignment (`this == &other`)
 * to prevent unnecessary operations and potential self-destruction.
 * 2.  All dynamically allocated `Command` objects currently owned by
 * the left-hand side object (`*this`) are `delete`d, and the `commands` map is cleared.
 * 3.  The `loadedCatalog` is copied from the `other` Engine.
 * 4.  The `CommandContext` needs to be effectively "re-bound" or
 * re-initialized to point to the newly copied `loadedCatalog` of `*this` object,
 * while retaining its references to the external I/O utilities. Note that direct
 * re-assignment of a reference member is not possible. The current implementation
 * implicitly assumes `context` can handle the `loadedCatalog` changing.
 * 5.  New, independent `Command` objects are created by
 * calling `clone()` on each command from the `other` Engine. 
 *
 * @param other The Engine object from which to copy.
 * @return A reference to the current Engine object (`*this`) after the copy.
 */
Engine& Engine::operator=(const Engine& other) {
    if (this == &other) { 
        return *this;
    }

    this->clearMemory();

    loadedCatalog = other.loadedCatalog; 

    for (const auto& pair : other.commands) {
        commands[pair.first] = pair.second->clone(context); 
    }

    return *this;
}

/**
 * @brief Frees all dynamically allocated `Command` objects and clears the map.
 *
 * This private helper method iterates through the `commands` map, `delete`s
 * each `Command*` object pointed to by the raw pointers, and then clears the map.
 * It is called by the destructor (`~Engine()`) and the copy assignment operator (`operator=`)
 * to ensure that memory is correctly managed and leaks are prevented.
 */
void Engine::clearMemory() {
    for (auto& pair : commands) {
        delete pair.second;
    }
    commands.clear();
}

/**
 * @brief Move constructor for the Engine class.
 *
 * Constructs a new Engine object by efficiently transferring resources
 * (the `loadedCatalog` and ownership of `Command` objects) from a temporary
 * or expiring `other` Engine object. This avoids expensive deep copies.
 *
 * 1.  The `loadedCatalog` is moved from `other.loadedCatalog`.
 * 2.  The `context` is initialized, binding to the *newly moved* `loadedCatalog`
 * of *this* Engine object. The references to external I/O utilities remain the same.
 * 3.  Ownership of the `Command` objects is transferred
 * from `other.commands` to `this->commands` using `std::move` on the map.
 * This leaves `other.commands` empty.
 *
 * @param other The Engine object to be moved from (an an rvalue reference).
 */
Engine::Engine(Engine&& other) noexcept
    : loadedCatalog(std::move(other.loadedCatalog)), 
    context(loadedCatalog,
        other.context.outputConsoleWritter,
        other.context.inputConsoleReader,
        other.context.outputFileWritter,
        other.context.inputFileReader),
    commands(std::move(other.commands)) 
{

}

/**
 * @brief Move assignment operator for the Engine class.
 *
 * Transfers resources from a temporary or expiring `other` Engine object
 * to the current Engine object. This operation frees any resources
 * currently held by `*this`, then efficiently moves the `loadedCatalog`
 * and ownership of `Command` objects from `other`. Self-assignment is handled.
 *
 * 1.  Prevents erroneous operations if `this` and `other` are the same object.
 * 2.  Calls `clearMemory()` to release existing `Command` objects owned by `*this`.
 * 3.  `loadedCatalog` is moved from `other.loadedCatalog`.
 * Ownership of `Command` objects (their raw pointers) is moved from `other.commands` to `this->commands`.
 * 4.  The `context` member is a value holding references.
 * After `loadedCatalog = std::move(other.loadedCatalog)`, the `context` of `*this`
 * implicitly operates on its now-updated `loadedCatalog`. The references to
 * external I/O objects remain unchanged.
 *
 * @param other The Engine object to be moved from (an rvalue reference).
 * @return A reference to the current Engine object (`*this`) after the move.
 */
Engine& Engine::operator=(Engine&& other) noexcept {
    if (this == &other) { 
        return *this;
    }

    this->clearMemory(); 

    loadedCatalog = std::move(other.loadedCatalog); 
    commands = std::move(other.commands);       

    return *this;
}