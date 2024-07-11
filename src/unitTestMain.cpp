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
#include "SystemController.h"

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
    products.clear();
    createProduct("TestProduct");
    assert(products.size() == 1);
    assert(products[0].name == "TestProduct");
    std::cout << "testCreateProduct passed.\n";
}

// ---------------------------------------------------------
// Function: testCreateMultipleProducts
void testCreateMultipleProducts() {
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
    products.clear();
    createProduct("TestProduct");
    createChangeRequest("TestUser", "TestProduct", "123456", "Test Change", "0001");
    queryChangeItem("TestProduct", "123456");
    std::cout << "testQueryChangeItem passed.\n";
}

// ---------------------------------------------------------
// Function: testUpdateChangeItem
void testUpdateChangeItem() {
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
    testCreateProduct();
    testCreateMultipleProducts();
    testCreateChangeRequest();
    testQueryChangeItem();
    testUpdateChangeItem();
}
