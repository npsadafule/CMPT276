// ============================================
// Module Name: SystemController.cpp
// ============================================
// Version History:
// Rev. 1 - 2024/07/01 - Neel Sadafule
// ============================================

#include "SystemController.h"
#include "Product.h"
#include "ChangeRequest.h"
#include "Report.h"
#include "User.h"
#include <iostream>
#include <fstream>
#include <vector>

// Global variable definitions
std::vector<Product> products;
std::vector<User> users;
std::map<std::string, std::string> changeRequests;

// ============================================
// Function Implementations
// ============================================

// ---------------------------------------------
// Function: initProduct
// Description: Initializes the product module.
// ---------------------------------------------
void initProduct() {
    std::ifstream productFile("products.dat", std::ios::binary);
    if (productFile.is_open()) {
        Product product;
        while (productFile.read(reinterpret_cast<char*>(&product), sizeof(Product))) {
            products.push_back(product);
        }
        productFile.close();
    } else {
        std::cerr << "Failed to open products.dat file.\n";
    }
}

// ---------------------------------------------
// Function: initChangeRequest
// Description: Initializes the change request module.
// ---------------------------------------------
void initChangeRequest() {
    std::ifstream changeRequestFile("changerequests.dat");
    if (changeRequestFile.is_open()) {
        std::string key, value;
        while (changeRequestFile >> key >> value) {
            changeRequests[key] = value;
        }
        changeRequestFile.close();
    } else {
        std::cerr << "Failed to open changerequests.dat file.\n";
    }
}

// ---------------------------------------------
// Function: initChangeItem
// Description: Initializes the change item module.
// ---------------------------------------------
void initChangeItem() {
    // Assuming change items are part of products and initialized in initProduct.
    std::cout << "Change items are initialized as part of products.\n";
}

// ---------------------------------------------
// Function: initReportGen
// Description: Initializes the report generation module.
// ---------------------------------------------
void initReportGen() {
    std::ifstream userFile("users.dat", std::ios::binary);
    if (userFile.is_open()) {
        User user;
        while (userFile.read(reinterpret_cast<char*>(&user), sizeof(User))) {
            users.push_back(user);
        }
        userFile.close();
    } else {
        std::cerr << "Failed to open users.dat file.\n";
    }
}

// ---------------------------------------------
// Function: start
// Description: Initializes the application by reading data from files.
// ---------------------------------------------
void start() {
    initProduct();
    initChangeRequest();
    initChangeItem();
    initReportGen();
}
