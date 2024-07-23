// ============================================
// Module Name: Product.cpp
// ============================================
// Version History:
// Rev. 2 - 2024/07/17 - Group 7
// ============================================

// Overall internal design issues:
// This module implements both Products and Product Releases. Hence it uses "Product" and "ProductRelease" structs, imported from Product.h (see it for detailed list of attributes). It uses linear search to find products within files based on a criteria of attributes (e.g., primary key (single or compound)).

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
    // Opens the product file for reading and writing in binary append mode
    // Exits the program if the file fails to open
    productFile.open("products.dat", std::ios::in | std::ios::out | std::ios::binary | std::ios::app);
    
	// Check if file opening worked properly, exit if it didn't
	if (!productFile.is_open()) exit(1);
}

// ---------------------------------------------------------
// Function: closeProductFile
void closeProductFile() {
    // Closes the product file if it is open
    if (productFile.is_open()) {
        productFile.close();
    }
}

// ---------------------------------------------------------
// Function: writeProduct
void writeProduct(const Product& product) {
    // Writes a Product object to the product file
    // Exits the program if there is a failure while writing
    if (!productFile.is_open()) return;

	// Get the character address of the product struct, write it a byte at a time (char),
	// writing "sizeof(Product)" amount of bytes  
	// Note: fixed-length writing as Product is a struct and attribute type fixes the struct size
    productFile.write(reinterpret_cast<const char*>(&product), sizeof(Product));
	productFile.flush();

	// Check if we ran out of disk space; exit if we have
	if (!productFile.good()) exit(1);
}

// ---------------------------------------------------------
// Function: seekToBeginningOfProductFile
void seekToBeginningOfProductFile() {
    // Seeks to the beginning of the product file
    if (!productFile.is_open()) return;

	// Reset internal flags
    productFile.clear();

	// Set the position in the input sequence to the beginning of the file
	// Zero offest from the beginning of the file
    productFile.seekg(0, std::ios::beg);
}

// ---------------------------------------------------------
// Function: displayProduct
void displayProduct(const Product& product) {
    // Displays the name of a product to the standard output
	std::cout << product.name << std::endl;
}

// ---------------------------------------------------------
// Function: productFileDisplay20OrLess
int productFileDisplay20OrLess(int& page) {
    // Displays up to 20 module objects from the specified page of the module file.
    // Returns the number of modules displayed or -1 if the file cannot be opened.
    // Parameter: page (The page number to display)
    // Parameter: filename (The name of the module file)
	
	// Constants
	static const int ITEMS_PER_PAGE = 20;	// static

	// Variables
	int modulePages;
	Product tmpModule;

	// Find the total number of items on file
	seekToBeginningOfProductFile();
	int counter = 0;
	while (productFile.read(reinterpret_cast<char*>(&tmpModule), sizeof(Product))) {
		counter++;
	}	
	productFile.clear();
	// std::cout << "total entries " << std::to_string(counter) << std::endl;

	// Calculate the total number of pages
	modulePages = (counter + ITEMS_PER_PAGE-1) / ITEMS_PER_PAGE;
	// std::cout << "total pages " << std::to_string(modulePages) << std::endl;

	// Determine if the provided page is valid
	if ((page < 1) || (page > modulePages)) {
		if (page < 1) {
			page++;
			std::cout << "No previous pages exist!" << std::endl;
		} else {
			page--;
			std::cout << "No next pages exist!" << std::endl;
		}
	} 

	// Display the selected page
	// Loop forward by the number of pages on the file so that the next read is the
	// desired page
	seekToBeginningOfProductFile();
	productFile.seekp((page-1)*ITEMS_PER_PAGE*sizeof(Product),std::ios::cur);
	// std::cout << "end of getting to page" << std::endl;

	// Print the page
	std::cout << std::endl;
	std::cout << "Page " << page << "/" << modulePages << std::endl;
	int pageRecordsCount = 0;
	while (productFile.read(reinterpret_cast<char*>(&tmpModule), sizeof(Product)) && 
		  (pageRecordsCount < ITEMS_PER_PAGE)) {
		std::cout << std::to_string(pageRecordsCount+1) << ") ";
		displayProduct(tmpModule);
		pageRecordsCount++;
	}
	productFile.clear();
	std::cout << "Enter ‘Exit’ to leave this selection screen." << std::endl;
	std::cout << "If previous/next pages exist, enter ‘<’ for the previous page and ‘>’ for the next page." << std::endl;
	
	return pageRecordsCount;
}

