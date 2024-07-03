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

// ---------------------------------------------
// Function: createProduct
// Description: Creates a new product and adds it to the global product list.
// Parameters:
// - name: The name of the product (in).
// ---------------------------------------------
void createProduct(const std::string& name) {
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

// ---------------------------------------------
// Function: createRelease
// Description: Creates a new release for an existing product.
// ---------------------------------------------
void createRelease(const std::string& productName, const std::string& releaseID, const std::string& releaseDate) {
    auto it = std::find_if(products.begin(), products.end(), [&](const Product& p) { return p.name == productName; });
    if (it == products.end()) {
        std::cerr << "Product does not exist. Please try again.\n";
        return;
    }

    // Assuming Product structure has a releases map (not defined in original code)
    it->releases[releaseID] = releaseDate;
    std::cout << "Release " << releaseID << " for Product " << productName << " added successfully.\n";
}
