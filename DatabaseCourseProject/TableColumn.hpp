#pragma once
#include <vector>
#include <string>

class TableColumn {
private:
	std::string name;
	std::vector<std::string> content;
	std::string type;

	template <typename T>
	bool checkEquivelenceBetweenColumnAndType(const T& value);

public:
	TableColumn(std::string name, std::string type);
	~TableColumn();

	std::string getName();
	std::string getType();
	std::vector<std::string> getContent();

	template <typename T>
	int findIndexOfGivenCell(T value);

	template <typename T>
	void changeValueAtGivenIndex(int index, T value);


};