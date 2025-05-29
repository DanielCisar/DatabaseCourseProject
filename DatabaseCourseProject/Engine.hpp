#pragma once
#include "CommandContext.hpp"
#include "Command.hpp"
#include "OutputConsoleWritter.hpp"
#include "InputConsoleReader.hpp"
#include <unordered_map>
#include <memory>
#include <vector>
#include <string>

class Engine {
public:
    Engine(
        OutputConsoleWritter& outputConsoleWritter,
        InputConsoleReader& inputConsoleReader,
        OutputFileWritter& outputFileWritter,
        InputFileReader& inputFileReader
    );

	~Engine();

   
    void run();

private:
    void dispatchCommand(const std::vector<std::string>& params);

    Catalog loadedCatalog; 
    CommandContext context;
    std::unordered_map<std::string, Command*> commands;
};
