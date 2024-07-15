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

// Variables for navigation options
int entryCount;

// Function Implementations
// ============================================

// Display functions for Scenario 4.1
// ============================================
// ---------------------------------------------------------
// Function: verifyAddingProduct
void confirmAddingProduct() {
	std::cout << "\nAre you sure you want to add the product (1 for Y, 0 for N)?\n";
}

// Function: doYouWantAnotherProduct
void doYouWantAnotherProduct() {
	std::cout << "\nDo you wish to add another product (1 for Y, 0 for N)?\n";
}

// Display functions for Scenario 4.2
// ============================================
// ---------------------------------------------------------
void confirmAddingProdRel() {
	std::cout << "\nAre you sure you want to add this product release (1 for Y, 0 for N)?\n" <<
	std::endl;
}

void doYouWantAnotherProdRel() {
	std::cout << "\nDo you wish to add another release (1 for Y, 0 for N)?\n" << std::endl;
}

// Display functions for Scenario 4.3
// ============================================
// ---------------------------------------------------------
// For use for A5 release.
void requesterOptions() {
	std::cout << "=== Enter '" << std::to_string(entryCount+1) << "' for previous 20 items, '" <<
				 std::to_string(entryCount+2) << "' for next 20 items ===" << std::endl <<
				 "=== 0 (zero) for exiting the list ===" << std::endl;
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

				// Product name read
				do {
					std::cout << "\nEnter the Product Name (max 30 char, must not exist): \n";
					std::cin.getline(productName, PRODUCT_NAME_LENGTH);

					// Check if input length is valid
					if (std::cin.fail()) {
						std::cin.clear(); // Clear the fail state
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
						std::cout << "\nInvalid input. Please enter 1 to 30 characters." << std::endl;
						notProperLen = true; // Continue the loop
						exists = false; // Reset exists flag
					} else if (strlen(productName) == 0) {
						std::cout << "\nProduct name cannot be empty. Please enter 1 to 30 characters." << std::endl;
						notProperLen = true; // Continue the loop
						exists = false; // Reset exists flag
					} else {
						// Check if the product already exists
						exists = retrieveProductByName("products.dat", productName, tmpProd);
						if (exists) {
							std::cout << "\nThe product already exists!" << std::endl;
						}
						notProperLen = false; // Exit the loop if both conditions are false
					}
				} while (notProperLen || exists);

				// Final choices
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
				bool ifUniqueProdRel;
				
				do {
					do {
						std::cout << "\nEnter the Product Name (max 30 char, must pre-exist): \n";
						std::cin.getline(productName, PRODUCT_NAME_LENGTH);

						// Check if input length is valid
						if (std::cin.fail()) {
							std::cin.clear(); // Clear the fail state
							std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
							std::cout << "\nInvalid input. Please enter 1 to 30 characters." << std::endl;
							notProperLen = true; // Continue the loop
							notExists = false; // Reset notExists flag
						} else if (strlen(productName) == 0) {
							std::cout << "\nProduct name cannot be empty. Please enter 1 to 30 characters." << std::endl;
							notProperLen = true; // Continue the loop
							notExists = false; // Reset notExists flag
						} else {
							// Check if the product exists
							notExists = !retrieveProductByName("products.dat", productName, tmpProd);
							if (notExists) {
								std::cout << "\nThe product must exist!" << std::endl;
							}
							notProperLen = false; // Exit the loop if both conditions are false
						}
					} while (notProperLen || notExists);

					// Get a product release ID
					do {
						std::cout << "\nEnter the Release ID (max 8 char following your organization's format): \n";
						std::cin.getline(releaseID, RELEASE_ID_LENGTH);

						// Check if input length is valid
						if (std::cin.fail()) {
							std::cin.clear(); // Clear the fail state
							std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
							std::cout << "\nInvalid input. Please enter 1 to 8 characters." << std::endl;
							notProperLen = true;
						} else {
							// Check if input is empty (0 characters)
							notProperLen = strlen(releaseID) == 0;
							if (notProperLen) {
								std::cout << "\nInput cannot be empty. Please enter 1 to 8 characters." << std::endl;
							}
						}
					} while (notProperLen);

					// Check for uniquenes by product release ID
					ifUniqueProdRel = retrieveProductReleaseByKey("productReleases.dat", productName, releaseID, tmpRel);
					if (ifUniqueProdRel)
					{
						std::cout << "You must enter a product release that has a unique compound primary key " 
						"(i.e., unique combination of product name and release ID).\n";
					}
				} while (ifUniqueProdRel);				

				// Get a release date
				do {
					std::cout << "\nEnter the release date (YYYYMMDD)): \n \n";
					std::cin.getline(releaseDate, RELEASE_DATE_LENGTH);

					notProperLen = std::cin.fail() || strlen(releaseDate) != 8;

					if (notProperLen) {
						std::cin.clear(); // Clear the fail state
						std::cout << "\nThe release date must be 8 characters!" << std::endl;
					}
				} while (notProperLen);

				// Final choices
				choiceConfirmAdd = readIntegerInput(confirmAddingProdRel,NO,YES);
				if (choiceConfirmAdd == YES) {
					createProductRelease(productName,releaseID,releaseDate);
					choiceRepeat = readIntegerInput(doYouWantAnotherProdRel,NO,YES);
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
        default: 
            std::cout << "Invalid choice. Please try again.\n";
    }
}

// ---------------------------------------------------------
// Function: handleChangeRequestMaintenance
void handleChangeRequestMaintenance(int choice) {
    // std::vector<User> users; // Declare the 'users' variable
	int requesterChoice; // For use in A5 release.
    switch (choice) {
        case 1: {
		// Scenario 4.3: Create Change Request
		// String used
		char requester[REQ_NAME_LENGTH];
		bool repeat = false;

		// Options for displaying and an input confirmation screen
		do
		{
			std::cout << "end of program so far" << std::endl;
			std::cin.get();
		} while (repeat);


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
        }
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
