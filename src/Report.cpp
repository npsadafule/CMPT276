// ============================================
// Module Name: Report.cpp
// ============================================
// Version History:
// Rev. 1 - 2024/07/01 - Neel Sadafule
// ============================================

#include "Report.h"
#include "Product.h"
#include "User.h"
#include <iostream>
#include <vector>

// Global variable definitions
extern std::vector<Product> products;
extern std::vector<User> users;

// ============================================
// Function Implementations
// ============================================

// ---------------------------------------------------------
// Function: generateReport1
void generateReport1(
    const std::string& productName    // in
) {
    // Description:
    // Generates a report listing all change items for a product that are not done or cancelled. If the
    // product does not exist, it displays an error message.
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

// ---------------------------------------------------------
// Function: generateReport2
void generateReport2(
    const std::string& changeID    // in
) {
    // Description:
    // Generates a report listing customers/staff who need to be informed when a particular change has
    // been implemented. It displays the list of users who need to be informed.
    std::cout << "Report #2: List of Customers/Staff Who Need to Be Informed When a Particular Change Has Been Implemented\n";
    for (const auto& user : users) {
        std::cout << "Name: " << user.name << ", Email: " << user.email << "\n";
    }
}
