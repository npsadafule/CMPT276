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
    productFile.open("products.dat", std::ios::in | std::ios::out | std::ios::binary);
    if (!productFile.is_open()) {
        std::cerr << "Failed to open products.dat file.\n";
    }
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
    productFile.write(reinterpret_cast<const char*>(&product), sizeof(Product));
}

// ---------------------------------------------------------
// Function: seekToBeginningOfProductFile
void seekToBeginningOfProductFile() {
    if (!productFile.is_open()) return;
    productFile.clear();
    productFile.seekg(0, std::ios::beg);
}

// ---------------------------------------------------------
// Function: getNextProduct
bool getNextProduct(Product& product) {
    if (!productFile.is_open()) return false;
    productFile.read(reinterpret_cast<char*>(&product), sizeof(Product));
    return !productFile.fail();
}

// ---------------------------------------------------------
// Function: createProduct
void createProduct(const std::string& name) {
    Product product = {name};
    openProductFile();
    seekToBeginningOfProductFile();
    writeProduct(product);
    closeProductFile();
    std::cout << "Product " << name << " added successfully.\n";
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
