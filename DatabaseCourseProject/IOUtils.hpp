#pragma once
#include <vector>
#include <string>
#include "OutputConsoleWritter.hpp"
#include "InputConsoleReader.hpp"

/**
 * @class IOUtils
 * @brief A static utility class for common input/output operations, particularly for paginated display.
 *
 * `IOUtils` encapsulates reusable functionality for interacting with the console,
 * specifically providing a method to display a large set of data in a user-friendly,
 * paginated format, allowing the user to navigate through pages.
 */
class IOUtils {
public:
    /**
    * @brief Prints a vector of strings to the console in a paginated format.
    *
    * This method displays the provided `rows` data page by page. It pauses after each page,
    * prompting the user to enter commands like "next", "prev", or "exit" to navigate
    * through the pages. The page size is fixed at 10 rows.
    *
    * @param rows A `std::vector<std::string>` containing the data rows to be displayed.
    * Each string in the vector is treated as a single line of output.
    * @param ocw A constant reference to an `OutputConsoleWritter` object, used for printing messages.
    * @param icr A constant reference to an `InputConsoleReader` object, used for reading user commands.
    */
    static void printInPageFormat(
        std::vector<std::string> rows,
        const OutputConsoleWritter& ocw,
        const InputConsoleReader& icr);
};