#include "Product.h"
#include <iostream>
#include <fstream>

// File handling functions
extern std::fstream productFile;


// ============================================
// Function Implementations
// ============================================

// ---------------------------------------------------------
// Function: openProductFile
void openProductFile() {
	// Note: trunc is ensuring that we test with an empty file: pre-condition followed
    productFile.open("products.dat", std::ios::in | std::ios::out | std::ios::binary | std::ios::trunc);
    
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

// ---------------------------------------------------------
// Function: getNextProduct
bool getNextProduct(Product& product) {
    if (!productFile.is_open()) return false;
    productFile.read(reinterpret_cast<char*>(&product), sizeof(Product));
    return !productFile.fail();
}

// For bringing up lists of products for reports
void readProductFile(const char* filename, Product& product) {
    std::ifstream inFile(filename, std::ios::binary);
    if (!inFile) {
        std::cerr << "Failed to open file for reading!" << std::endl;
        return;
    }

    while (inFile.read(reinterpret_cast<char*>(&product), sizeof(Product))) {
        std::cout << "Product Name: " << product.name << std::endl;
    }
}

// For retrieving a particular product with a particular name
bool retrieveProductByName(const char* filename, const char* productName, Product& product) {
    Product tmpProduct;

	seekToBeginningOfProductFile();

	std::ifstream inFile(filename, std::ios::binary);
    if (!inFile) {
        std::cerr << "Failed to open file for reading!" << std::endl;
        return false;
    }

    // Read each product from the file and compare its name with the target name
    while (inFile.read(reinterpret_cast<char*>(&tmpProduct), sizeof(Product))) {
        if (std::strcmp(tmpProduct.name, productName) == 0) {
            inFile.close();
			
			// Store the product into the product outside of the function
			std::strcpy(product.name, tmpProduct.name);

            return true; // Product found
        }
    }

    inFile.close();
    return false; // Product not found
}

// ---------------------------------------------------------
// Function: createProduct
void createProduct(const char* namePtr) {
	// Create the product
    Product product = {};
	
	// Store the string into product's name attribute
	std::strcpy(product.name, namePtr);

	//std::cout << "createProduct: the product we received was named " << product.name << std::endl;

	// Write it to file
    seekToBeginningOfProductFile();
    writeProduct(product);
}

// ---------------------------------------------------------
// Function: createRelease
void createRelease(const std::string& productName, const std::string& releaseID, const std::string& releaseDate) {
    Product product;
    std::fstream tempFile("temp.dat", std::ios::out | std::ios::binary);
    seekToBeginningOfProductFile();
	// While there are products in the product.dat file...
    while (getNextProduct(product)) {
		// TBD: checking the productRelease file before adding more product releases
		// If the name of the product retrieved from the file
		// is the same as the product we are trying to insert
        // if ((product.name == productName)) {
        //     product.releases[releaseID] = releaseDate;
        // }
		
		// Write the current product into the temp file
        tempFile.write(reinterpret_cast<const char*>(&product), sizeof(Product));
    }
    closeProductFile();
    tempFile.close();
	// Deletes the previous products file
    remove("products.dat");
	// Updates the previous products file to a new one
    rename("temp.dat", "products.dat");
	// Message output for the user
    std::cout << "Release " << releaseID << " for Product " << productName << " added successfully.\n";
}
