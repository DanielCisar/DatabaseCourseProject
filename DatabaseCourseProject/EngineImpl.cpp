#include "Engine.hpp"
#include "FileCommandFactory.hpp"
#include "CatalogCommandFactory.hpp"
#include "CommandParser.hpp"
#include "SupportedCommands.hpp"

Engine::Engine(OutputConsoleWritter& outputConsoleWritter,
    InputConsoleReader& inputConsoleReader,
    OutputFileWritter& outputFileWritter,
    InputFileReader& inputFileReader)
    : loadedCatalog(nullptr),
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

void Engine::run() {
    while (true) {
        std::string rawInput = context.inputConsoleReader.readLineAsString();
        std::vector<std::string> args = CommandParser::parseRawCommand(rawInput);

        if (args.empty()) {
            context.outputConsoleWritter.printLine("No command entered.");
            continue;
        }

        dispatchCommand(args);

        if (args[0] == "exit") { break; }
    }
}

void Engine::dispatchCommand(const std::vector<std::string>& args) {
    const std::string& commandName = args[0];

    auto it = commands.find(commandName);
    if (it != commands.end()) {
        try {
            it->second->execute(args);
        }
        catch (const std::exception& e) {
            context.outputConsoleWritter.printLine(e.what());
        }
    }
    else {
        context.outputConsoleWritter.printLine("Unknown command: " + commandName);
    }
}

Engine::~Engine() {
    for (auto& pair : commands) {
        delete pair.second;
    }
    commands.clear();
}