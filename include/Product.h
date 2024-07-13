#ifndef PRODUCT_H
#define PRODUCT_H

#include <cstring>
#include <string>
#include <map>

// Constants
// Note: 1 extra for the null terminator (using C-style strings)
const int PRODUCT_NAME_LENGTH = 30 +1;
const int RELEASE_ID_LENGTH = 8 +1;
const int RELEASE_DATE_LENGTH = 10 +1;

// ============================================
// Data structures
// ============================================
struct Product {
    char name[PRODUCT_NAME_LENGTH];
};

struct ProductRelease {
	char productName[PRODUCT_NAME_LENGTH];
	char releaseID[RELEASE_ID_LENGTH];
	char releaseDate[RELEASE_DATE_LENGTH];
};

// ============================================
// Function Declarations: Product
// ============================================
void openProductFile();
void closeProductFile();
void writeProduct(const Product& product);
void seekToBeginningOfProductFile();
bool getNextProduct(Product& product);
void readProductFile(const char* filename, Product& product);
bool retrieveProductByName(const char* filename, const char* productName, Product& product);

// NOTE: DOESNT APPEND, CHECK DUPLICATE
void createProduct(const char* namePtr); 

// ============================================
// Function Declarations: Product Release
// ============================================
void openProductReleaseFile();
void closeProductReleaseFile();
void writeProductRelease(const ProductRelease& productRelease);
void seekToBeginningOfProductReleaseFile();
bool getNextProductRelease(ProductRelease& productRelease);
void readProductReleaseFile(const char* filename, ProductRelease& productRelease);
bool retrieveProductReleaseByKey(const char* filename, const char* productReleaseName, const char* releaseID, ProductRelease& productRelease);

// NOTE: DOESNT APPEND, CHECK DUPLICATE
void createProductRelease(const char* productName, const char* releaseID, const char* releaseDate);

#endif // PRODUCT_H
