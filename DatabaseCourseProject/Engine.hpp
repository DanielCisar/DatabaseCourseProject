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
 * @brief Core controller of the application. Manages command dispatching and input/output flow.
 *
 * The Engine initializes all supported commands using factories and maintains the main
 * event loop that reads user input and executes commands accordingly.
 */
class Engine {
public:
    /**
 * @brief Constructs the Engine and initializes available commands.
 *
 * @param outputConsoleWritter Handles console output.
 * @param inputConsoleReader Handles console input.
 * @param outputFileWritter Handles file output.
 * @param inputFileReader Handles file input.
 */
    Engine(
        OutputConsoleWritter& outputConsoleWritter,
        InputConsoleReader& inputConsoleReader,
        OutputFileWritter& outputFileWritter,
        InputFileReader& inputFileReader
    );

    /**
     * @brief Destructor. Frees memory allocated for commands.
     */

	~Engine();

    /**
      * @brief Starts the main loop of the engine.
      *
      * Reads commands from the console and dispatches them until 'exit' is entered.
      */
    void run();

private:
    /**
     * @brief Dispatches a command based on user input.
     *
     * @param params Parsed command-line parameters.
     */
    void dispatchCommand(const std::vector<std::string>& params);

    /// Currently loaded catalog used by commands.
    Catalog loadedCatalog; 

    /// Shared context passed to commands.
    CommandContext context;

    /// Map of supported command names to their corresponding Command objects.
    std::unordered_map<std::string, Command*> commands;
};
