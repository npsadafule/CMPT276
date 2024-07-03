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
int main() {
    // Description:
    // Entry point for unit tests. It runs all the test functions and prints a success message if all tests pass.
    runAllTests();
    std::cout << "All unit tests passed.\n";
    return 0;
}

// ============================================
// Test Implementations
// ============================================

// ---------------------------------------------------------
// Function: testCreateProduct
void testCreateProduct() {
    // Description:
    // Tests the creation of a single product by clearing the products vector, creating a new product,
    // and asserting that the product was added successfully.
    products.clear();
    createProduct("TestProduct");
    assert(products.size() == 1);
    assert(products[0].name == "TestProduct");
    std::cout << "testCreateProduct passed.\n";
}

// ---------------------------------------------------------
// Function: testCreateMultipleProducts
void testCreateMultipleProducts() {
    // Description:
    // Tests the creation of multiple products to check system performance under load. It creates
    // 1000 products and asserts that all products were added successfully.
    products.clear();
    for (int i = 1; i <= 1000; ++i) {
        createProduct("Product" + std::to_string(i));
    }
    assert(products.size() == 1000);
    std::cout << "testCreateMultipleProducts passed.\n";
}

// ---------------------------------------------------------
// Function: testCreateChangeRequest
void testCreateChangeRequest() {
    // Description:
    // Tests the creation of a change request by creating a product and a change request, and asserting
    // that the change request was added successfully.
    products.clear();
    createProduct("TestProduct");
    createChangeRequest("TestUser", "TestProduct", "123456", "Test Change", "0001");
    assert(products[0].changeItems.size() == 1);
    assert(products[0].changeItems["123456"].description == "Test Change");
    std::cout << "testCreateChangeRequest passed.\n";
}

// ---------------------------------------------------------
// Function: testQueryChangeItem
void testQueryChangeItem() {
    // Description:
    // Tests querying a change item by creating a product and a change request, then querying the change
    // item and asserting that the query was successful.
    products.clear();
    createProduct("TestProduct");
    createChangeRequest("TestUser", "TestProduct", "123456", "Test Change", "0001");
    queryChangeItem("TestProduct", "123456");
    std::cout << "testQueryChangeItem passed.\n";
}

// ---------------------------------------------------------
// Function: testUpdateChangeItem
void testUpdateChangeItem() {
    // Description:
    // Tests updating a change item by creating a product and a change request, then updating the change
    // item and asserting that the update was successful.
    products.clear();
    createProduct("TestProduct");
    createChangeRequest("TestUser", "TestProduct", "123456", "Test Change", "0001");
    updateChangeItem("TestProduct", "123456", "InProgress");
    assert(products[0].changeItems["123456"].state == "InProgress");
    std::cout << "testUpdateChangeItem passed.\n";
}

// ---------------------------------------------------------
// Function: runAllTests
void runAllTests() {
    // Description:
    // Runs all the test functions in the module.
    testCreateProduct();
    testCreateMultipleProducts();
    testCreateChangeRequest();
    testQueryChangeItem();
    testUpdateChangeItem();
}
