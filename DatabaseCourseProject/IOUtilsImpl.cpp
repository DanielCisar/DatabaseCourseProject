#include "IOUtils.hpp"

/**
 * @brief Prints a vector of strings to the console in a paginated format.
 *
 * This function iterates through the `rows` data, displaying them in chunks
 * defined by `pageSize`. It then prompts the user for navigation commands
 * ("next", "prev", "exit") using the provided `InputConsoleReader` and
 * prints output using the `OutputConsoleWritter`.
 *
 * @param rows The data rows to display.
 * @param ocw An `OutputConsoleWritter` instance for output.
 * @param icr An `InputConsoleReader` instance for input.
 */
void IOUtils::printInPageFormat(
    std::vector<std::string> rows,
    const OutputConsoleWritter& ocw,
    const InputConsoleReader& icr) {

    const size_t pageSize = 10;
    size_t currentPage = 0;
    size_t totalPages = (rows.size() + pageSize - 1) / pageSize;

    if (rows.empty()) {
        ocw.printLine("No rows to display.");
        return;
    }

    std::string command;

	bool validCommand = true;

    while (true) {
        if (validCommand) {

            int start = currentPage * pageSize;
            int end = std::min(start + pageSize, rows.size());

            for (int i = start; i < end; ++i) {
                ocw.printLine(rows[i]);
            }

            ocw.printLine("Page " + std::to_string(currentPage + 1) + " of "
                + std::to_string(totalPages));

            ocw.printLine("\nCommands: next, prev, exit\n");
        }
		ocw.print("Enter command: ");
        command = icr.readLineAsString();

        if (command == "next") {
            if (currentPage + 1 < totalPages) {
                ++currentPage;
                validCommand = true;
            }
            else {
                ocw.printLine("Already on last page. ");
                validCommand = false;
            }
        }
        else if (command == "prev") {
            if (currentPage > 0) {
                --currentPage;
                validCommand = true;
            }
            else {
                ocw.printLine("Already on first page. ");
				validCommand = false;
            }
        }
        else if (command == "exit") {
			ocw.printLine("Exiting pagination. ");
            break;
        }
        else {
            ocw.printLine("Unknown command. Use next, prev, or exit. ");
            validCommand = false;
        }
    }
}