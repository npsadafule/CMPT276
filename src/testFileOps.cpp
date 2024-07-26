// ============================================
// Module Name: testFileOps.cpp
// ============================================
// Version History:
// Rev. 1 - 2024/07/17 - Group 7
// ============================================

#include <iostream>
#include <cassert>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include "Product.h"

// Non-expored module-scope constants
static const int STRCMP_TRUE = 0;
// For extracting predetermined attribute test data from 'attributes' array
static const int PR_NAME = 0;
static const int PR_RELEASE_ID = 1;
static const int PR_RELEASE_DATE = 2;
static const int NUM_TEST_PR = 5;

// ============================================
// Function Declarations
// ============================================
void testCreateProductRelease();
void runAllTests();

// Main Function
// ============================================
// ---------------------------------------------------------
// Function: main
int main() {
    // Entry point of the program. Runs all test functions and prints end message.
    // Returns: int (Exit status, 0 indicates successful execution)
    runAllTests();  // Run all defined test functions
    std::cout << "End of testFileOps" << std::endl;  // Print end of tests message
    return 0;  // Exit program successfully
}

// ============================================
// Test Implementations
// ============================================
// ---------------------------------------------------------
// Function: testCreateProductRelease
void testCreateProductRelease() {
    // Test function for creating product releases and verifying their storage and retrieval.
    // This function initializes product releases with predetermined attribute data,
    // stores them in a file, retrieves them, and checks for correctness.
    // Define a 2D array of C-style strings containing the attribute test data
    const char* attributes[NUM_TEST_PR][3] = {
        {"A", "11", "20240611"},
        {"B", "12", "20240612"},
        {"C", "13", "20240613"},
        {"D", "14", "20240614"},
        {"E", "15", "20240615"}
    };

    // Open the product release file for writing
    openProductReleaseFile();

    // Pre-test initialization and output
    ProductRelease productRelease = {"tmpName", "tmpRelID", "tmpRelDate"};
    std::cout << "BEFORE TEST: Our 'empty' product release has the name \"" << productRelease.productName << "\", "
              << "the release ID \"" << productRelease.releaseID << "\", and the release date \"" << productRelease.releaseDate << "\"" << std::endl;

    // Run the function to create product releases from the attribute data
    std::cout << "Running createProductRelease()..." << std::endl;
    // Loop forward by the number of test entries of product releases that need to be created
    for (int i = 0; i < NUM_TEST_PR; ++i) {
        createProductRelease(attributes[i][PR_NAME], attributes[i][PR_RELEASE_ID], attributes[i][PR_RELEASE_DATE]);
    }

    // Read entries from the file, retrieve them, and tally correct outputs
    std::cout << "AFTER TEST: The product releases retrieved and stored into our 'empty' product release are:" << std::endl;

    // Initialize tally of correct retrievals
    int correctTally = 0;
    // Loop forward by the number of test entries of product releases that need to be retrieved
    for (int i = 0; i < NUM_TEST_PR; ++i) {
        // Retrieve product release from file
        retrieveProductReleaseByKey(attributes[i][PR_NAME], attributes[i][PR_RELEASE_ID], productRelease);

        // Check if the retrieved product release matches the expected attributes
        if ((std::strcmp(productRelease.productName, attributes[i][PR_NAME]) == STRCMP_TRUE) &&
            (std::strcmp(productRelease.releaseID, attributes[i][PR_RELEASE_ID]) == STRCMP_TRUE)) {
            correctTally++;
        }

        // Display retrieved product release information
        std::cout << productRelease.productName << ", " << productRelease.releaseID
                  << ", " << productRelease.releaseDate << std::endl;
    }

    // Final evaluation of the test
    std::cout << "Test evaluation: ";
    if (correctTally == NUM_TEST_PR) {
        std::cout << "passed" << std::endl;
    } else {
        std::cout << "failed" << std::endl;
    }

    // Close the product release file
    closeProductReleaseFile();
}

// ---------------------------------------------------------
// Function: runAllTests
void runAllTests() {
    // Function to run all defined test functions.
    testCreateProductRelease();  // Run test for creating and retrieving product releases
}