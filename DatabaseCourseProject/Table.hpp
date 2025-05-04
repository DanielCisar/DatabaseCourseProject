#pragma once
#include <string>
#include <vector>

struct TableColumn
{
	std::string type;
	std::vector<std::string> content;
	std::string name;
};

class Table {
private:
	std::vector<TableColumn> columns;
	std::string name;
	std::string filename;

public:
	Table(const std::vector<TableColumn> columns, const std::string name, const std::string filename);
	~Table();

	//TODO: Think about copy constructor and assignment operator and iterator

	std::string getName() const;

	std::string getFilename() const;

	std::vector<std::string> describe() const;

	void print() const;

	template<typename T>
	void select(int numberOfColumn, T value) const;

	void addColumn(std::string name, std::string type);

	template<typename T, typename U>
	void update(int searchColumn, T searchValue, int targetColumn, U targetValue);

	template<typename T>
	void deleteRow(int searchColumn, T searchValue);

	void insert(std::vector<std::string> values);

	void changeName(std::string newName);

	template<typename T>
	int count(int searchColumn, T value) const;

	template<typename T>
	void agregate(int searchColumn, T searchValue, int targetColumn, std::string operation);
};