#pragma once
#include <iostream>	
#include <string>

class OutputConsoleWritter {
public:
	OutputConsoleWritter();
	~OutputConsoleWritter();

	void printLine(const std::string& messsage) const;
	void print(const std::string& message) const;
};