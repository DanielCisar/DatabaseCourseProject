#pragma once

#include <memory>
#include "OutputConsoleWritter.hpp"
#include "InputConsoleReader.hpp"
#include "InputFileReader.hpp"
#include "OutputFileWritter.hpp"
#include "Catalog.hpp"



struct CommandContext {
    std::vector<std::string> params;
    Catalog& loadedCatalog;
    bool loadedCatalogExists;

    OutputConsoleWritter& outputConsoleWritter;
    InputConsoleReader& inputConsoleReader;
    OutputFileWritter& outputFileWritter;
    InputFileReader& inputFileReader;

    CommandContext(
        Catalog& loadedCatalogRef,
        OutputConsoleWritter& outputConsoleWritter,
        InputConsoleReader& inputConsoleReader,
        OutputFileWritter& outputFileWritter,
        InputFileReader& inputFileReader
    )
        : loadedCatalog(loadedCatalogRef),
        loadedCatalogExists(false),
        outputConsoleWritter(outputConsoleWritter),
        inputConsoleReader(inputConsoleReader),
        outputFileWritter(outputFileWritter),
        inputFileReader(inputFileReader)
    {}

};