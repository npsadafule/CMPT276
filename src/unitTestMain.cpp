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
#include "ChangeItem.h"

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

	// Run the function
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
	// Test data
	const ChangeItem CITest[3] {
		{1235, "Product A", "Sample description that runs on for a while", "R51B", "Reported"},
		{4567, "Random stuff", "The quick brown fox jumps over the lazy dog", "AB12", "Reported"},
		{6789, "Random", "Hahahhahahahahahha", "APO1", "Reported"}
	};

	// Open the file
	openChangeItemFile();

	// Pre-test initialization and output
	ChangeItem displayCI = {1682, "testProdName", "testDesc", "AJK3", "Reported"};

	std::cout << "BEFORE tmp change item: " << intToCString(displayCI.changeID) << " " << displayCI.productName <<
				 " " << displayCI.description << " " << displayCI.anticipatedReleaseID << " " << 
				 displayCI.state << std::endl;
	
	// Run the function
	std::cout << "Running createChangeItem()..." << std::endl;
	for (int i=0; i<3; i++) {
		createChangeItem(CITest[i].changeID,
						 CITest[i].productName,
						 CITest[i].description,
						 CITest[i].anticipatedReleaseID,
						 CITest[i].state);
	}

	// Read entries out of file, and tally correct outputs
	std::cout << "AFTER TEST: The change items we retrieved and stored into our empty product are the following:" << std::endl;

	// Initialize tally
	int correctTally = 0;
    for (int i=0; i<3; i++) {
		// Perform the retrieval
		retrieveChangeItemByKey("changeItems.dat", CITest[i].changeID, displayCI);
		
		// Count if desired product release was retrieved
		if (displayCI.changeID == CITest[i].changeID) {
			correctTally++;
		}

		// Display to the user
		std::cout << intToCString(displayCI.changeID) << 
				  ", " << displayCI.productName << 
				  ", " << displayCI.description << 
				  ", " << displayCI.anticipatedReleaseID <<
				  ", " << displayCI.state << std::endl;
	}

	// Final evaluation
	std::cout << "Test evaluation: ";
	if (correctTally == 3) {
		std::cout << "passed" << std::endl;
	} else {
		std::cout << "failed" << std::endl;
	}

	// Close the change item file
	closeChangeItemFile();
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
