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

	std::string getName() const;
	std::string getType() const;
	std::vector<std::string> getContent() const;

	template <typename T>
	int findIndexOfGivenCell(T value) const;

	template <typename T>
	void changeValueAtGivenIndex(int index, T value);

	std::string returnValueAtGivenIndex(int index) const;
};