// ---------------------------------------------------------
// Function: retrieveProductByName
bool retrieveProductByName(const char* filename, const char* productName, Product& product) {
    // Retrieves a product from the product file by its name
    // Parameters:
    //   filename (The name of the file to retrieve the product from)
    //   productName (The name of the product to retrieve)
    //   product (The Product object to store the retrieved data)
    // Returns:
    //   bool (true if retrieval was successful, false otherwise)
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
    // Creates a new product with the given name and writes it to the product file if it doesn't already exist
    // Parameter: namePtr (Pointer to the name of the product to create)
	// Create the product
    Product product = {};
	
	// Store the string into product's name attribute
	std::strcpy(product.name, namePtr);

	//std::cout << "createProduct: the product we received was named " << product.name << std::endl;

	// Check if the product is on the file
	bool productExists = false;

	Product tmpProduct;

	seekToBeginningOfProductFile();
	
	while (productFile.read(reinterpret_cast<char*>(&tmpProduct), sizeof(Product))) {
        if (std::strcmp(tmpProduct.name, namePtr) == 0) {
			productExists = true;
        }
    }
	productFile.clear();

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
    // Opens the product release file for reading and writing in binary append mode
    // Exits the program if the file fails to open
    productReleaseFile.open("productReleases.dat", std::ios::in | std::ios::out | std::ios::binary | std::ios::app);
    
	// Check if file opening worked properly, exit if it didn't
	if (!productReleaseFile.is_open()) exit(1);
}

// ---------------------------------------------------------
// Function: closeProductReleaseFile
void closeProductReleaseFile() {
    // Closes the product release file if it is open
    if (productReleaseFile.is_open()) {
        productReleaseFile.close();
    }
}

// ---------------------------------------------------------
// Function: writeProductRelease
void writeProductRelease(const ProductRelease& productRelease) {
    // Writes a ProductRelease object to the product release file
    // Exits the program if there is a failure while writing
    if (!productReleaseFile.is_open()) return;

	// Get the character address of the product struct, write it a byte at a time (char),
	// writing "sizeof(Product)" amount of bytes  
	// Note: fixed-length writing as Product is a struct and attribute type fixes the struct size
	productReleaseFile.write(reinterpret_cast<const char*>(&productRelease), sizeof(ProductRelease));
	productReleaseFile.flush();

	// Check if we ran out of disk space; exit if we have
	if (!productReleaseFile.good()) exit(1);
}

// ---------------------------------------------------------
// Function: seekToBeginningOfProductReleaseFile
void seekToBeginningOfProductReleaseFile() {
    // Seeks to the beginning of the product release file
    if (!productReleaseFile.is_open()) return;

	// Reset internal flags
    productReleaseFile.clear();

	// Set the position in the input sequence to the beginning of the file
	// Zero offest from the beginning of the file
    productReleaseFile.seekg(0, std::ios::beg);
}

// ---------------------------------------------------------
// Function: displayProductRelease
void displayProductRelease(const ProductRelease& productRelease) {
    // Displays details of a product release to the standard output
	std::cout << productRelease.productName <<
				 ", " << productRelease.releaseID <<
				 ", " << productRelease.releaseDate << std::endl;
}

