#include "Product.h"
#include <iostream>
#include <fstream>
#include <cstring>

// File handling functions
extern std::fstream productFile;
extern std::fstream productReleaseFile;

// ============================================
// Function Implementations: Product
// ============================================

// ---------------------------------------------------------
// Function: openProductFile
void openProductFile() {
    productFile.open("products.dat", std::ios::in | std::ios::out | std::ios::binary | std::ios::app);
    
	// Check if file opening worked properly, exit if it didn't
	if (!productFile.is_open()) exit(1);
}

// ---------------------------------------------------------
// Function: closeProductFile
void closeProductFile() {
    if (productFile.is_open()) {
        productFile.close();
    }
}

// ---------------------------------------------------------
// Function: writeProduct
void writeProduct(const Product& product) {
    if (!productFile.is_open()) return;

	// Get the character address of the product struct, write it a byte at a time (char),
	// writing "sizeof(Product)" amount of bytes  
	// Note: fixed-length writing as Product is a struct and attribute type fixes the struct size
    productFile.write(reinterpret_cast<const char*>(&product), sizeof(Product));

	// Check if we ran out of disk space; exit if we have
	if (!productFile.good()) exit(1);
}

// ---------------------------------------------------------
// Function: seekToBeginningOfProductFile
void seekToBeginningOfProductFile() {
    if (!productFile.is_open()) return;

	// Reset internal flags
    productFile.clear();

	// Set the position in the input sequence to the beginning of the file
	// Zero offest from the beginning of the file
    productFile.seekg(0, std::ios::beg);
}

void displayProduct(const Product& product) {
	std::cout << product.name << std::endl;
}

void productFileDisplay20OrLess(const char* filename) {
	const int MAX_READS = 20;

	Product tmpProduct;

	int counter = 0;
    while (productFile.read(reinterpret_cast<char*>(&tmpProduct), sizeof(Product)) &&
		   counter < MAX_READS) {
		displayProduct(tmpProduct);
		counter++;
    }
	productFile.clear();
}


// For retrieving a particular product with a particular name
bool retrieveProductByName(const char* filename, const char* productName, Product& product) {
    Product tmpProduct;

	seekToBeginningOfProductFile();

    // Read each product from the file and compare its name with the target name
    while (productFile.read(reinterpret_cast<char*>(&tmpProduct), sizeof(Product))) {
        if (std::strcmp(tmpProduct.name, productName) == 0) {
			
			// Store the product into the product outside of the function
			std::strcpy(product.name, tmpProduct.name);

            return true; // Product found
        }
    }
	// Clear out flags if we do not find the product
	if (!productFile.good()) {
		productFile.clear();
	}


    return false; // Product not found
}

// ---------------------------------------------------------
// Function: createProduct
void createProduct(const char* namePtr) { 
	// Create the product
    Product product = {};
	
	// Store the string into product's name attribute
	std::strcpy(product.name, namePtr);

	// Check if the product is on the file
	bool productExists = false;

	Product tmpProduct;

	seekToBeginningOfProductFile();
	
    if (!productFile.is_open()) {
        std::cerr << "Failed to open file for reading!" << std::endl;
        exit(1);
    }

	while (productFile.read(reinterpret_cast<char*>(&tmpProduct), sizeof(Product))) {
        if (std::strcmp(tmpProduct.name, namePtr) == 0) {
			productExists = true;
        }
    }

	// Clear flags if we didn't find the product
	if (!productFile.good()) {
		productFile.clear();
	}

	// If the product doesn't exist, append it to the end of the file
    if (!productExists) {
		writeProduct(product);
	}	
}




















































// ============================================
// Function Implementations: Product Release
// ============================================

// ---------------------------------------------------------
// Function: openProductReleaseFile
void openProductReleaseFile() {
    productReleaseFile.open("productReleases.dat", std::ios::in | std::ios::out | std::ios::binary | std::ios::app);
    
	// Check if file opening worked properly, exit if it didn't
	if (!productReleaseFile.is_open()) exit(1);
}

// ---------------------------------------------------------
// Function: closeProductReleaseFile
void closeProductReleaseFile() {
    if (productReleaseFile.is_open()) {
        productReleaseFile.close();
    }
}

