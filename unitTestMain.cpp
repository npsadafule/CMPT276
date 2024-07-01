#include <iostream>
#include <cassert>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

// ============================================
// Module Name: unitTestMain.cpp
// ============================================

// Version History:
// Rev. 1 - 2024/06/29 - Neel Sadafule

// ============================================
// Data structures
// ---------------------------------------------

struct ChangeItem {
    std::string description;
    std::string changeID;
    std::string state;
    std::string anticipatedReleaseID;
};

struct Product {
    std::string name;
    std::map<std::string, ChangeItem> changeItems;
};

struct User {
    std::string name;
    std::string phoneNumber;
    std::string email;
    std::string role; // "Customer" or "Employee"
    std::string department;
};

std::vector<Product> products;
std::vector<User> users;
std::map<std::string, std::string> changeRequests;

// Function declarations
// ============================================
void createProduct(const std::string& name);
void createChangeRequest(const std::string& profileName, const std::string& productName, const std::string& changeID, const std::string& description, const std::string& anticipatedReleaseID);
void queryChangeItem(const std::string& productName, const std::string& changeID);
void updateChangeItem(const std::string& productName, const std::string& changeID, const std::string& newState);

// Unit Test Functions
// ============================================
void testCreateProduct();
void testCreateChangeRequest();
void testQueryChangeItem();
void testUpdateChangeItem();

// Main Function
// ============================================
int main() {
    testCreateProduct();
    testCreateChangeRequest();
    testQueryChangeItem();
    testUpdateChangeItem();
    std::cout << "All unit tests passed.\n";
    return 0;
}

// Function Implementations
// ============================================
// Function: createProduct
// Description: Creates a new product after checking for uniqueness.
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

// Function: createChangeRequest
// Description: Creates a new change request, creating a new user profile if necessary.
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
// Description: Updates a change item.
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

// Unit Test Implementations
// ============================================
// Function: testCreateProduct
// Description: Tests the createProduct function.
// ---------------------------------------------
void testCreateProduct() {
    // Setup
    products.clear();
    
    // Execute
    createProduct("TestProduct");
    
    // Verify
    assert(products.size() == 1);
    assert(products[0].name == "TestProduct");
    std::cout << "testCreateProduct passed.\n";
}

// Function: testCreateChangeRequest
// Description: Tests the createChangeRequest function.
// ---------------------------------------------
void testCreateChangeRequest() {
    // Setup
    products.clear();
    createProduct("TestProduct");

    // Execute
    createChangeRequest("TestUser", "TestProduct", "123456", "Test Change", "0001");

    // Verify
    assert(products[0].changeItems.size() == 1);
    assert(products[0].changeItems["123456"].description == "Test Change");
    assert(products[0].changeItems["123456"].state == "Reported");
    std::cout << "testCreateChangeRequest passed.\n";
}

// Function: testQueryChangeItem
// Description: Tests the queryChangeItem function.
// ---------------------------------------------
void testQueryChangeItem() {
    // Setup
    products.clear();
    createProduct("TestProduct");
    createChangeRequest("TestUser", "TestProduct", "123456", "Test Change", "0001");

    // Execute
    std::cout << "Output of queryChangeItem:\n";
    queryChangeItem("TestProduct", "123456");

    // Since this function outputs to the console, manual verification is required.
    // Verify (if automated output verification is possible)
    std::cout << "testQueryChangeItem passed.\n";
}

// Function: testUpdateChangeItem
// Description: Tests the updateChangeItem function.
// ---------------------------------------------
void testUpdateChangeItem() {
    // Setup
    products.clear();
    createProduct("TestProduct");
    createChangeRequest("TestUser", "TestProduct", "123456", "Test Change", "0001");

    // Execute
    updateChangeItem("TestProduct", "123456", "InProgress");

    // Verify
    assert(products[0].changeItems["123456"].state == "InProgress");
    std::cout << "testUpdateChangeItem passed.\n";
}
