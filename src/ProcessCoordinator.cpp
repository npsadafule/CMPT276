// ============================================
// Module Name: ProcessCoordinator.cpp
// ============================================
// Version History:
// Rev. 1 - 2024/07/01 - Group 7
// ============================================

#include "ProcessCoordinator.h"
#include "Product.h"
#include "ChangeRequest.h"
#include "Report.h"
#include "User.h"
#include "UserInterface.h"
#include <iostream>
#include <vector>
#include <map>

// Global variables
extern std::vector<Product> products;
extern std::vector<User> users;
extern std::map<std::string, std::string> changeRequests;

// Function Implementations
// ============================================

// ---------------------------------------------------------
// Function: handleProductMaintenance
void handleProductMaintenance(
    int choice    // in
) {
    // Description:
    // Handles product maintenance options based on the user's menu choice. It allows the user to
    // create a new product or a release for an existing product.
    char X;
    switch (choice) {
        case 1: {
            std::string productName;
            std::cout << "\nEnter the Product Name (max 30 char): \n \n";
            std::cin.ignore();
            std::getline(std::cin, productName);
            std::cout << "\nAre you sure you want to add the product " << productName << " (Y/N)? \n \n";
            std::cin >> X;
            if (X == 'Y') {
                createProduct(productName);
                std::cout << "\nDo you wish to add another product (Y/N)? \n \n";
                std::cin >> X;
                if (X == 'Y') {
                    handleProductMaintenance(1);
                } else {
                    break;
                }
            } else {
                break;
            }
        }
        case 2: {
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
                createRelease(productName, releaseID, releaseDate);
                std::cout << "\nDo you wish to add another release (Y/N)? \n \n";
                std::cin >> X;
                if (X == 'Y') {
                    handleProductMaintenance(2);
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
void handleChangeRequestMaintenance(
    int choice    // in
) {
    // Description:
    // Handles change request maintenance options based on the user's menu choice. It allows the user to
    // add a new change request.
    switch (choice) {
        case 1: {
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
                std::cout << "Are you a Customer or an Employee? (C/E): ";
                std::getline(std::cin, newUser.role);
                if (newUser.role == "E") {
                    std::cout << "Enter the name of the employee’s department (max 30 char): ";
                    std::getline(std::cin, newUser.department);
                }
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
void handleChangeItemMaintenance(
    int choice    // in
) {
    // Description:
    // Handles change item maintenance options based on the user's menu choice. It allows the user to
    // query or update a change item.
    switch (choice) {
        case 1: {
            std::string productName, changeID;
            std::cout << "Select a product (must pre-exist): ";
            std::cin.ignore();
            std::getline(std::cin, productName);
            std::cout << "Enter the Change ID: ";
            std::getline(std::cin, changeID);
            queryChangeItem(productName, changeID);
            break;
        }
        case 2: {
            std::string productName, changeID, newState;
            std::cout << "Select a product (must pre-exist): ";
            std::cin.ignore();
            std::getline(std::cin, productName);
            std::cout << "Enter the Change ID: ";
            std::getline(std::cin, changeID);
            std::cout << "Enter the new state: ";
            std::getline(std::cin, newState);
            updateChangeItem(productName, changeID, newState);
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
void handleReportGeneration(
    int choice    // in
) {
    // Description:
    // Handles report generation options based on the user's menu choice. It allows the user to
    // generate reports based on change items or change requests.
    switch (choice) {
        case 1: {
            std::string productName;
            std::cout << "Enter the product name to generate Report #1: ";
            std::cin.ignore();
            std::getline(std::cin, productName);
            generateReport1(productName);
            break;
        }
        case 2: {
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
    // Description:
    // Displays help information about the system and how to use it.
    std::cout << "Help: This system is designed to manage and track issues, such as bugs and feature requests, within a software development environment.\n";
    std::cout << "At any point, type 'Help' to receive guidance on the available options and how to use them.\n";
}
