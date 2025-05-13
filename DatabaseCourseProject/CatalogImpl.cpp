#include "Catalog.hpp"
#include <vector>

Catalog::Catalog(const std::string catalogPath) : catalogPath(catalogPath){

}

Catalog::~Catalog() {

}

void Catalog::addTable(Table table) {
	tableCollection.push_back(table);
}

void Catalog::removeTable(int index) {
	tableCollection.erase(tableCollection.begin() + index);
}

std::vector<Table>::iterator Catalog::begin() {
	return tableCollection.begin();
}

std::vector <Table>::iterator Catalog::end() {
	return tableCollection.end();
}

Table Catalog::returnTableByName(std::string name) const{
	for (Table table : tableCollection) {
		if (table.getName() == name) {
			return table;
		}
	}
}