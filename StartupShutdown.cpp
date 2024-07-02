// ============================================
// Module Name: StartupShutdown.cpp
// ============================================
// Version History:
// Rev. 1 - 2024/07/01 - Neel Sadafule
// ============================================

#include "StartupShutdown.h"
#include "Product.h"
#include "ChangeRequest.h"
#include "Report.h"
#include "User.h"
#include <iostream>
#include <fstream>

// Global variables
extern std::vector<Product> products;
extern std::vector<User> users;
extern std::map<std::string, std::string> changeRequests;

// ============================================
// Function Implementations
// ============================================

// ---------------------------------------------
// Function: start
// Description: Initializes the application by reading data from files.
// ---------------------------------------------
void start() {
    std::ifstream productFile("products.dat", std::ios::binary);
    if (productFile.is_open()) {
        Product product;
        while (productFile.read(reinterpret_cast<char*>(&product), sizeof(Product))) {
            products.push_back(product);
        }
        productFile.close();
    }

    std::ifstream userFile("users.dat", std::ios::binary);
    if (userFile.is_open()) {
        User user;
        while (userFile.read(reinterpret_cast<char*>(&user), sizeof(User))) {
            users.push_back(user);
        }
        userFile.close();
    }

    std::ifstream changeRequestFile("changerequests.dat");
    if (changeRequestFile.is_open()) {
        std::string key, value;
        while (changeRequestFile >> key >> value) {
            changeRequests[key] = value;
        }
        changeRequestFile.close();
    }
}

// ---------------------------------------------
// Function: shutdown
// Description: Cleans up the application by writing data to files.
// ---------------------------------------------
void shutdown() {
    std::ofstream productFile("products.dat", std::ios::binary | std::ios::trunc);
    if (productFile.is_open()) {
        for (const auto& product : products) {
            productFile.write(reinterpret_cast<const char*>(&product), sizeof(Product));
        }
        productFile.close();
    }

    std::ofstream userFile("users.dat", std::ios::binary | std::ios::trunc);
    if (userFile.is_open()) {
        for (const auto& user : users) {
            userFile.write(reinterpret_cast<const char*>(&user), sizeof(User));
        }
        userFile.close();
    }

    std::ofstream changeRequestFile("changerequests.dat", std::ios::trunc);
    if (changeRequestFile.is_open()) {
        for (const auto& pair : changeRequests) {
            changeRequestFile << pair.first << " " << pair.second << "\n";
        }
        changeRequestFile.close();
    }
}
