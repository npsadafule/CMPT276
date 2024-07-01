#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include "Product.h"
#include "ChangeRequest.h"
#include "Report.h"
#include "User.h"

// ============================================
// Module Name: main.cpp
// ============================================

// Version History:
// Rev. 1 - 2024/07/01 - Neel Sadafule

// ============================================
// Data structures
// ---------------------------------------------

std::vector<Product> products;
std::vector<User> users;
std::map<std::string, std::string> changeRequests;

// Function Declarations
// ============================================
void displayMainMenu();
void handleProductMaintenance();
void handleChangeRequestMaintenance();
void handleChangeItemMaintenance();
void handleReportGeneration();
void displayHelp();

// Main Function
// ============================================
int main() {
    displayMainMenu();
    return 0;
}

// Function Implementations
// ============================================
// Function: displayMainMenu
// Description: Displays the main menu and handles user input.
// ---------------------------------------------
void displayMainMenu() {
    int choice;
    do {
        std::cout << "\n====== Main Menu ======\n";
        std::cout << "1) Product Maintenance\n";
        std::cout << "2) Change Request Maintenance\n";
        std::cout << "3) Change Item Maintenance\n";
        std::cout << "4) Report Generation\n";
        std::cout << "0) Exit\n";
        std::cout << "Enter the number you want [0-4]: ";
        std::cin >> choice;

        switch (choice) {
            case 1: handleProductMaintenance(); break;
            case 2: handleChangeRequestMaintenance(); break;
            case 3: handleChangeItemMaintenance(); break;
            case 4: handleReportGeneration(); break;
            case 0: std::cout << "Thank you for using the Issue Tracking System.\n"; break;
            default: std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);
}

// Function: handleProductMaintenance
// Description: Handles product maintenance options.
// ---------------------------------------------
void handleProductMaintenance() {
    int choice;
    do {
        std::cout << "\n====== Product Maintenance ======\n";
        std::cout << "1) Create a Product\n";
        std::cout << "2) Create a Release of a Product\n";
        std::cout << "0) Return to Main Menu\n";
        std::cout << "Choose an option [0-2] and press ENTER: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::string productName;
                std::cout << "Enter the Product Name (max 30 char): ";
                std::cin.ignore();
                std::getline(std::cin, productName);
                createProduct(productName);
                break;
            }
            case 2: createRelease(); break;
            case 0: break;
            default: std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);
}

// Function: handleChangeRequestMaintenance
// Description: Handles change request maintenance options.
// ---------------------------------------------
void handleChangeRequestMaintenance() {
    int choice;
    do {
        std::cout << "\n====== Change Request Maintenance ======\n";
        std::cout << "1) Add a new change request\n";
        std::cout << "0) Go back to Main Menu\n";
        std::cout << "Choose an option [0-1] and press ENTER: ";
        std::cin >> choice;

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
            case 0: break;
            default: std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);
}

// Function: handleChangeItemMaintenance
// Description: Handles change item maintenance options.
// ---------------------------------------------
void handleChangeItemMaintenance() {
    int choice;
    do {
        std::cout << "\n====== Change Item Maintenance ======\n";
        std::cout << "1) Query Change Item to Screen\n";
        std::cout << "2) Update/Assess Change Item\n";
        std::cout << "0) Return to Main Menu\n";
        std::cout << "Choose an option [0-2] and press ENTER: ";
        std::cin >> choice;

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
            case 0: break;
            default: std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);
}

// Function: handleReportGeneration
// Description: Handles report generation options.
// ---------------------------------------------
void handleReportGeneration() {
    int choice;
    do {
        std::cout << "\n====== Report Generation ======\n";
        std::cout << "1) Generate Report #1\n";
        std::cout << "2) Generate Report #2\n";
        std::cout << "0) Return to Main Menu\n";
        std::cout << "Choose an option [0-2] and press ENTER: ";
        std::cin >> choice;

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
            case 0: break;
            default: std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);
}

// Function: displayHelp
// Description: Displays help information.
// ---------------------------------------------
void displayHelp() {
    std::cout << "Help: This system is designed to manage and track issues, such as bugs and feature requests, within a software development environment.\n";
    std::cout << "At any point, type 'Help' to receive guidance on the available options and how to use them.\n";
}
