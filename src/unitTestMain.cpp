// ============================================
// Module Name: unitTestMain.cpp
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
#include "ChangeRequest.h"
#include "Report.h"
#include "Requester.h"
#include "SystemController.h"
#include "ChangeItem.h"

// Non-exported module-scope constant
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
// ---------------------------------------------------------
// Function: main
int main() {
    // Entry point of the program. Runs all test functions and prints end message.
    // Returns: int (Exit status, 0 indicates successful execution)
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
    // Test function for creating a product and verifying its storage and retrieval.
	// ORIGINAL TEST

	// String we are testing
	char testString[PRODUCT_NAME_LENGTH] = "ProductXXX";

	// Open the file
	openProductFile();

	// Run the function
	Product product2 = {"tmpName"};
	std::cout << "BEFORE TEST: Our 'empty' product on RAM has the name " << '"' << product2.name << '"' << std::endl;

	// Run the function
	std::cout << "Running createProduct()..." << std::endl;
    createProduct(testString);

	// Read "joey" out of file
	retrieveProductByName(testString, product2);

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
        // // Loop forward by the number of test products we have to store them on file
	// for (int i=0; i<5; i++)
	// {
	// 	createProduct(attributes[i]);
	// }

	// // Read "joey" out of file
        // // Loop forward by the numbre of test products we have to retrieve them from file
	// for (int i=0; i<5; i++)
	// {
	// 	retrieveProductByName(attributes[i], product2);
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
	
	// // Test sequential reading
	// seekToBeginningOfProductFile();
	// productFileDisplay20OrLess("products.dat");

	// // Close the product file
	// closeProductFile();

	// ==========================================
	// CHANGE ITEM TEST

	

}

// ---------------------------------------------------------
// Function: testCreateChangeItem
void testCreateChangeItem() {
    // Test function for creating change items and verifying their storage and retrieval.
	// Test data
	const ChangeItem CITest[3] {
		{3, "Product A", "Sample description while", "R51B", "Reported"},
		{4, "RandThing", "The quick brown lazy dog", "AB12", "Reported"},
		{6, "Random", "Hahahhahahahahahha", "APO1", "Reported"}
	};

	// Open the file
	openChangeItemFile();

	// Pre-test initialization and output
	ChangeItem displayCI = {1682, "testName", "testDesc", "AJK3", "Reported"};

	std::cout << "BEFORE tmp change item: " << intToCString(displayCI.changeID) << " " << displayCI.productName <<
				 " " << displayCI.description << " " << displayCI.anticipatedReleaseID << " " << 
				 displayCI.state << std::endl;
	
	// Run the function
	std::cout << "Running createChangeItem()..." << std::endl;
        // Loop forward by the number of test change items there are to store them into file
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
    // Loop forward by the number of test change items there are to retrieve them from file
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

	// Test sequential reading
	// seekToBeginningOfChangeItemFile();
	// changeItemFileDisplay20OrLess("changeItems.dat");

	// Close the change item file
	closeChangeItemFile();
}

// ---------------------------------------------------------
// Function: testCreateRequester
void testCreateRequester() {
    // Test function for creating requesters and verifying their storage and retrieval.
	// Test data
	const Requester reqTest[2] {
		{"HMMMMMMM", "6041237654", "fakeemail@yahoo.com", "Engineering"},
		{"mama", "7784039872", "asedf@gmail.com", "N/A"}
	};

	// Open the file
	openRequesterFile();

	// Pre-test initialization and output
	Requester displayReq = {"tmpName", "tmpNum", "tmpEmail", "tmpDep"};
	std::cout << "BEFORE displayReq: " << displayReq.reqName << " " << displayReq.phoneNumber <<
				 " " << displayReq.email << " " << displayReq.department << std::endl;

	// Run the function
	std::cout << "Running createRequester()..." << std::endl;
    // Store the attribute test data as product releases
    // Loop forward by the number of test requesters to store them on file
    for (int i=0; i<2; i++) {
        createRequester(reqTest[i].reqName,reqTest[i].phoneNumber,reqTest[i].email,reqTest[i].department);
    }
	
	// Read entries out of file, and tally correct outputs
	std::cout << "AFTER TEST: The requesters we retrieved and stored into our empty product are the following:" << std::endl;

	// Initialize tally
	int correctTally = 0;
    // Loop forward by the number of test requesters to retrieve them from file 
    for (int i=0; i<2; i++) {
		// Perform the retrieval
		retrieveRequesterByKey(reqTest[i].reqName, displayReq);
		
		// Count if desired product release was retrieved
		if ((std::strcmp(displayReq.reqName, reqTest[i].reqName) == STRCMP_TRUE)) {
			correctTally++;
		}

		// Display to the user
		std::cout << displayReq.reqName << 
					 ", " << displayReq.phoneNumber << 
					 ", " << displayReq.email <<
					 ", " << displayReq.department << std::endl;
	}

	// Final evaluation
	std::cout << "Test evaluation: ";
	if (correctTally == 2) {
		std::cout << "passed" << std::endl;
	} else {
		std::cout << "failed" << std::endl;
	}

	// Test sequential reading
	// seekToBeginningOfRequesterFile();
	// requesterFileDisplay20OrLess("requestersFile.dat");

	// Close the product release file
	closeRequesterFile();
}

