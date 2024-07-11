#include "ProcessCoordinator.h"
#include "Product.h"
#include "ChangeRequest.h"
#include "Report.h"
#include "User.h"
#include "UserInterface.h"
#include <iostream>

// Function Implementations
// ============================================

// Constants for repeating a scneario
const int CREATE_PROD = 1;
const int CREATE_PROD_REL = 2;

// ---------------------------------------------------------
// Function: handleProductMaintenance
void handleProductMaintenance(int choice) {
    char X;
    switch (choice) {
        case 1: {
		// Scenario 4.1: Creating a Product
            char productName[PROD_NAME_LEN];
            std::cout << "\nEnter the Product Name (max 30 char): \n \n";
            std::cin.ignore();
            std::cin.getline(productName,PROD_NAME_LEN);
            std::cout << "\nAre you sure you want to add the product " << productName << " (Y/N)? \n \n";
            std::cin >> X;
            if (X == 'Y') {
                createProduct(productName);
                std::cout << "\nDo you wish to add another product (Y/N)? \n \n";
                std::cin >> X;
                if (X == 'Y') {
                    handleProductMaintenance(CREATE_PROD);
                } else {
                    break;
                }
            } else {
                break;
            }
        }
        case 2: {
		// Scenario 4.2: Creating a Release of a Product
            std::string productName, releaseID, releaseDate;
            std::cout << "\nEnter the Product Name (max 30 char, must pre-exist): \n \n";
            std::cin.ignore();
            std::getline(std::cin, productName);
            std::cout << "\nEnter the Release ID (max 30 char following your organization's format): \n \n";
            std::getline(std::cin, releaseID);
            std::cout << "\nEnter the Release Date (YYYY-MM-DD): \n \n";
            std::getline(std::cin, releaseDate);
            std::cout << "\nAre you sure you want to add the release " << releaseID << " for Product " << productName << " (Y/N)? \n \n";
            std::cin >> X;
            if (X == 'Y') {
                createProductRelease(productName, releaseID, releaseDate);
                std::cout << "\nDo you wish to add another release (Y/N)? \n \n";
                std::cin >> X;
                if (X == 'Y') {
                    handleProductMaintenance(CREATE_PROD_REL);
                } else {
                    break;
                }
            } else {
                break;
            }
        }
        case 0: 
            activateUI();
            break;
        default: 
            std::cout << "Invalid choice. Please try again.\n";
    }
}

// ---------------------------------------------------------
// Function: handleChangeRequestMaintenance
void handleChangeRequestMaintenance(int choice) {
    std::vector<User> users; // Declare the 'users' variable
    switch (choice) {
        case 1: {
		// Scenario 4.3: Create Change Request
            std::string profileName, productName, changeID, description, anticipatedReleaseID;
            std::cout << "Select your profile (enter name or 'new' to create a new profile): ";
            std::cin.ignore();
            std::getline(std::cin, profileName);

            if (profileName == "new") {
                User newUser;
                std::cout << "Enter the Customer Name (max 30 char): ";
                std::getline(std::cin, newUser.name);
                std::cout << "Enter the phone number of the customer (max 30 char in the format (DDD)DDD-DDDD): ";
                std::getline(std::cin, newUser.phoneNumber);
                std::cout << "Enter the email of the customer (max 30 char in the format username@email_provider.domain_type): ";
                std::getline(std::cin, newUser.email);
                std::cout << "If you are an employee, enter a department (max 30 char); otherwise, enter 'N/A': ";
                std::getline(std::cin, newUser.department);
                users.push_back(newUser);
                profileName = newUser.name;
            }

            std::cout << "Select a product (must pre-exist): ";
            std::getline(std::cin, productName);

            std::cout << "Enter the Change ID (6 digit number): ";
            std::getline(std::cin, changeID);
            std::cout << "Enter the description for the product (max 150 char): ";
            std::getline(std::cin, description);
            std::cout << "Enter the Anticipated Release ID for the product (max 8 char): ";
            std::getline(std::cin, anticipatedReleaseID);

            createChangeRequest(profileName, productName, changeID, description, anticipatedReleaseID);
            break;
        }
        case 0: 
            activateUI();
            break;
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
        case 0: 
            activateUI();
            break;
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
        case 0: 
            activateUI();
            break;
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
