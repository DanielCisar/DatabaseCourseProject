#pragma once

#include <memory>
#include "OutputConsoleWritter.hpp"
#include "InputConsoleReader.hpp"
#include "InputFileReader.hpp"
#include "OutputFileWritter.hpp"
#include "Catalog.hpp"



struct CommandContext {
    std::vector<std::string> params;
    std::shared_ptr<Catalog>& loadedCatalog;

    OutputConsoleWritter& outputConsoleWritter;
    InputConsoleReader& inputConsoleReader;
    OutputFileWritter& outputFileWritter;
    InputFileReader& inputFileReader;

    CommandContext(
        std::shared_ptr<Catalog>& loadedCatalogRef,
        OutputConsoleWritter& outputConsoleWritter,
        InputConsoleReader& inputConsoleReader,
        OutputFileWritter& outputFileWritter,
        InputFileReader& inputFileReader
    )
        : loadedCatalog(loadedCatalogRef),
        outputConsoleWritter(outputConsoleWritter),
        inputConsoleReader(inputConsoleReader),
        outputFileWritter(outputFileWritter),
        inputFileReader(inputFileReader)
    {}

};