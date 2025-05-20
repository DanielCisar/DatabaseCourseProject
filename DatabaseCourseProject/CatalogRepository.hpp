#pragma once
#include <vector>
#include "Catalog.hpp"

class CatalogRepository {
private:
	std::vector<Catalog> catalogs;
	
public:
	CatalogRepository();
	~CatalogRepository();

	void addCatalog(const Catalog& catalog);
	Catalog& getCatalogByPath(const std::string& path);
};