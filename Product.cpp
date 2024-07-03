// ============================================
// Module Name: Product.cpp
// ============================================
// Version History:
// Rev. 1 - 2024/07/01 - Neel Sadafule
// ============================================

#include "Product.h"
#include "ProcessCoordinator.h"
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
void createRelease() {
    std::string productName;
    std::cout << "\nEnter the Product Name (max 30 char, must pre-exist): \n \n";
    std::cin.ignore();
    std::getline(std::cin, productName);

    auto it = std::find_if(products.begin(), products.end(), [&](const Product& p) { return p.name == productName; });
    if (it == products.end()) {
        std::cerr << "\nProduct does not exist. Please try again.\n \n";
        return;
    }

    std::string releaseID, releaseDate;
    std::cout << "\nEnter the Release ID (max 30 char following your organization's format): \n \n";
    std::getline(std::cin, releaseID);
    std::cout << "\nEnter the Release Date (YYYY-MM-DD): \n \n";
    std::getline(std::cin, releaseDate);
    char X;
    std::cout << "\nAre you sure you want to add the release" << releaseID << "for Product " << productName << " (Y/N)? \n \n";
    std::cin >> X;
    if(X == 'Y'){
        std::cout << "Release " << releaseID << " for Product " << productName << " added successfully.\n \n";
        std::cout << "\nDo you wish to add another release (Y/N)? \n \n";
        std::cin >> X;
        if(X == 'Y'){
            handleProductMaintenance(2);
        }
        else{
  
        }
    }
    else{
           
        }

    // std::cout << "Release " << releaseID << " for Product " << productName << " added successfully.\n";
}
