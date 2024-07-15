#include "ProcessCoordinator.h"
#include "Product.h"
#include "ChangeRequest.h"
#include "Report.h"
#include "Requester.h"
#include "UserInterface.h"
#include <iostream>

// Constants for repeating a scneario
const int CREATE_PROD = 1;
const int CREATE_PROD_REL = 2;
static const int YES = 1;
static const int NO = 0;

// Function Implementations
// ============================================

// Display functions for Scenario 4.1
// ============================================
// ---------------------------------------------------------
// Function: verifyAddingProduct
void confirmAddingProduct() {
	std::cout << "\nAre you sure you want to add the product (1 for Y, 0 for N)?\n";
}

void doYouWantAnotherProduct() {
	std::cout << "\nDo you wish to add another product (1 for Y, 0 for N)?\n";
}

// Functions for Executing Scenarios
// ============================================
// ---------------------------------------------------------
// Function: handleProductMaintenance
void handleProductMaintenance(int choice) {
    int choiceConfirmAdd;
	int choiceRepeat;
    switch (choice) {
        case 1: {
			bool repeat = false;
			do
			{
				// Scenario 4.1: Creating a Product - duplication prevention logic not implemented
				char productName[PRODUCT_NAME_LENGTH];
				Product tmpProd;
				int notProperLen;
				int exists;

				// ABOUT TO IMPLEMENT READ FUNCTION
				do {
					std::cout << "\nEnter the Product Name (max 30 char, must not exist): \n \n";
					std::cin.getline(productName, PRODUCT_NAME_LENGTH);

					notProperLen = std::cin.fail() || strlen(productName) == 0;
					exists = retrieveProductByName("products.dat", productName, tmpProd);

					if (notProperLen) {
						std::cin.clear(); // Clear the fail state
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
						std::cout << "\nThe product name must be 1 to 30 characters!" << std::endl;
					} else if (exists) {
						std::cout << "\nThe product must not exist!" << std::endl;
					}
				} while (notProperLen || exists);
				choiceConfirmAdd = readIntegerInput(confirmAddingProduct,NO,YES);
				if (choiceConfirmAdd == YES) {
					createProduct(productName);
					choiceRepeat = readIntegerInput(doYouWantAnotherProduct,NO,YES);
					if (choiceRepeat == YES) {
						repeat = true;
					} else {
						break;
					}
				} else {
					break;
				}
			} while (repeat);
			break;
        }
        case 2: {
			// Scenario 4.2: Creating a Release of a Product - duplication prevention logic not implemented
            char productName[PRODUCT_NAME_LENGTH], releaseID[RELEASE_ID_LENGTH], releaseDate[RELEASE_DATE_LENGTH];
            
			bool repeat = false;
			do
			{
				Product tmpProd;
				ProductRelease tmpRel;
				int notProperLen;
				int notExists;
				int exists;
				
				// Get a product name
				do {
					std::cout << "\nEnter the Product Name (max 30 char, must pre-exist): \n \n";
					std::cin.getline(productName, PRODUCT_NAME_LENGTH);

					notProperLen = std::cin.fail() || strlen(productName) == 0;
					notExists = !retrieveProductByName("products.dat", productName, tmpProd);

					if (notProperLen) {
						std::cin.clear(); // Clear the fail state
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
						std::cout << "\nThe product name must be 1 to 30 characters!" << std::endl;
					} else if (notExists) {
						std::cout << "\nThe product must exist!" << std::endl;
					}
				} while (notProperLen || notExists);

				// Get a product release ID
				do {
					std::cout << "\nEnter the Release ID (max 8 char following your organizations format): \n \n";
					std::cin.getline(releaseID, RELEASE_ID_LENGTH);

					notProperLen = std::cin.fail() || strlen(releaseID) == 0;

					if (notProperLen) {
						std::cin.clear(); // Clear the fail state
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
						std::cout << "\nThe release ID must be 1 to 8 characters!" << std::endl;
					}
				} while (notProperLen);

				std::cout << "Here's the end so far" << std::endl;
				std::cin.get();

				// Make sure that you are entering a unique product release now that you have the compound key
				do {
					std::cout << "\nEnter the Release ID (max 8 char following your organizations format): \n \n";
					std::cin.getline(releaseID, RELEASE_ID_LENGTH);

					notProperLen = std::cin.fail() || strlen(releaseID) == 0;
					exists = retrieveProductReleaseByKey("productReleases.dat", productName, releaseID, tmpRel);

					if (notProperLen) {
						std::cin.clear(); // Clear the fail state
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
						std::cout << "\nThe release ID must be 1 to 8 characters!" << std::endl;
					} else if (exists) {
						std::cout << "\nThe release ID must not exist!" << std::endl;
					}
				} while (notProperLen || exists);

				// Get a product release date

				
				
			} while (repeat);
			break;
			
            // std::cout << "\nEnter the Release ID (max 8 char following your organization's format): \n \n";
            // std::cin.ignore();
			// std::cin.getline(releaseID,RELEASE_ID_LENGTH);

            // std::cout << "\nEnter the Release Date (YYYYMMDD): \n \n";
            // std::cin.ignore();
			// std::cin.getline(releaseDate, RELEASE_DATE_LENGTH);

            // std::cout << "\nAre you sure you want to add the release " << releaseID << " for Product " << productName << " (Y/N)? \n \n";
            // std::cin >> X;
            // if (X == 'Y') {
            //     createProductRelease(productName, releaseID, releaseDate);
            //     std::cout << "\nDo you wish to add another release (Y/N)? \n \n";
            //     std::cin >> X;
            //     if (X == 'Y') {
            //         handleProductMaintenance(CREATE_PROD_REL);
            //     } else {
            //         break;
            //     }
            // } else {
            //     break;
            // }
        }
        default: 
            std::cout << "Invalid choice. Please try again.\n";
    }
}

