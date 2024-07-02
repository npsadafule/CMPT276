// ============================================
// Module Name: unitTestMain.cpp
// ============================================
// Version History:
// Rev. 1 - 2024/07/01 - Neel Sadafule
// ============================================

#include <iostream>
#include <cassert>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include "Product.h"
#include "ChangeRequest.h"
#include "Report.h"
#include "User.h"

// Global variables
std::vector<Product> products;
std::vector<User> users;
std::map<std::string, std::string> changeRequests;

// ============================================
// Function Declarations
// ============================================
void testCreateProduct();
void testCreateMultipleProducts();
void testCreateChangeRequest();
void testQueryChangeItem();
void testUpdateChangeItem();
void runAllTests();

// Main Function
// ============================================
// Function: main
// Description: Entry point for unit tests.
// ---------------------------------------------
int main() {
    runAllTests();
    std::cout << "All unit tests passed.\n";
    return 0;
}

// ============================================
// Test Implementations
// ============================================

// ---------------------------------------------
// Function: testCreateProduct
// Description: Tests the creation of a single product.
// ---------------------------------------------
void testCreateProduct() {
    products.clear();
    createProduct("TestProduct");
    assert(products.size() == 1);
    assert(products[0].name == "TestProduct");
    std::cout << "testCreateProduct passed.\n";
}

// ---------------------------------------------
// Function: testCreateMultipleProducts
// Description: Tests the creation of multiple products to check system performance under load.
// ---------------------------------------------
void testCreateMultipleProducts() {
    products.clear();
    for (int i = 1; i <= 1000; ++i) {
        createProduct("Product" + std::to_string(i));
    }
    assert(products.size() == 1000);
    std::cout << "testCreateMultipleProducts passed.\n";
}

// ---------------------------------------------
// Function: testCreateChangeRequest
// Description: Tests the creation of a change request.
// ---------------------------------------------
void testCreateChangeRequest() {
    products.clear();
    createProduct("TestProduct");
    createChangeRequest("TestUser", "TestProduct", "123456", "Test Change", "0001");
    assert(products[0].changeItems.size() == 1);
    assert(products[0].changeItems["123456"].description == "Test Change");
    std::cout << "testCreateChangeRequest passed.\n";
}

// ---------------------------------------------
// Function: testQueryChangeItem
// Description: Tests querying a change item.
// ---------------------------------------------
void testQueryChangeItem() {
    products.clear();
    createProduct("TestProduct");
    createChangeRequest("TestUser", "TestProduct", "123456", "Test Change", "0001");
    queryChangeItem("TestProduct", "123456");
    std::cout << "testQueryChangeItem passed.\n";
}

// ---------------------------------------------
// Function: testUpdateChangeItem
// Description: Tests updating a change item.
// ---------------------------------------------
void testUpdateChangeItem() {
    products.clear();
    createProduct("TestProduct");
    createChangeRequest("TestUser", "TestProduct", "123456", "Test Change", "0001");
    updateChangeItem("TestProduct", "123456", "InProgress");
    assert(products[0].changeItems["123456"].state == "InProgress");
    std::cout << "testUpdateChangeItem passed.\n";
}

// ---------------------------------------------
// Function: runAllTests
// Description: Runs all unit tests.
// ---------------------------------------------
void runAllTests() {
    testCreateProduct();
    testCreateMultipleProducts();
    testCreateChangeRequest();
    testQueryChangeItem();
    testUpdateChangeItem();
}
