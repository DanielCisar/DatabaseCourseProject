#pragma once
#include <vector>
#include <string>
#include "OutputConsoleWriter.hpp"
#include "InputConsoleReader.hpp"

class IOUtils {
public:
    static void printInPageFormat(
        std::vector<std::string> rows,
        const OutputConsoleWritter& ocw,
        const InputConsoleReader icr);

		
};