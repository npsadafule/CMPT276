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
	// Note: trunc is ensuring that we test with an empty file: pre-condition followed
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

// NOTE: DOESNT APPEND, CHECK DUPLICATE
void createProduct(const char* namePtr) { 
	// Create the product
    Product product = {};
	
	// Store the string into product's name attribute
	std::strcpy(product.name, namePtr);

	//std::cout << "createProduct: the product we received was named " << product.name << std::endl;

	// Check if the product is on the file
	bool productExists = false;

	Product tmpProduct;

	seekToBeginningOfProductFile();
	
	std::ifstream inFile("products.dat", std::ios::binary);
    if (!inFile) {
        std::cerr << "Failed to open file for reading!" << std::endl;
        exit(1);
    }

	while (inFile.read(reinterpret_cast<char*>(&tmpProduct), sizeof(Product))) {
        if (std::strcmp(tmpProduct.name, namePtr) == 0) {
			productExists = true;
        }
    }
	inFile.close();

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
	// Note: trunc is ensuring that we test with an empty file: pre-condition followed
    productReleaseFile.open("productReleases.dat", std::ios::in | std::ios::out | std::ios::binary | std::ios::app);
    
	// // Check if empty
	// productReleaseFile.clear();
	// productReleaseFile.seekg(0,std::ios::end);
	// std::cout << "Is the file empty? " << productReleaseFile.tellg() << std::endl;

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

// ---------------------------------------------------------
// Function: getNextProductRelease
bool getNextProductRelease(ProductRelease& productRelease) {
	// std::cout << "get next product release" << std::endl;
    if (!productReleaseFile.is_open()) return false;
    productReleaseFile.read(reinterpret_cast<char*>(&productRelease), sizeof(ProductRelease));
    return !productReleaseFile.fail();
}

// ---------------------------------------------------------
// For bringing up lists of products for reports
// void readProductReleaseFile(const char* filename, ProductRelease& productRelease) {
//     std::ifstream inFile(filename, std::ios::binary);
//     if (!inFile) {
//         std::cerr << "Failed to open file for reading!" << std::endl;
//         return;
//     }

//     while (inFile.read(reinterpret_cast<char*>(&product), sizeof(Product))) {
//         std::cout << "Product Name: " << product.name << std::endl;
//     }
// }

// For retrieving a particular product with a particular name
bool retrieveProductReleaseByKey(const char* filename, const char* productReleaseName, const char* releaseID, ProductRelease& productRelease) {
	ProductRelease tmpProductRelease;

	seekToBeginningOfProductFile();

	std::ifstream inFile(filename, std::ios::binary);
    if (!inFile) {
        std::cerr << "Failed to open file for reading!" << std::endl;
        return false;
    }

    // Read each product from the file and compare its name with the target name
	// std::cout << "before read loop" << std::endl;
	// inFile.read(reinterpret_cast<char*>(&tmpProductRelease), sizeof(ProductRelease));

	// std::cout << ".good " << inFile.good() << " .eof " << inFile.eof() <<
	// 			 " .fail() " << inFile.fail() << " .bad " << inFile.bad() << std::endl;


    while (inFile.read(reinterpret_cast<char*>(&tmpProductRelease), sizeof(ProductRelease))) {
		// If in the inFile, there exists an element that matches what we hope to retrieve
		// std::cout << "read: " << tmpProductRelease.productName << ", " << tmpProductRelease.releaseID << std::endl;
		// std::cout << "comparing: " << productReleaseName << ", " << releaseID << std::endl;
        if ((std::strcmp(tmpProductRelease.productName, productReleaseName) == 0) &&
			(std::strcmp(tmpProductRelease.releaseID, releaseID) == 0)) {
			inFile.close();
			
			// Store the product into the product outside of the function
			std::strcpy(productRelease.productName, tmpProductRelease.productName);
			std::strcpy(productRelease.releaseID, tmpProductRelease.releaseID);
			std::strcpy(productRelease.releaseDate, tmpProductRelease.releaseDate);

            return true; // Product found
        }
    }

	inFile.close();
    return false; // Product not found
}

// ---------------------------------------------------------
// Function: createProductRelease

// NOTE: DOESNT APPEND, CHECK DUPLICATE
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

	seekToBeginningOfProductFile();

	std::ifstream inFile("productReleases.dat", std::ios::binary);
    if (!inFile) {
        std::cerr << "Failed to open file for reading!" << std::endl;
        exit(1);
    }

    // Read each product from the file and compare its name with the target name
	// std::cout << "before read loop" << std::endl;
    while (inFile.read(reinterpret_cast<char*>(&tmpProductRelease), sizeof(ProductRelease))) {
        if ((std::strcmp(tmpProductRelease.productName, productName) == 0) &&
			(std::strcmp(tmpProductRelease.releaseID, releaseID) == 0)) {
			productReleaseExists = true;
        }
    }
	inFile.close();
	
	// If the product release doesn't exist, append it to the end of the file
    if (!productReleaseExists) {
		writeProductRelease(productRelease);
	}	
}


// OLD CREATE RPODUCT

	// // Set up the tempFile for writing
	// std::fstream tempFile("temp.dat", std::ios::out | std::ios::binary);
	// if (!tempFile) {
	// 	std::cerr << "Failed to open temp.dat for writing!" << std::endl;
	// 	return;
	// }	

	// // Set up a temporary Product Release for looping through a file
	// ProductRelease tmpPR;	
	// // Set up duplicate flag
	// bool duplicateFlag = false;
	// // While there are products in the product.dat file...
    // while (getNextProductRelease(tmpPR)) {
	// 	// If an entry exists in the file with the same key, set the duplicate
	// 	// flag to "true" to prevent "appending" a duplicate to the file
    //     if ((strcmp(tmpPR.productName, productName) == 0) &&
	// 		(strcmp(tmpPR.releaseID, releaseID) == 0)) {
    //         duplicateFlag = true;
	// 		//std::cout << "duplicate!" << std::endl;
    //     }
		
	// 	// Write the current product release into the temp file
    //     tempFile.write(reinterpret_cast<const char*>(&tmpPR), sizeof(ProductRelease));
    // }
	// tempFile.flush();

	// // // If no duplicate found, append productRelease to tempFile
	// if (!duplicateFlag) {
	// 	tempFile.seekp(0, std::ios::end);
	// 	// std::cout << "writing new prod release into temp file" << std::endl;
	// 	tempFile.write(reinterpret_cast<const char*>(&productRelease), sizeof(ProductRelease));
	// 	// std::cout << "post-write call" << std::endl;
	// }

	// // // Replace original products.dat with temp.dat
	// if (!duplicateFlag) {
	// 	// std::cout << "no duplicates found in product rel file" << std::endl;
	// 	if (remove("productReleases.dat") != 0) {
	// 		std::cerr << "Failed to remove productReleases.dat" << std::endl;
	// 		return;
	// 	}
	// 	if (rename("temp.dat", "productReleases.dat") != 0) {
	// 		std::cerr << "Failed to rename temp.dat to productReleases.dat" << std::endl;
	// 		return;
	// 	}
	// } else {
	// 	// std::cout << "duplicates found in product rel file" << std::endl;
	// 	// If duplicate was found, just remove temp.dat
	// 	remove("temp.dat");
	// }

	// // std::cout << "Reached end of createProductRelease" << std::endl;