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

// ---------------------------------------------------------
// Function: initProduct
void initProduct() {
    // Description:
    // Initializes the product module by reading product data from a binary file and populating the
    // global products vector. If the file cannot be opened, it displays an error message.
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

// ---------------------------------------------------------
// Function: initChangeRequest
void initChangeRequest() {
    // Description:
    // Initializes the change request module by reading change request data from a file and populating
    // the global changeRequests map. If the file cannot be opened, it displays an error message.
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

// ---------------------------------------------------------
// Function: initChangeItem
void initChangeItem() {
    // Description:
    // Initializes the change item module. It assumes that change items are part of products and
    // are initialized in the initProduct function.
    std::cout << "Change items are initialized as part of products.\n";
}

// ---------------------------------------------------------
// Function: initReportGen
void initReportGen() {
    // Description:
    // Initializes the report generation module by reading user data from a binary file and populating
    // the global users vector. If the file cannot be opened, it displays an error message.
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

// ---------------------------------------------------------
// Function: start
void start() {
    // Description:
    // Initializes the application by calling the initialization functions for products, change requests,
    // change items, and report generation.
    initProduct();
    initChangeRequest();
    initChangeItem();
    initReportGen();
}
