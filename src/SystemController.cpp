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
void initRequester() {
    requesterFile.open("requestersFile.dat", std::ios::in | std::ios::out | std::ios::binary | std::ios::app);
    if (!(requesterFile.is_open())) {
        std::cerr << "Failed to open requestersFile.dat file.\n";
		exit(1);
    }
}

// ---------------------------------------------------------
// Function: initProduct
void initProduct() {
    productFile.open("products.dat", std::ios::in | std::ios::out | std::ios::binary | std::ios::app);
	if (!(productFile.is_open())) {
		// Check if we were unable to open the file
		std::cerr << "Failed to open products.dat file.\n";
		exit(1);

    }

	productReleaseFile.open("productReleases.dat", std::ios::in | std::ios::out | std::ios::binary | std::ios::app);
	if (!(productFile.is_open())) {
		// Check if we were unable to open the file
		std::cerr << "Failed to open products.dat file.\n";
		exit(1);
    }
}

// ---------------------------------------------------------
// Function: initChangeRequest
void initChangeRequest() {
    changeRequestFile.open("changeRequests.dat", std::ios::in | std::ios::out | std::ios::binary | std::ios::app);
    if (!(changeRequestFile.is_open())) {
        std::cerr << "Failed to open changeRequests.dat file.\n";
		exit(1);
    }
}

// ---------------------------------------------------------
// Function: initChangeItem
void initChangeItem() {
    changeItemFile.open("changeItems.dat", std::ios::in | std::ios::out | std::ios::binary | std::ios::app);
    if (!(changeItemFile.is_open())) {
        std::cerr << "Failed to open changeItem.dat file.\n";
		exit(1);
    }
}

// ---------------------------------------------------------
// Function: initReportGen
void initReportGen() {
	// TBD
}

void initHighestCID() {
    highestCIDFile.open("highestCID.dat", std::ios::in | std::ios::out | std::ios::binary | std::ios::app);
    if (!(highestCIDFile.is_open())) {
        std::cerr << "Failed to open highestCID.dat file.\n";
		exit(1);
    }
}

// ---------------------------------------------------------
// Function: start
void start() {
	storeHighestCID();
	initRequester();
    initProduct();
    initChangeRequest();
    initChangeItem();
    initReportGen();
	initHighestCID();
}

// ---------------------------------------------------------
// Function: shutdown
void shutdown() {
	closeRequesterFile();
    closeProductFile();
    closeChangeRequestFile();
    closeChangeItemFile();
    closeReportFile();
	closeHighestCID();
}
