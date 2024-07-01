#include <iostream>
#include <cassert>
#include "Product.h"
#include "ChangeRequest.h"
#include "Report.h"
#include "User.h"

// ============================================
// Module Name: unitTestMain.cpp
// ============================================

// Version History:
// Rev. 1 - 2024/07/01 - Neel Sadafule

// ============================================
// Data structures
// ---------------------------------------------

// Global variable definitions
std::vector<Product> products;
std::vector<User> users;
std::map<std::string, std::string> changeRequests;

// Function Declarations
// ============================================

/**
 * @brief Tests the createProduct function.
 */
void testCreateProduct();

/**
 * @brief Tests the createChangeRequest function.
 */
void testCreateChangeRequest();

/**
 * @brief Tests the queryChangeItem function.
 */
void testQueryChangeItem();

/**
 * @brief Tests the updateChangeItem function.
 */
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
// Function: testCreateProduct
// Description: Tests the creation of a new product.
// ---------------------------------------------
void testCreateProduct() {
    createProduct("TestProduct");
    assert(products.size() == 1);
    assert(products[0].name == "TestProduct");
    std::cout << "testCreateProduct passed.\n";
}

// Function: testCreateChangeRequest
// Description: Tests the creation of a new change request.
// ---------------------------------------------
void testCreateChangeRequest() {
    createProduct("TestProduct");
    createChangeRequest("TestUser", "TestProduct", "123456", "Test Change", "0001");
    assert(products[0].changeItems.size() == 1);
    assert(products[0].changeItems["123456"].description == "Test Change");
    std::cout << "testCreateChangeRequest passed.\n";
}

// Function: testQueryChangeItem
// Description: Tests querying a change item.
// ---------------------------------------------
void testQueryChangeItem() {
    createProduct("TestProduct");
    createChangeRequest("TestUser", "TestProduct", "123456", "Test Change", "0001");
    queryChangeItem("TestProduct", "123456");
    std::cout << "testQueryChangeItem passed.\n";
}

// Function: testUpdateChangeItem
// Description: Tests updating a change item.
// ---------------------------------------------
void testUpdateChangeItem() {
    createProduct("TestProduct");
    createChangeRequest("TestUser", "TestProduct", "123456", "Test Change", "0001");
    updateChangeItem("TestProduct", "123456", "InProgress");
    assert(products[0].changeItems["123456"].state == "InProgress");
    std::cout << "testUpdateChangeItem passed.\n";
}
