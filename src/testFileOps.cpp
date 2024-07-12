#include <iostream>
#include <cassert>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include "Product.h"

// Constants
static const int STRCMP_TRUE = 0;
// For extracting predetermined attribute test data from 'attributes' array
static const int PR_NAME = 0;
static const int PR_RELEASE_ID = 1;
static const int PR_RELEASE_DATE = 2;
static const int NUM_TEST_PR = 5;

// ============================================
// Function Declarations
// ============================================
void testCreateProduct();
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
void testCreateProductRelease() {
	// Open the file
	openProductReleaseFile();

	// Define a 3x5 array of C-style strings contianing the attribute test data
    const char* attributes[5][3] = {
        {"A", "11", "2024-06-11"},
        {"B", "12", "2024-06-12"},
        {"C", "13", "2024-06-13"},
        {"D", "14", "2024-06-14"},
        {"E", "15", "2024-06-15"}
    };

	// Pre-test initialization and output
	ProductRelease productRelease = {"tmpName","tmpRelID","tmpRelDate"};
	std::cout << "BEFORE TEST: Our 'empty' product on RAM has the name " << '"' << productRelease.productName << '"' << ',' <<
				 " the releaseID " << '"' << productRelease.releaseID << '"' << ',' << " and releaseDate " << 
				 '"' << productRelease.releaseDate << '"' << std::endl;

	// // Run the function
	std::cout << "Running createProductRelease()..." << std::endl;

    // Store the attribute test data as product releases
    for (int i=0; i<NUM_TEST_PR; i++) {
		//std::cout << attributes[i][PR_NAME] << " " << attributes[i][PR_RELEASE_ID] << " " << attributes[i][PR_RELEASE_DATE] << std::endl;
        createProductRelease(attributes[i][PR_NAME],attributes[i][PR_RELEASE_ID],attributes[i][PR_RELEASE_DATE]);
    }

	// // Read "testProduct" out of file
    for (int i=0; i<NUM_TEST_PR; i++) {
		retrieveProductReleaseByKey("productReleases.dat", attributes[i][PR_NAME], attributes[i][PR_RELEASE_ID], productRelease);
		std::cout << productRelease.productName << ", " << productRelease.releaseID << 
					 ", " << productRelease.releaseDate << std::endl;
	}

	// Close the product release file
	closeProductReleaseFile();




	// std::cout << "AFTER TEST: The product we retrieved and stored into our empty product is named " << 
	// 			 '"' << product2.name << '"' << std::endl;

	// // Final evaluation
	// std::cout << "Test evaluation: ";
	// if (std::strcmp("testProduct", product2.name) == STRCMP_TRUE) {
	// 	std::cout << "passed" << std::endl;
	// } else {
	// 	std::cout << "failed" << std::endl;
	// }
}

// ---------------------------------------------------------
// Function: runAllTests
void runAllTests() {
    testCreateProductRelease();
}