// ---------------------------------------------------------
// Function: testCreateChangeRequest
void testCreateChangeRequest() {
    // Test function for creating change requests and verifying their storage and retrieval.
	// Test data
	const ChangeRequest CRTest[2] {
		{"HMMMMMMM", 1234, "A1CD", "20040923", "1"},
		{"mama", 5678, "MA34", "20240913", "2"}
	};

	// Open the file
	openChangeRequestFile();

	// Pre-test initialization and output
	ChangeRequest displayCR = {"asdf", 3893, "MA34", "20240923", "3"};
	std::cout << "BEFORE displayCR: " << displayCR.requesterName << " " << intToCString(displayCR.changeID) << " " << displayCR.reportedRelease <<
				 " " << displayCR.reportedDate << " " << displayCR.priority << std::endl;

	// Run the function
	std::cout << "Running createChangeRequest()..." << std::endl;
    // Loop forward by the number of test change requests to store them on file
    for (int i=0; i<2; i++) {
        createChangeRequest(CRTest[i].requesterName,
						CRTest[i].changeID,
						CRTest[i].reportedRelease,
						CRTest[i].reportedDate,
						CRTest[i].priority);
    }
	
	// Read entries out of file, and tally correct outputs
	std::cout << "AFTER TEST: The change requests we retrieved and stored into our empty product are the following:" << std::endl;

	// Initialize tally
	int correctTally = 0;
    // Loop forward by the number of test change requests to retrieve them from file
    for (int i=0; i<2; i++) {
		// Perform the retrieval
		retrieveChangeRequestByKey("changeRequests.dat", 
								   CRTest[i].requesterName,
								   CRTest[i].changeID,
								   displayCR);
		
		// Count if desired product release was retrieved
		if ((std::strcmp(displayCR.requesterName, CRTest[i].requesterName) == STRCMP_TRUE) &&
			(displayCR.changeID == CRTest[i].changeID)) {
			correctTally++;
		}

		// Display to the user
		std::cout << displayCR.requesterName << 
					 ", " << intToCString(displayCR.changeID) << 
					 ", " << displayCR.reportedRelease <<
					 ", " << displayCR.reportedDate <<
					 ", " << displayCR.priority << std::endl;
	}

	// Final evaluation
	std::cout << "Test evaluation: ";
	if (correctTally == 2) {
		std::cout << "passed" << std::endl;
	} else {
		std::cout << "failed" << std::endl;
	}

	// // Test sequential reading
	// seekToBeginningOfRequesterFile();
	// requesterFileDisplay20OrLess("requestersFile.dat");

	// Close the product release file
	closeChangeRequestFile();
}

// ---------------------------------------------------------
// Function: runAllTests
void runAllTests() {
    // Runs all defined test functions.
    testCreateProduct();
	// std::cout << "========================================" << std::endl;
	// testCreateChangeItem();
	// std::cout << "========================================" << std::endl;
	// testCreateRequester();
	// std::cout << "========================================" << std::endl;
	// testCreateChangeRequest();
}