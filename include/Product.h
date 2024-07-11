#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <map>
#include "ChangeItem.h"

// Constants
const int PRODUCT_NAME_LENGTH = 30 +1;
const int RELEASE_ID_LENGTH = 8 +1;
const int RELEASE_DATE_LENGTH = 10 +1;

// ============================================
// Data structures
// ============================================
struct Product {
	// Note: 1 extra for the null terminator
    char name[PRODUCT_NAME_LENGTH];
};

struct ProductRelease {
	char productName[PRODUCT_NAME_LENGTH];
	char releaseID[RELEASE_ID_LENGTH];
	char releaseDate[RELEASE_DATE_LENGTH];
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
void createProductRelease(const std::string& productName, const std::string& releaseID, const std::string& releaseDate);

#endif // PRODUCT_H
