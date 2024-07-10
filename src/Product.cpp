#include "Product.h"
#include <iostream>
#include <fstream>

// File handling functions
std::fstream productFile;


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
    openProductFile();
    seekToBeginningOfProductFile();
    while (getNextProduct(product)) {
        if (product.name == productName) {
            product.releases[releaseID] = releaseDate;
        }
        tempFile.write(reinterpret_cast<const char*>(&product), sizeof(Product));
    }
    closeProductFile();
    tempFile.close();
    remove("products.dat");
    rename("temp.dat", "products.dat");
    std::cout << "Release " << releaseID << " for Product " << productName << " added successfully.\n";
}
