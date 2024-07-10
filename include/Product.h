#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <map>
#include "ChangeItem.h"

// ============================================
// Data structures
// ============================================
struct Product {
    std::string name;
    std::map<std::string, ChangeItem> changeItems;
    std::map<std::string, std::string> releases;
};

struct ProductRelease {
	std::string productName;
	std::string releaseID;
	std::string releaseDate;
};

// ============================================
// Function Declarations
// ============================================
void openProductFile();
void closeProductFile();
void writeProduct(const Product& product);
void seekToBeginningOfProductFile();
bool getNextProduct(Product& product);
void createProduct(const std::string& name);
void createRelease(const std::string& productName, const std::string& releaseID, const std::string& releaseDate);

#endif // PRODUCT_H
