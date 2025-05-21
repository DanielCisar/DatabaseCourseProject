#include "Catalog.hpp"
#include <vector>
#include <stdexcept>

Catalog::Catalog(const std::string catalogPath) : catalogPath(catalogPath){

}

Catalog::~Catalog() {

}

Catalog& Catalog::operator=(const Catalog& other) {
	if (this != &other) {
		this->tableCollection = other.tableCollection;
		this->catalogPath = other.catalogPath;
	}
	return *this;
}

void Catalog::addTable(Table table) {
	for (auto& t : tableCollection) {
		if (table.getName() == t.getName()) {
			throw std::runtime_error("Duplicate table name in catalog: " + table.getName());
		}
	}

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

std::string Catalog::getPath() const {
	return this->catalogPath;
}
