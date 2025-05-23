#include "IOUtils.hpp"

void IOUtils::printInPageFormat(
    std::vector<std::string> rows,
    const OutputConsoleWritter& ocw,
    const InputConsoleReader icr) {

    const size_t pageSize = 10;
    size_t currentPage = 0;
    size_t totalPages = (rows.size() + pageSize - 1) / pageSize;

    std::string command;

    while (true) {
        ocw.printLine("Page " + std::to_string(currentPage + 1) + " of " + std::to_string(totalPages));

        int start = currentPage * pageSize;
        int end = std::min(start + pageSize, rows.size());

        for (int i = 0; i < end; ++i) {
            ocw.printLine(rows[i]);

        }

        ocw.printLine("\nCommands: next, prev, exit\n");
        icr.readLine();

        if (command == "next") {
            if (currentPage + 1 < totalPages) {
                ++currentPage;
            }
            else {
                ocw.printLine("Already on last page. ");
                break;
            }
        }
        else if (command == "prev") {
            if (currentPage > 0) {
                --currentPage;
            }
            else {
                ocw.printLine("Already on first page. ");
            }
        }
        else if (command == "exit") {
            break;
        }
        else {
            ocw.printLine("Unknown command. Use next, prev, or exit. ");
        }
    }
}