#include <iostream>
#include <cassert>
#include <chrono>
#include "Product.h"
#include "ChangeRequest.h"
#include "Report.h"
#include "User.h"

// ============================================
// Module Name: unitTestMain.cpp
// ============================================

// Version History:
// Rev. 1 - 2024/06/29 - Neel Sadafule

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
 * @brief Tests the creation of multiple products.
 */
void testCreateMultipleProducts();

/**
 * @brief Tests the performance of querying a change item.
 */
void testQueryPerformance();

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
    testCreateMultipleProducts();
    testQueryPerformance();
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
    products.clear();  // Clear the products vector before the test
    createProduct("TestProduct");
    assert(products.size() == 1);
    assert(products[0].name == "TestProduct");
    std::cout << "testCreateProduct passed.\n";
}

// Function: testCreateMultipleProducts
// Description: Tests the creation of multiple products.
// ---------------------------------------------
void testCreateMultipleProducts() {
    products.clear();  // Clear the products vector before the test
    for (int i = 1; i <= 1000; ++i) {
        createProduct("Product" + std::to_string(i));
    }
    assert(products.size() == 1000);
    std::cout << "testCreateMultipleProducts passed.\n";
}

// Function: testQueryPerformance
// Description: Tests the performance of querying a change item.
// ---------------------------------------------
void testQueryPerformance() {
    products.clear();  // Clear the products vector before the test
    createProduct("TestProduct");
    createChangeRequest("TestUser", "TestProduct", "123456", "Test Change", "0001");

    auto start = std::chrono::high_resolution_clock::now();
    queryChangeItem("TestProduct", "123456");
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    assert(elapsed.count() < 0.1); // Ensure the query takes less than 100ms
    std::cout << "testQueryPerformance passed.\n";
}

// Function: testCreateChangeRequest
// Description: Tests the creation of a new change request.
// ---------------------------------------------
void testCreateChangeRequest() {
    products.clear();  // Clear the products vector before the test
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
    products.clear();  // Clear the products vector before the test
    createProduct("TestProduct");
    createChangeRequest("TestUser", "TestProduct", "123456", "Test Change", "0001");
    queryChangeItem("TestProduct", "123456");
    std::cout << "testQueryChangeItem passed.\n";
}

// Function: testUpdateChangeItem
// Description: Tests updating a change item.
// ---------------------------------------------
void testUpdateChangeItem() {
    products.clear();  // Clear the products vector before the test
    createProduct("TestProduct");
    createChangeRequest("TestUser", "TestProduct", "123456", "Test Change", "0001");
    updateChangeItem("TestProduct", "123456", "InProgress");
    assert(products[0].changeItems["123456"].state == "InProgress");
    std::cout << "testUpdateChangeItem passed.\n";
}