// ---------------------------------------------------------
// Function: handleChangeRequestMaintenance
void handleChangeRequestMaintenance(int choice) {
    // std::vector<User> users; // Declare the 'users' variable
    switch (choice) {
    //     case 1: {
	// 	// Scenario 4.3: Create Change Request
    //         std::string profileName, productName, changeID, description, anticipatedReleaseID;
    //         std::cout << "Select your profile (enter name or 'new' to create a new profile): ";
    //         std::cin.ignore();
    //         std::getline(std::cin, profileName);

    //         if (profileName == "new") {
    //             User newUser;
    //             std::cout << "Enter the Customer Name (max 30 char): ";
    //             std::getline(std::cin, newUser.name);
    //             std::cout << "Enter the phone number of the customer (max 30 char in the format (DDD)DDD-DDDD): ";
    //             std::getline(std::cin, newUser.phoneNumber);
    //             std::cout << "Enter the email of the customer (max 30 char in the format username@email_provider.domain_type): ";
    //             std::getline(std::cin, newUser.email);
    //             std::cout << "If you are an employee, enter a department (max 30 char); otherwise, enter 'N/A': ";
    //             std::getline(std::cin, newUser.department);
    //             users.push_back(newUser);
    //             profileName = newUser.name;
    //         }

    //         std::cout << "Select a product (must pre-exist): ";
    //         std::getline(std::cin, productName);

    //         std::cout << "Enter the Change ID (6 digit number): ";
    //         std::getline(std::cin, changeID);
    //         std::cout << "Enter the description for the product (max 150 char): ";
    //         std::getline(std::cin, description);
    //         std::cout << "Enter the Anticipated Release ID for the product (max 8 char): ";
    //         std::getline(std::cin, anticipatedReleaseID);

    //         createChangeRequest(profileName, productName, changeID, description, anticipatedReleaseID);
    //         break;
    //     }
        default: 
            std::cout << "Invalid choice. Please try again.\n";
    }
}

// ---------------------------------------------------------
// Function: handleChangeItemMaintenance
void handleChangeItemMaintenance(int choice) {
    switch (choice) {
        case 1: {
		// Scenario 4.4: Querying Change Items
            std::string productName, changeID;
            std::cout << "Select a product (must pre-exist): ";
            std::cin.ignore();
            std::getline(std::cin, productName);
            std::cout << "Enter the Change ID: ";
            std::getline(std::cin, changeID);
            queryChangeRequest(productName, changeID);
            break;
        }
        case 2: {
		// Scenario 4.5: Update/Assess Change Item
            std::string productName, changeID, newState;
            std::cout << "Select a product (must pre-exist): ";
            std::cin.ignore();
            std::getline(std::cin, productName);
            std::cout << "Enter the Change ID: ";
            std::getline(std::cin, changeID);
            std::cout << "Enter the new state: ";
            std::getline(std::cin, newState);
            updateChangeRequest(productName, changeID, newState);
            break;
        }
        default: 
            std::cout << "Invalid choice. Please try again.\n";
    }
}

// ---------------------------------------------------------
// Function: handleReportGeneration
void handleReportGeneration(int choice) {
    switch (choice) {
        case 1: {
		// Scenario 4.6: Report #1: List of All Change Items for a 
		// Particular Product that are Not Done and Not Cancelled
            std::string productName;
            std::cout << "Enter the product name to generate Report #1: ";
            std::cin.ignore();
            std::getline(std::cin, productName);
            generateReport1(productName);
            break;
        }
        case 2: {
		// Scenario 4.7: Report #2: List of Customers/Staff Who Need to Be Informed When
		// a Particular Change Has Been Implemented, and in What ProductRelease ID
            std::string changeID;
            std::cout << "Enter the Change ID to generate Report #2: ";
            std::cin.ignore();
            std::getline(std::cin, changeID);
            generateReport2(changeID);
            break;
        }
        default: 
            std::cout << "Invalid choice. Please try again.\n";
    }
}

// ---------------------------------------------------------
// Function: displayHelp
void displayHelp() {
    std::cout << "Help: This system is designed to manage and track issues, such as bugs and feature requests, within a software development environment.\n";
    std::cout << "At any point, type 'Help' to receive guidance on the available options and how to use them.\n";
}
