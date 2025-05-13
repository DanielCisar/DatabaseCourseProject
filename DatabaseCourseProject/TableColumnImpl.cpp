#include "TableColumn.hpp"
#include <vector>	
#include <string>

TableColumn::TableColumn(std::string name, std::string type) : name(name), type(type){

}
TableColumn::~TableColumn() {

}

template <typename T>
bool TableColumn::checkEquivelenceBetweenColumnAndType(const T& value) {
	if (std::is_integral<T>::value && type == "Integer") {
		return true;
	}
	else if (std::is_floating_point<T>::value && type == "Double") {
		return true;
	}
	else if (std::is_same<T, std::string>::value && type == "String") {
		return true;
	}
	return false;
}

std::string TableColumn::getName() const{
	return this->name;
}
std::string TableColumn::getType() const{
	return this->type;
}
std::vector<std::string> TableColumn::getContent() const{
	return this->content;
}

template <typename T>
int TableColumn::findIndexOfGivenCell(T value) const{
	int i = 0;
	for (std::string cell : content) {
		if (std::is_same<T, std::string>::value) {
			if (cell == value) {
				return i;
			}
		}
		else {
			std::stringstream ss(cell);
			T cellValue;
			ss >> cellValue;

			if (!ss.fail() && ss.eof() && cellValue == value) {
				return i;
			}
		}

		i++;
	}
	return -1;
}
template <typename T>
void TableColumn::changeValueAtGivenIndex(int index, T value) {
	if (!checkEquivelenceBetweenColumnAndType(value)) {
		throw std::invalid_argument("This column doesn't accept this value type. ");
	}
	content[index] = std::to_string(value);
}

std::string TableColumn::returnValueAtGivenIndex(int index) const {
	return content[index];
}