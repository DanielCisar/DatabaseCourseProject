#pragma once

#include "OutputConsoleWritter.hpp"
#include "InputConsoleReader.hpp"
#include "InputFileReader.hpp"
#include "OutputFileWritter.hpp"
#include "Catalog.hpp"


/**
 * @struct CommandContext
 * @brief Shared execution context passed to all command classes.
 *
 * Holds references to I/O utilities and the currently loaded catalog,
 * allowing command objects to operate in a consistent environment.
 */
struct CommandContext {

    /**
     * @brief Command-line parameters passed to the current command.
     */
    std::vector<std::string> params;

    /**
    * @brief Reference to the currently loaded catalog (database).
    */
    Catalog& loadedCatalog;

    /**
     * @brief Indicates whether a catalog is currently loaded.
     */
    bool loadedCatalogExists;

    /**
    * @brief Console writer for output.
    */
    OutputConsoleWritter& outputConsoleWritter;

    /**
     * @brief Console reader for input.
     */
    InputConsoleReader& inputConsoleReader;

    /**
     * @brief File writer used to save data to disk.
     */
    OutputFileWritter& outputFileWritter;

    /**
     * @brief File reader used to load data from disk.
     */
    InputFileReader& inputFileReader;

    /**
     * @brief Constructs a new CommandContext.
     *
     * @param loadedCatalogRef Reference to the current catalog.
     * @param outputConsoleWritter Reference to console writer.
     * @param inputConsoleReader Reference to console reader.
     * @param outputFileWritter Reference to file writer.
     * @param inputFileReader Reference to file reader.
     */
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