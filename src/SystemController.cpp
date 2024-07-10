#include "SystemController.h"
#include "Product.h"
#include "ChangeRequest.h"
#include "Report.h"
#include "User.h"
#include <iostream>
#include <fstream>

// Global variable definitions
std::vector<Product> products;
std::vector<User> users;
std::map<std::string, ChangeRequest> changeRequests;
// Global file streams
std::fstream productFile("products.dat", std::ios::binary);

// Constants for data lengths
const int PRODUCT_NAME_LENGTH = 30;
const int CHANGE_DESCRIPTION_LENGTH = 150;
const int CHANGE_ID_LENGTH = 6;
const int STATE_LENGTH = 10;
const int RELEASE_ID_LENGTH = 8;
const int USER_NAME_LENGTH = 30;
const int PHONE_NUMBER_LENGTH = 30;
const int EMAIL_LENGTH = 30;
const int DEPARTMENT_LENGTH = 30;

// ============================================
// Function Implementations
// ============================================

// ---------------------------------------------------------
// Function: initProduct
void initProduct() {
    // Open the file for products
	if (!(productFile.is_open())) {
		// Check if we were unable to open the file
		std::cerr << "Failed to open products.dat file.\n";

    }

	// Open the file for product releases
	std::ifstream productReleasesFile("productReleases.dat", std::ios::binary);
	if (!(productReleasesFile.is_open())) {
		// Check if we were unable to open the file
		std::cerr << "Failed to open productReleases.dat file.\n";

    }
}

// ---------------------------------------------------------
// Function: initChangeRequest
void initChangeRequest() {
    std::ifstream changeRequestFile("changeRequests.dat", std::ios::binary);
    if (!(changeRequestFile.is_open())) {
        std::cerr << "Failed to open changeRequests.dat file.\n";
    }
}

// ---------------------------------------------------------
// Function: initChangeItem
void initChangeItem() {
    std::cout << "Change items are initialized as part of products.\n";
}

// ---------------------------------------------------------
// Function: initReportGen
void initReportGen() {
    std::ifstream userFile("users.dat", std::ios::binary);
    if (!(userFile.is_open())) {
        std::cerr << "Failed to open users.dat file.\n";
    }

	
}

// ---------------------------------------------------------
// Function: start
void start() {
    initProduct();
    initChangeRequest();
    initChangeItem();
    initReportGen();
}

// ---------------------------------------------------------
// Function: shutdown
void shutdown() {
    std::ofstream outputFile("output.txt", std::ios::binary);
    if (!outputFile.is_open()) {
        std::cerr << "Error opening output file.\n";
        exit(1);
    }

    int numProducts = products.size();
    outputFile.write(reinterpret_cast<const char*>(&numProducts), sizeof(numProducts));

    for (const auto &product : products) {
        outputFile.write(product.name.data(), PRODUCT_NAME_LENGTH);
        int numChangeItems = product.changeItems.size();
        outputFile.write(reinterpret_cast<const char*>(&numChangeItems), sizeof(numChangeItems));

        for (const auto &pair : product.changeItems) {
            const ChangeItem &item = pair.second;
            outputFile.write(item.description.data(), CHANGE_DESCRIPTION_LENGTH);
            outputFile.write(item.changeID.data(), CHANGE_ID_LENGTH);
            outputFile.write(item.state.data(), STATE_LENGTH);
            outputFile.write(item.anticipatedReleaseID.data(), RELEASE_ID_LENGTH);
        }
    }

    int numUsers = users.size();
    outputFile.write(reinterpret_cast<const char*>(&numUsers), sizeof(numUsers));

    for (const auto &user : users) {
        outputFile.write(user.name.data(), USER_NAME_LENGTH);
        outputFile.write(user.phoneNumber.data(), PHONE_NUMBER_LENGTH);
        outputFile.write(user.email.data(), EMAIL_LENGTH);
        outputFile.write(user.department.data(), DEPARTMENT_LENGTH);
    }

    outputFile.close();
    std::cout << "System data written to output.txt\n";
}
