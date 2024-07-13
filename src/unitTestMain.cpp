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

// Constants
static const int STRCMP_TRUE = 0;

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
    // std::cout << "All unit tests passed.\n";
	std::cout << "End of unitTestMain" << std::endl;
    return 0;
}

// ============================================
// Test Implementations
// ============================================

// ---------------------------------------------------------
// Function: testCreateProduct
void testCreateProduct() {
	// ORIGINAL TEST

	// String we are testing
	char testString[PRODUCT_NAME_LENGTH] = "testProduct";

	// Open the file
	openProductFile();

	// Pre-test initialization and output
	Product product2 = {"tmpName"};
	std::cout << "BEFORE TEST: Our 'empty' product on RAM has the name " << '"' << product2.name << '"' << std::endl;

	// Run the function
	std::cout << "Running createProduct()..." << std::endl;
    createProduct(testString);

	// Read "joey" out of file
	retrieveProductByName("products.dat", testString, product2);

	std::cout << "AFTER TEST: The product we retrieved and stored into our empty product is named " << 
				 '"' << product2.name << '"' << std::endl;

	// Final evaluation
	std::cout << "Test evaluation: ";
	if (std::strcmp(testString, product2.name) == STRCMP_TRUE) {
		std::cout << "passed" << std::endl;
	} else {
		std::cout << "failed" << std::endl;
	}
	
	// Close the product file
	closeProductFile();

	// ==========================================
	// LOOPING TEST

	// // String we are testing
	// const char* attributes[5] = {
	// 	"reagan","anthony","ed","zolensky","joeBiden"
	// };

	// // Open the file
	// openProductFile();

	// // Pre-test initialization and output
	// Product product2 = {"tmpName"};
	// std::cout << "BEFORE TEST: Our 'empty' product on RAM has the name " << '"' << product2.name << '"' << std::endl;

	// // Run the function
	// std::cout << "Running createProduct()..." << std::endl;
	// for (int i=0; i<5; i++)
	// {
	// 	createProduct(attributes[i]);
	// }

	// // Read "joey" out of file
	// for (int i=0; i<5; i++)
	// {
	// 	retrieveProductByName("products.dat", attributes[i], product2);
	// 	std::cout << product2.name << std::endl;
	// }
	// std::cout << "AFTER TEST: The product we retrieved and stored into our empty product is named " << 
	// 			 '"' << product2.name << '"' << std::endl;

	// // Final evaluation
	// std::cout << "Test evaluation: ";
	// if (std::strcmp(attributes[4], product2.name) == STRCMP_TRUE) {
	// 	std::cout << "passed" << std::endl;
	// } else {
	// 	std::cout << "failed" << std::endl;
	// }
	
	// // Close the product file
	// closeProductFile();

	// ==========================================
	// CHANGE ITEM TEST

	

}

void testCreateChangeItem() {

}

// ---------------------------------------------------------
// Function: testCreateMultipleProducts
void testCreateMultipleProducts() {
    // products.clear();
    // for (int i = 1; i <= 1000; ++i) {
    //     createProduct("Product" + std::to_string(i));
    // }
    // assert(products.size() == 1000);
    // std::cout << "testCreateMultipleProducts passed.\n";
}

// ---------------------------------------------------------
// Function: testCreateChangeRequest
void testCreateChangeRequest() {
    // products.clear();
    // createProduct("TestProduct");
    // createChangeRequest("TestUser", "TestProduct", "123456", "Test Change", "0001");
    // assert(products[0].changeItems.size() == 1);
    // assert(products[0].changeItems["123456"].description == "Test Change");
    // std::cout << "testCreateChangeRequest passed.\n";
}

// ---------------------------------------------------------
// Function: testQueryChangeItem
void testQueryChangeItem() {
    // products.clear();
    // createProduct("TestProduct");
    // createChangeRequest("TestUser", "TestProduct", "123456", "Test Change", "0001");
    // queryChangeItem("TestProduct", "123456");
    // std::cout << "testQueryChangeItem passed.\n";
}

// ---------------------------------------------------------
// Function: testUpdateChangeItem
void testUpdateChangeItem() {
    // products.clear();
    // createProduct("TestProduct");
    // createChangeRequest("TestUser", "TestProduct", "123456", "Test Change", "0001");
    // updateChangeItem("TestProduct", "123456", "InProgress");
    // assert(products[0].changeItems["123456"].state == "InProgress");
    // std::cout << "testUpdateChangeItem passed.\n";
}

// ---------------------------------------------------------
// Function: runAllTests
void runAllTests() {
    // testCreateProduct();
	testCreateChangeItem();
	
    // testCreateMultipleProducts();
    // testCreateChangeRequest();
    // testQueryChangeItem();
    // testUpdateChangeItem();
}
