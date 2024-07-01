#include "Report.h"
#include "User.h"
#include <iostream>
#include <vector>

// ============================================
// Module Name: Report.cpp
// ============================================

// Version History:
// Rev. 1 - 2024/06/29 - Neel Sadafule

// Global variable definitions
extern std::vector<Product> products;
extern std::vector<User> users;

// Function Implementations
// ============================================
// Function: generateReport1
// Description: Generates Report #1.
// ---------------------------------------------
void generateReport1(const std::string& productName) {
    auto it = std::find_if(products.begin(), products.end(), [&](const Product& p) { return p.name == productName; });
    if (it == products.end()) {
        std::cerr << "Product does not exist. Please try again.\n";
        return;
    }

    std::cout << "Report #1: List of All Change Items for " << productName << " that are Not Done and Not Cancelled\n";
    for (const auto& [id, item] : it->changeItems) {
        if (item.state != "Done" && item.state != "Cancelled") {
            std::cout << "ID: " << id << ", Description: " << item.description << ", State: " << item.state << ", Anticipated Release ID: " << item.anticipatedReleaseID << "\n";
        }
    }
}

// Function: generateReport2
// Description: Generates Report #2.
// ---------------------------------------------
void generateReport2(const std::string& changeID) {
    std::cout << "Report #2: List of Customers/Staff Who Need to Be Informed When a Particular Change Has Been Implemented\n";
    for (const auto& user : users) {
        std::cout << "Name: " << user.name << ", Email: " << user.email << "\n";
    }
}
