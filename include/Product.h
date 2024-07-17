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


// Opens the Product file
void openProductFile();

// Closes the Product file
void closeProductFile();

// Writes a Product to the file
// Parameter: product (The Product to write)
void writeProduct(const Product& product);

// Seeks to the beginning of the Product file
void seekToBeginningOfProductFile();


// Displays a Product
// Parameter: product (The Product to display)
void displayProduct(const Product& product);


// Displays the first 20 or fewer Products in the file
// Parameter: filename (The name of the file to display Products from)
void productFileDisplay20OrLess(const char* filename);

// Retrieves a Product by its name
// Parameter: filename (The name of the file to retrieve the Product from)
// Parameter: productName (The name of the Product)
// Parameter: product (The Product object to store the retrieved data)
// Returns: bool (true if retrieval was successful, false otherwise)
bool retrieveProductByName(const char* filename, const char* productName, Product& product);


// Creates a new Product
// Parameter: namePtr (The name of the Product)
void createProduct(const char* namePtr); 

// ============================================
// Function Declarations: Product Release
// ============================================


// Opens the ProductRelease file
void openProductReleaseFile();

// Closes the ProductRelease file
void closeProductReleaseFile();

// Writes a ProductRelease to the file
// Parameter: productRelease (The ProductRelease to write)
void writeProductRelease(const ProductRelease& productRelease);

// Seeks to the beginning of the ProductRelease file
void seekToBeginningOfProductReleaseFile();

// Displays a ProductRelease
// Parameter: productRelease (The ProductRelease to display)
void displayProductRelease(const ProductRelease& productRelease);

// Displays the first 20 or fewer ProductReleases in the file
// Parameter: filename (The name of the file to display ProductReleases from)
void productReleaseFileDisplay20OrLess(const char* filename);

bool retrieveProductReleaseByKey(const char* filename, const char* productReleaseName, const char* releaseID, ProductRelease& productRelease);
void createProductRelease(const char* productName, const char* releaseID, const char* releaseDate);
bool determineReleaseIDExistence(const char* releaseID);

#endif // PRODUCT_H
