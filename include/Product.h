// ============================================
// Module Name: Product.h
// ============================================
// Version History:
// Rev. 2 - 2024/07/17 - Group 7
// ============================================

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

// ---------------------------------------------------------
// Opens the Product file
void openProductFile();

// ---------------------------------------------------------
// Closes the Product file
void closeProductFile();

// ---------------------------------------------------------
// Writes a Product to the file
void writeProduct(
    // Parameter: product (The Product to write)
    const Product& product  // in
);

// ---------------------------------------------------------
// Seeks to the beginning of the Product file
void seekToBeginningOfProductFile();

// ---------------------------------------------------------
// Displays a Product
void displayProduct(
    // Parameter: product (The Product to display)
    const Product& product  // in
);

// ---------------------------------------------------------
// Displays the first 20 or fewer Products in the file
int productFileDisplay20OrLess(
    // Parameter: filename (The name of the file to display Products from)
    int& page   // in/out
);

// ---------------------------------------------------------
bool retrieveProductByName(
    // Retrieves a Product by its name
    // Parameter: filename (The name of the file to retrieve the Product from)
    // Parameter: productName (The name of the Product)
    // Parameter: product (The Product object to store the retrieved data)
    // Returns: bool (true if retrieval was successful, false otherwise)
    const char* filename,    // in   
    const char* productName,    // in
    Product& product    // out
);

// ---------------------------------------------------------
// Creates a new Product
void createProduct(
    // Parameter: namePtr (The name of the Product)
    const char* namePtr    // in
); 

// ============================================
// Function Declarations: Product Release
// ============================================
// ---------------------------------------------------------
// Opens the ProductRelease file
void openProductReleaseFile();

// ---------------------------------------------------------
// Closes the ProductRelease file
void closeProductReleaseFile();

// ---------------------------------------------------------
// Writes a ProductRelease to the file
void writeProductRelease(
    // Parameter: productRelease (The ProductRelease to write)
    const ProductRelease& productRelease
);

// ---------------------------------------------------------
// Seeks to the beginning of the ProductRelease file
void seekToBeginningOfProductReleaseFile();

// ---------------------------------------------------------
void displayProductRelease(
    // Displays a ProductRelease
    // Parameter: productRelease (The ProductRelease to display)
    const ProductRelease& productRelease
);

// ---------------------------------------------------------
// Displays the first 20 or fewer ProductReleases in the file
int productReleaseFileDisplay20OrLess(
    // Parameter: filename (The name of the file to display ProductReleases from)
    int& page,   // in/out
	const char* productName		// in
);

// ---------------------------------------------------------
bool retrieveProductReleaseByKey(
    // Retrieves a ProductRelease by its key (product name and release ID)
    // Parameter: filename (The name of the file to retrieve the ProductRelease from)
    // Parameter: productReleaseName (The name of the product associated with the ProductRelease)
    // Parameter: releaseID (The release ID of the ProductRelease)
    // Parameter: productRelease (The ProductRelease object to store the retrieved data)
    // Returns: bool (true if retrieval was successful, false otherwise)
    const char* filename,     // in
    const char* productReleaseName,    // in
    const char* releaseID,    // in
    ProductRelease& productRelease    // out
);

// ---------------------------------------------------------
void createProductRelease(
    // Creates a new ProductRelease
    // Parameter: productName (The name of the product associated with the ProductRelease)
    // Parameter: releaseID (The release ID of the ProductRelease)
    // Parameter: releaseDate (The release date of the ProductRelease)
    const char* productName,    // in
    const char* releaseID,    // in
    const char* releaseDate    // in
);

// ---------------------------------------------------------
bool determineReleaseIDExistence(
    // Determines if a given release ID exists
    // Parameter: releaseID (The release ID to check for existence)
    // Returns: bool (true if the release ID exists, false otherwise)
    const char* releaseID    // in
);

#endif // PRODUCT_H