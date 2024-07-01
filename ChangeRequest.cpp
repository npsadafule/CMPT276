#include "ChangeRequest.h"
#include <iostream>
#include <algorithm>
#include <vector>

// ============================================
// Module Name: ChangeRequest.cpp
// ============================================

// Version History:
// Rev. 1 - 2024/06/29 - Neel Sadafule

// Global variable definitions
extern std::vector<Product> products;

// Function Implementations
// ============================================
// Function: createChangeRequest
// Description: Creates a new change request.
// ---------------------------------------------
void createChangeRequest(const std::string& profileName, const std::string& productName, const std::string& changeID, const std::string& description, const std::string& anticipatedReleaseID) {
    auto it = std::find_if(products.begin(), products.end(), [&](const Product& p) { return p.name == productName; });
    if (it == products.end()) {
        std::cerr << "Product does not exist. Please try again.\n";
        return;
    }

    ChangeItem newItem = { description, changeID, "Reported", anticipatedReleaseID };
    it->changeItems[changeID] = newItem;
    std::cout << "Change Request ID is " << changeID << ". The Change Request was successfully added.\n";
}

// Function: queryChangeItem
// Description: Queries a change item and displays its details.
// ---------------------------------------------
void queryChangeItem(const std::string& productName, const std::string& changeID) {
    auto it = std::find_if(products.begin(), products.end(), [&](const Product& p) { return p.name == productName; });
    if (it == products.end()) {
        std::cerr << "Product does not exist. Please try again.\n";
        return;
    }

    auto itemIt = it->changeItems.find(changeID);
    if (itemIt == it->changeItems.end()) {
        std::cerr << "Change Item does not exist. Please try again.\n";
        return;
    }

    const ChangeItem& item = itemIt->second;
    std::cout << "Product: " << productName << "\nDescription: " << item.description << "\nChange ID: " << item.changeID << "\nState: " << item.state << "\nAnticipated Release ID: " << item.anticipatedReleaseID << "\n";
}

// Function: updateChangeItem
// Description: Updates the state of a change item.
// ---------------------------------------------
void updateChangeItem(const std::string& productName, const std::string& changeID, const std::string& newState) {
    auto it = std::find_if(products.begin(), products.end(), [&](const Product& p) { return p.name == productName; });
    if (it == products.end()) {
        std::cerr << "Product does not exist. Please try again.\n";
        return;
    }

    auto itemIt = it->changeItems.find(changeID);
    if (itemIt == it->changeItems.end()) {
        std::cerr << "Change Item does not exist. Please try again.\n";
        return;
    }

    ChangeItem& item = itemIt->second;
    item.state = newState;
    std::cout << "Change Item updated successfully.\n";
}
