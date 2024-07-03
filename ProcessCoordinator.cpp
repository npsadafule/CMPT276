// ============================================
// Module Name: ProcessCoordinator.cpp
// ============================================
// Version History:
// Rev. 1 - 2024/07/01 - Group 7
// ============================================

#include "UserInterface.h"
#include "Product.h"
#include "ChangeRequest.h"
#include "Report.h"
#include "User.h"
#include "ProcessCoordinator.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>

// Global variables
extern std::vector<Product> products;
extern std::vector<User> users;
extern std::map<std::string, std::string> changeRequests;

// // Constants for data lengths
// const int PRODUCT_NAME_LENGTH = 30;
// const int CHANGE_DESCRIPTION_LENGTH = 150;
// const int CHANGE_ID_LENGTH = 6;
// const int STATE_LENGTH = 10;
// const int RELEASE_ID_LENGTH = 8;
// const int USER_NAME_LENGTH = 30;
// const int PHONE_NUMBER_LENGTH = 30;
// const int EMAIL_LENGTH = 30;
// const int ROLE_LENGTH = 10;
// const int DEPARTMENT_LENGTH = 30;

// Function Declarations
// ============================================

void handleProductMaintenance(int choice);
void handleChangeRequestMaintenance(int choice);
void handleChangeItemMaintenance(int choice);
void handleReportGeneration(int choice);
void displayHelp();



// ---------------------------------------------
// Function: handleProductMaintenance
// Description: Handles product maintenance options.
// ---------------------------------------------
void handleProductMaintenance(int choice) {
        switch (choice) {
            char X;
            case 1: {
                std::string productName;
                std::cout << "\nEnter the Product Name (max 30 char): \n \n";
                std::cin.ignore();
                std::getline(std::cin, productName);
                std::cout << "\nAre you sure you want to add the product ProductX (Y/N)? \n \n";
                std::cin >> X;
                if(X == 'Y'){
                createProduct(productName);
                std::cout << "\nDo you wish to add another product (Y/N)? \n \n";
                std::cin >> X;
                if(X == 'Y'){
                    handleProductMaintenance(1);
                }
                else{
                    break;
                    break;
                    break;
                }
                }
                else{
                break;
                break;
                }
            }
            case 2: createRelease(); break;
            case 0: activateUI();
            default: std::cout << "Invalid choice. Please try again.\n";
        } 
        
}

// ---------------------------------------------
// Function: handleChangeRequestMaintenance
// Description: Handles change request maintenance options.
// ---------------------------------------------
void handleChangeRequestMaintenance(int choice) {

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
            case 0: activateUI();
            default: std::cout << "Invalid choice. Please try again.\n";
        }
}

// ---------------------------------------------
// Function: handleChangeItemMaintenance
// Description: Handles change item maintenance options.
// ---------------------------------------------
void handleChangeItemMaintenance(int choice) {
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
            case 0: activateUI();
            default: std::cout << "Invalid choice. Please try again.\n";
        }
}

// ---------------------------------------------
// Function: handleReportGeneration
// Description: Handles report generation options.
// ---------------------------------------------
void handleReportGeneration(int choice) {
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
            case 0: activateUI();
            default: std::cout << "Invalid choice. Please try again.\n";
        }
}

// ---------------------------------------------
// Function: displayHelp
// Description: Displays help information.
// ---------------------------------------------
void displayHelp() {
    std::cout << "Help: This system is designed to manage and track issues, such as bugs and feature requests, within a software development environment.\n";
    std::cout << "At any point, type 'Help' to receive guidance on the available options and how to use them.\n";
}