// ---------------------------------------------------------
// Function: writeProductRelease
void writeProductRelease(const ProductRelease& productRelease) {
    if (!productReleaseFile.is_open()) return;

	// Get the character address of the product struct, write it a byte at a time (char),
	// writing "sizeof(Product)" amount of bytes  
	// Note: fixed-length writing as Product is a struct and attribute type fixes the struct size
	productReleaseFile.write(reinterpret_cast<const char*>(&productRelease), sizeof(ProductRelease));

	// Check if we ran out of disk space; exit if we have
	if (!productReleaseFile.good()) exit(1);
}

// ---------------------------------------------------------
// Function: seekToBeginningOfProductReleaseFile
void seekToBeginningOfProductReleaseFile() {
    if (!productReleaseFile.is_open()) return;

	// Reset internal flags
    productReleaseFile.clear();

	// Set the position in the input sequence to the beginning of the file
	// Zero offest from the beginning of the file
    productReleaseFile.seekg(0, std::ios::beg);
}

void displayProductRelease(const ProductRelease& productRelease) {
	std::cout << productRelease.productName <<
				 ", " << productRelease.releaseID <<
				 ", " << productRelease.releaseDate << std::endl;
}

void productReleaseFileDisplay20OrLess(const char* filename) {
	const int MAX_READS = 20;

	ProductRelease tmpPR;

	int counter = 0;
    while (productReleaseFile.read(reinterpret_cast<char*>(&tmpPR), sizeof(ProductRelease)) &&
		   counter < MAX_READS) {
		displayProductRelease(tmpPR);
		counter++;
    }
	productReleaseFile.clear();
}


// For retrieving a particular product with a particular key
bool retrieveProductReleaseByKey(const char* filename, const char* productReleaseName, const char* releaseID, ProductRelease& productRelease) {
	ProductRelease tmpProductRelease;

	seekToBeginningOfProductReleaseFile();

    while (productReleaseFile.read(reinterpret_cast<char*>(&tmpProductRelease), sizeof(ProductRelease))) {
		// If in the inFile, there exists an element that matches what we hope to retrieve
        if ((std::strcmp(tmpProductRelease.productName, productReleaseName) == 0) &&
			(std::strcmp(tmpProductRelease.releaseID, releaseID) == 0)) {
			
			// Store the product into the product outside of the function
			std::strcpy(productRelease.productName, tmpProductRelease.productName);
			std::strcpy(productRelease.releaseID, tmpProductRelease.releaseID);
			std::strcpy(productRelease.releaseDate, tmpProductRelease.releaseDate);

            return true; // Product found
        }
    }

    return false; // Product not found
}

// ---------------------------------------------------------
// Function: createProductRelease
void createProductRelease(const char* productName, const char* releaseID, const char* releaseDate) {	// Variables
	// Create the product release
	ProductRelease productRelease = {};
	
	// Store input strings to their corresponding attributes
	std::strcpy(productRelease.productName, productName);
	std::strcpy(productRelease.releaseID, releaseID);
	std::strcpy(productRelease.releaseDate, releaseDate);
	
	// Write it to file
	bool productReleaseExists = false;

    ProductRelease tmpProductRelease;

	seekToBeginningOfProductReleaseFile();

    // Read each product from the file and compare its name with the target name
	// std::cout << "before read loop" << std::endl;
    while (productReleaseFile.read(reinterpret_cast<char*>(&tmpProductRelease), sizeof(ProductRelease))) {
        if ((std::strcmp(tmpProductRelease.productName, productName) == 0) &&
			(std::strcmp(tmpProductRelease.releaseID, releaseID) == 0)) {
			productReleaseExists = true;
        }
    }
	productReleaseFile.clear();
	
	// If the product release doesn't exist, append it to the end of the file
    if (!productReleaseExists) {
		writeProductRelease(productRelease);
	}	
}

// Function: getNextChangeRequest
bool determineReleaseIDExistence(const char* releaseID) {
    ProductRelease tmpProductRelease;

	seekToBeginningOfProductReleaseFile();

	// Determine if the release exists
    while (productReleaseFile.read(reinterpret_cast<char*>(&tmpProductRelease), sizeof(ProductRelease))) {
		// If in the inFile, there exists an element that matches what we hope to retrieve
        if ((std::strcmp(tmpProductRelease.releaseID, releaseID) == 0)) {
            return true; // release ID found
        }
    }
	productReleaseFile.clear();

    return false; // release ID not found
}