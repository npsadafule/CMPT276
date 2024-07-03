#include "SystemController.h"
#include "Product.h"
#include "ChangeRequest.h"
#include "Report.h"
#include "User.h"
#include <iostream>
#include <fstream>

// Global variable definitions
std::vector<Product> products;
std::vector<User> users;
std::map<std::string, ChangeRequest> changeRequests;

// ============================================
// Function Implementations
// ============================================

// ---------------------------------------------------------
// Function: initProduct
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

// ---------------------------------------------------------
// Function: initChangeRequest
void initChangeRequest() {
    std::ifstream changeRequestFile("changeRequests.dat", std::ios::binary);
    if (changeRequestFile.is_open()) {
        ChangeRequest changeRequest;
        while (changeRequestFile.read(reinterpret_cast<char*>(&changeRequest), sizeof(ChangeRequest))) {
            changeRequests[changeRequest.changeID] = changeRequest;
        }
        changeRequestFile.close();
    } else {
        std::cerr << "Failed to open changeRequests.dat file.\n";
    }
}

// ---------------------------------------------------------
// Function: initChangeItem
void initChangeItem() {
    std::cout << "Change items are initialized as part of products.\n";
}

// ---------------------------------------------------------
// Function: initReportGen
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

// ---------------------------------------------------------
// Function: start
void start() {
    initProduct();
    initChangeRequest();
    initChangeItem();
    initReportGen();
}
