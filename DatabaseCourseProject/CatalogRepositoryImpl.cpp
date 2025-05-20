#include "CatalogRepository.hpp"
#include <stdexcept>

CatalogRepository::CatalogRepository() {

}
CatalogRepository::~CatalogRepository() {

}

void CatalogRepository::addCatalog(const Catalog& catalog) {
	this->catalogs.push_back(catalog);
}
Catalog& CatalogRepository::getCatalogByPath(const std::string& path) {
	for (auto& catalog : catalogs) {
		if (catalog.getPath() == path) {
			return catalog;
		}
	}
	throw std::invalid_argument("No catalog with this path exists! ");
}
