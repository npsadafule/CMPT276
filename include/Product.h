#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <map>
#include "ChangeItem.h"

// Constants
const int PROD_NAME_LEN = 31;

// ============================================
// Data structures
// ============================================
struct Product {
	// Note: 1 extra for the null terminator
    char name[PROD_NAME_LEN];
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
void readProductFile(const char* filename, Product& product);
bool retrieveProductByName(const char* filename, const char* productName, Product& product);

void createProduct(const char* namePtr);
void createRelease(const std::string& productName, const std::string& releaseID, const std::string& releaseDate);

#endif // PRODUCT_H
