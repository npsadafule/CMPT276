// ============================================
// Module Name: Product.cpp
// ============================================
// Version History:
// Rev. 1 - 2024/07/01 - Neel Sadafule
// ============================================

#include "Product.h"
#include <iostream>
#include <algorithm>
#include <vector>

// Global variable definition
extern std::vector<Product> products;

// ============================================
// Function Implementations
// ============================================

// ---------------------------------------------------------
// Function: createProduct
void createProduct(
    const std::string& name    // in
) {
    // Description:
    // Creates a new product and adds it to the global product list. It checks if a product with the
    // same name already exists and displays an error message if it does.
    Product newProduct;
    newProduct.name = name;

    for (const auto& product : products) {
        if (product.name == newProduct.name) {
            std::cerr << "Product name already exists. Please try again.\n";
            return;
        }
    }

    products.push_back(newProduct);
    std::cout << "Product " << newProduct.name << " added successfully.\n";
}

// ---------------------------------------------------------
// Function: createRelease
void createRelease(
    const std::string& productName,    // in
    const std::string& releaseID,      // in
    const std::string& releaseDate     // in
) {
    // Description:
    // Creates a new release for an existing product. It checks if the product exists and adds the
    // release to the product's list of releases. If the product does not exist, it displays an error message.
    auto it = std::find_if(products.begin(), products.end(), [&](const Product& p) { return p.name == productName; });
    if (it == products.end()) {
        std::cerr << "Product does not exist. Please try again.\n";
        return;
    }

    it->releases[releaseID] = releaseDate;
    std::cout << "Release " << releaseID << " for Product " << productName << " added successfully.\n";
}
