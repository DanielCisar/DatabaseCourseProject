#include <iostream>
#include "OutputConsoleWriter.hpp"
#include <string>

OutputConsoleWritter::OutputConsoleWritter() {

}
OutputConsoleWritter::~OutputConsoleWritter() {

}

void OutputConsoleWritter::printLine(const std::string& messsage) const {
	std::cout << messsage << std::endl;
}