#include "SystemController.h"
#include "Product.h"
#include "ChangeRequest.h"
#include "Report.h"
#include "Requester.h"
#include "ChangeItem.h"
#include <iostream>
#include <fstream>

// Global variable definitions
std::vector<Product> products;
// std::vector<User> users;
std::map<std::string, ChangeRequest> changeRequests;
// Global file streams
std::fstream requesterFile;
std::fstream productFile;
std::fstream productReleaseFile;
std::fstream changeRequestFile;
std::fstream changeItemFile;
std::fstream highestCIDFile;


// ============================================
// Function Implementations
// ============================================

// ---------------------------------------------------------
// Function: initRequester
// Initializes the requester file stream for reading and writing requesters.
// Ensures the requesterFile stream is opened in binary append mode.
void initRequester() {
    requesterFile.open("requestersFile.dat", std::ios::in | std::ios::out | std::ios::binary | std::ios::app);
    if (!requesterFile.is_open()) {
        std::cerr << "Failed to open requestersFile.dat file.\n";
        exit(1);
    }
}

// ---------------------------------------------------------
// Function: initProduct
// Initializes the product and product release file streams for reading and writing products.
// Ensures both productFile and productReleaseFile streams are opened in binary append mode.
void initProduct() {
    productFile.open("products.dat", std::ios::in | std::ios::out | std::ios::binary | std::ios::app);
    if (!productFile.is_open()) {
        std::cerr << "Failed to open products.dat file.\n";
        exit(1);
    }

    productReleaseFile.open("productReleases.dat", std::ios::in | std::ios::out | std::ios::binary | std::ios::app);
    if (!productReleaseFile.is_open()) {
        std::cerr << "Failed to open productReleases.dat file.\n";
        exit(1);
    }
}

// ---------------------------------------------------------
// Function: initChangeRequest
// Initializes the change request file stream for reading and writing change requests.
// Ensures the changeRequestFile stream is opened in binary append mode.
void initChangeRequest() {
    changeRequestFile.open("changeRequests.dat", std::ios::in | std::ios::out | std::ios::binary | std::ios::app);
    if (!changeRequestFile.is_open()) {
        std::cerr << "Failed to open changeRequests.dat file.\n";
        exit(1);
    }
}

// ---------------------------------------------------------
// Function: initChangeItem
// Initializes the change item file stream for reading and writing change items.
// Ensures the changeItemFile stream is opened in binary append mode.
void initChangeItem() {
    changeItemFile.open("changeItems.dat", std::ios::in | std::ios::out | std::ios::binary);
    if (!(changeItemFile.is_open())) {
        std::cerr << "Failed to open changeItem.dat file.\n";
		exit(1);
    }
}

// ---------------------------------------------------------
// Function: initReportGen
// Initializes the report generation functionality.
// This function is currently to be determined (TBD) and has no implementation.
void initReportGen() {
    // TBD
}

// ---------------------------------------------------------
// Function: initHighestCID
// Initializes the highest change ID file stream for reading and writing.
// Ensures the highestCIDFile stream is opened in binary append mode.
void initHighestCID() {
    highestCIDFile.open("highestCID.dat", std::ios::in | std::ios::out | std::ios::binary);
    if (!(highestCIDFile.is_open())) {
        std::cerr << "Failed to open highestCID.dat file.\n";
        exit(1);
    }
}

// ---------------------------------------------------------
// Function: start
// Starts the system, initializing all necessary components.
// Calls functions to initialize requester, product, change request, change item,
// report generation, and highest change ID functionalities.
void start() {
	initRequester();
    initProduct();
    initChangeRequest();
    initChangeItem();
    initReportGen();
	initHighestCID();
	storeHighestCID();
}

// ---------------------------------------------------------
// Function: shutdown
// Shuts down the system, closing all open file streams.
// Calls functions to close requester, product, change request, change item,
// and report file streams.
void shutdown() {
    closeRequesterFile();
    closeProductFile(); // Function call to close product file (not defined here)
    closeChangeRequestFile(); // Function call to close change request file (not defined here)
    closeChangeItemFile(); // Function call to close change item file (not defined here)
    closeReportFile(); // Function call to close report file (not defined here)
    closeHighestCID(); // Function call to close highest change ID file (not defined here)
}

// End of file
