// ============================================
// Module Name: UserInterface.cpp
// ============================================
// Version History:
// Rev. 1 - 2024/07/01 - Neel Sadafule
// ============================================

#include "UserInterface.h"
#include "Product.h"
#include "ChangeRequest.h"
#include "Report.h"
#include "User.h"
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

// Constants for data lengths
const int PRODUCT_NAME_LENGTH = 30;
const int CHANGE_DESCRIPTION_LENGTH = 150;
const int CHANGE_ID_LENGTH = 6;
const int STATE_LENGTH = 10;
const int RELEASE_ID_LENGTH = 8;
const int USER_NAME_LENGTH = 30;
const int PHONE_NUMBER_LENGTH = 30;
const int EMAIL_LENGTH = 30;
const int ROLE_LENGTH = 10;
const int DEPARTMENT_LENGTH = 30;

// Function Declarations
// ============================================
void start();
void startMainMenu();
void handleProductMaintenance();
void handleChangeRequestMaintenance();
void handleChangeItemMaintenance();
void handleReportGeneration();
void displayHelp();
void shutdown();

// Function Implementations
// ============================================

// ---------------------------------------------
// Function: start
// Description: Initializes the system and opens necessary files.
// ---------------------------------------------
void start() {
    std::ifstream inputFile("dummy_data.bin", std::ios::binary);
    if (!inputFile.is_open()) {
        std::cerr << "Error opening input file.\n";
        exit(1);
    }

    int numProducts;
    inputFile.read(reinterpret_cast<char*>(&numProducts), sizeof(numProducts));
    products.resize(numProducts);

    for (int i = 0; i < numProducts; ++i) {
        products[i].name.resize(PRODUCT_NAME_LENGTH);
        inputFile.read(&products[i].name[0], PRODUCT_NAME_LENGTH);

        int numChangeItems;
        inputFile.read(reinterpret_cast<char*>(&numChangeItems), sizeof(numChangeItems));

        for (int j = 0; j < numChangeItems; ++j) {
            ChangeItem item;
            item.description.resize(CHANGE_DESCRIPTION_LENGTH);
            item.changeID.resize(CHANGE_ID_LENGTH);
            item.state.resize(STATE_LENGTH);
            item.anticipatedReleaseID.resize(RELEASE_ID_LENGTH);

            inputFile.read(&item.description[0], CHANGE_DESCRIPTION_LENGTH);
            inputFile.read(&item.changeID[0], CHANGE_ID_LENGTH);
            inputFile.read(&item.state[0], STATE_LENGTH);
            inputFile.read(&item.anticipatedReleaseID[0], RELEASE_ID_LENGTH);

            products[i].changeItems[item.changeID] = item;
        }
    }

    int numUsers;
    inputFile.read(reinterpret_cast<char*>(&numUsers), sizeof(numUsers));
    users.resize(numUsers);

    for (int i = 0; i < numUsers; ++i) {
        users[i].name.resize(USER_NAME_LENGTH);
        users[i].phoneNumber.resize(PHONE_NUMBER_LENGTH);
        users[i].email.resize(EMAIL_LENGTH);
        users[i].role.resize(ROLE_LENGTH);

        inputFile.read(&users[i].name[0], USER_NAME_LENGTH);
        inputFile.read(&users[i].phoneNumber[0], PHONE_NUMBER_LENGTH);
        inputFile.read(&users[i].email[0], EMAIL_LENGTH);
        inputFile.read(&users[i].role[0], ROLE_LENGTH);

        if (users[i].role == "Employee") {
            users[i].department.resize(DEPARTMENT_LENGTH);
            inputFile.read(&users[i].department[0], DEPARTMENT_LENGTH);
        }
    }

    inputFile.close();
    std::cout << "System initialized with data from dummy_data.bin\n";
}

// ---------------------------------------------
// Function: startMainMenu
// Description: Starts the main menu loop.
// ---------------------------------------------
void startMainMenu() {
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

// ---------------------------------------------
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

// ---------------------------------------------
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

// ---------------------------------------------
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

// ---------------------------------------------
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

// ---------------------------------------------
// Function: displayHelp
// Description: Displays help information.
// ---------------------------------------------
void displayHelp() {
    std::cout << "Help: This system is designed to manage and track issues, such as bugs and feature requests, within a software development environment.\n";
    std::cout << "At any point, type 'Help' to receive guidance on the available options and how to use them.\n";
}

// ---------------------------------------------
// Function: shutdown
// Description: Shuts down the system and closes any open files.
// ---------------------------------------------
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
        outputFile.write(user.role.data(), ROLE_LENGTH);
        if (user.role == "Employee") {
            outputFile.write(user.department.data(), DEPARTMENT_LENGTH);
        }
    }

    outputFile.close();
    std::cout << "System data written to output.txt\n";
}
