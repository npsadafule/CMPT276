#include "SystemController.h"
#include "Product.h"
#include "ChangeRequest.h"
#include "Report.h"
#include "Requester.h"
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


// ============================================
// Function Implementations
// ============================================

// ---------------------------------------------------------
// Function: initRequester
void initRequester(std::fstream& requesterFile) {
    requesterFile.open("requestersFile.dat", std::ios::in | std::ios::out | std::ios::binary | std::ios::app);
    if (!(requesterFile.is_open())) {
        std::cerr << "Failed to open requestersFile.dat file.\n";
		exit(1);
    }
}

// ---------------------------------------------------------
// Function: initProduct
void initProduct(std::fstream& productFile, std::fstream& productReleaseFile) {
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
void initChangeItem(std::fstream& changeItemFile) {
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

// ---------------------------------------------------------
// Function: start
void start() {
	initRequester(requesterFile);
    initProduct(productFile, productReleaseFile);
    initChangeRequest();
    initChangeItem(changeItemFile);
    initReportGen();
}

// ---------------------------------------------------------
// Function: shutdown
void shutdown() {
    // std::ofstream outputFile("output.txt", std::ios::binary);
    // if (!outputFile.is_open()) {
    //     std::cerr << "Error opening output file.\n";
    //     exit(1);
    // }

    // int numProducts = products.size();
    // outputFile.write(reinterpret_cast<const char*>(&numProducts), sizeof(numProducts));

    // for (const auto &product : products) {
    //     outputFile.write(product.name.data(), PRODUCT_NAME_LENGTH);
    //     int numChangeItems = product.changeItems.size();
    //     outputFile.write(reinterpret_cast<const char*>(&numChangeItems), sizeof(numChangeItems));

    //     for (const auto &pair : product.changeItems) {
    //         const ChangeItem &item = pair.second;
    //         outputFile.write(item.description.data(), CHANGE_DESCRIPTION_LENGTH);
    //         outputFile.write(item.changeID.data(), CHANGE_ID_LENGTH);
    //         outputFile.write(item.state.data(), STATE_LENGTH);
    //         outputFile.write(item.anticipatedReleaseID.data(), RELEASE_ID_LENGTH);
    //     }
    // }

    // int numUsers = users.size();
    // outputFile.write(reinterpret_cast<const char*>(&numUsers), sizeof(numUsers));

    // for (const auto &user : users) {
    //     outputFile.write(user.name.data(), USER_NAME_LENGTH);
    //     outputFile.write(user.phoneNumber.data(), PHONE_NUMBER_LENGTH);
    //     outputFile.write(user.email.data(), EMAIL_LENGTH);
    //     outputFile.write(user.department.data(), DEPARTMENT_LENGTH);
    // }

    // outputFile.close();
    // std::cout << "System data written to output.txt\n";
}