// ---------------------------------------------------------
// Function: productReleaseFileDisplay20OrLess
int productReleaseFileDisplay20OrLess(int& page, const char* productName) {
    // Displays up to 20 module objects from the specified page of the module file.
    // Returns the number of modules displayed or -1 if the file cannot be opened.
    // Parameter: page (The page number to display)
    // Parameter: filename (The name of the module file)
	
	// Constants
	static const int ITEMS_PER_PAGE = 20;	// static

	// Variables
	int modulePages;
	ProductRelease tmpModule;

	// Find the total number of items on file
	seekToBeginningOfProductReleaseFile();
	int counter = 0;
	while (productReleaseFile.read(reinterpret_cast<char*>(&tmpModule), sizeof(ProductRelease))) {
		counter++;
	}	
	productReleaseFile.clear();
	// std::cout << "total entries " << std::to_string(counter) << std::endl;

	// Calculate the total number of pages
	modulePages = (counter + ITEMS_PER_PAGE-1) / ITEMS_PER_PAGE;
	// std::cout << "total pages " << std::to_string(modulePages) << std::endl;

	// Determine if the provided page is valid
	if ((page < 1) || (page > modulePages)) {
		if (page < 1) {
			page++;
			std::cout << "No previous pages exist!" << std::endl;
		} else {
			page--;
			std::cout << "No next pages exist!" << std::endl;
		}
	} 

	// Display the selected page
	// Loop forward by the number of pages on the file so that the next read is the
	// desired page
	seekToBeginningOfProductReleaseFile();
	productReleaseFile.seekp((page-1)*ITEMS_PER_PAGE*sizeof(ProductRelease),std::ios::cur);
	// std::cout << "end of getting to page" << std::endl;

	// Print the page
	std::cout << std::endl;
	std::cout << "Page " << page << "/" << modulePages << std::endl;
	int pageRecordsCount = 0;
	while (productReleaseFile.read(reinterpret_cast<char*>(&tmpModule), sizeof(ProductRelease)) && 
		  (pageRecordsCount < ITEMS_PER_PAGE)) {
		if (strcmp(tmpModule.productName,productName) == 0) {
			std::cout << std::to_string(pageRecordsCount+1) << ") ";
			displayProductRelease(tmpModule);
			pageRecordsCount++;
		}
	}
	productReleaseFile.clear();
	std::cout << "Enter ‘Exit’ to leave this selection screen." << std::endl;
	std::cout << "If previous/next pages exist, enter ‘<’ for the previous page and ‘>’ for the next page." << std::endl;
	
	return pageRecordsCount;
}


// ---------------------------------------------------------
// Function: retrieveProductReleaseByKey
bool retrieveProductReleaseByKey(const char* filename, const char* productReleaseName, const char* releaseID, ProductRelease& productRelease) {
    ProductRelease tmpProductRelease;

	seekToBeginningOfProductReleaseFile();

    while (productReleaseFile.read(reinterpret_cast<char*>(&tmpProductRelease), sizeof(ProductRelease))) {
		// If in the productReleaseFile, there exists an element that matches what we hope to retrieve
        if ((std::strcmp(tmpProductRelease.productName, productReleaseName) == 0) &&
			(std::strcmp(tmpProductRelease.releaseID, releaseID) == 0)) {
			
			// Store the product into the product outside of the function
			std::strcpy(productRelease.productName, tmpProductRelease.productName);
			std::strcpy(productRelease.releaseID, tmpProductRelease.releaseID);
			std::strcpy(productRelease.releaseDate, tmpProductRelease.releaseDate);

            return true; // Product found
        }
    }
	productReleaseFile.clear();

    return false; // Product not found
}

// ---------------------------------------------------------
// Function: createProductRelease
void createProductRelease(const char* productName, const char* releaseID, const char* releaseDate) {	// Variables
    // Creates a new product release with the given details and writes it to the product release file if it doesn't already exist
    // Parameters:
    //   productName (The name of the product in the release)
    //   releaseID (The release ID of the product release)
    //   releaseDate (The date of the product release)
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


// ---------------------------------------------------------
// Function: determineReleaseIDExistence
bool determineReleaseIDExistence(const char* releaseID) {
    // Checks if a given release ID exists in the product release file
    // Parameter:
    //   releaseID (The release ID to check for existence)
    // Returns:
    //   bool (true if the release ID exists, false otherwise)
    ProductRelease tmpProductRelease;

	seekToBeginningOfProductReleaseFile();

	// Determine if the release exists
    while (productReleaseFile.read(reinterpret_cast<char*>(&tmpProductRelease), sizeof(ProductRelease))) {
		// If in the productReleaseFile, there exists an element that matches what we hope to retrieve
        if ((std::strcmp(tmpProductRelease.releaseID, releaseID) == 0)) {
            return true; // release ID found
        }
    }
	productReleaseFile.clear();

    return false; // release ID not found
}