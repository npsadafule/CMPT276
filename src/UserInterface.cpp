#include "UserInterface.h"
#include "Product.h"
#include "ChangeRequest.h"
#include "Report.h"
#include "User.h"
#include "ProcessCoordinator.h"
#include "SystemController.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>

// Global variables
extern std::vector<Product> products;
extern std::vector<User> users;
extern std::map<std::string, ChangeRequest> changeRequests;

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

// ---------------------------------------------------------
// Function: start
void start();

// ---------------------------------------------------------
// Function: activateUI
void activateUI() {
    int choice;
    do {
        system("clear");
        std::cout << "\n====== Main Menu ======\n";
        std::cout << "1) Product Maintenance\n";
        std::cout << "2) Change Request Maintenance\n";
        std::cout << "3) Change Item Maintenance\n";
        std::cout << "4) Report Generation\n";
        std::cout << "0) Exit\n";
        std::cout << "Enter the number you want [0-4]: ";
        std::cin >> choice;

        switch (choice) {
            case 1: 
                system("clear");
                std::cout << "\n====== Product Maintenance ======\n";
                std::cout << "1) Create a Product\n";
                std::cout << "2) Create a Release of a Product\n";
                std::cout << "0) Return to Main Menu\n";
                std::cout << "Choose an option [0-2] and press ENTER: ";
                std::cin >> choice;
                handleProductMaintenance(choice); break;
        
            case 2: 
                system("clear");
                std::cout << "\n====== Change Request Maintenance ======\n";
                std::cout << "1) Add a new change request\n";
                std::cout << "0) Go back to Main Menu\n";
                std::cout << "Choose an option [0-1] and press ENTER: ";
                std::cin >> choice;
                handleChangeRequestMaintenance(choice); break;
            case 3: 
                system("clear");
                std::cout << "\n====== Change Item Maintenance ======\n";
                std::cout << "1) Query Change Item to Screen\n";
                std::cout << "2) Update/Assess Change Item\n";
                std::cout << "0) Return to Main Menu\n";
                std::cout << "Choose an option [0-2] and press ENTER: ";
                std::cin >> choice;
                handleChangeItemMaintenance(choice); break;
            case 4: 
                system("clear");
                std::cout << "\n====== Report Generation ======\n";
                std::cout << "1) Generate Report #1\n";
                std::cout << "2) Generate Report #2\n";
                std::cout << "0) Return to Main Menu\n";
                std::cout << "Choose an option [0-2] and press ENTER: ";
                std::cin >> choice;
                handleReportGeneration(choice); break;
            case 0: 
                shutdown();
                std::cout << "Thank you for using the Issue Tracking System.\n"; 
                break;
            default: 
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);
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
        outputFile.write(user.role.data(), ROLE_LENGTH);
        if (user.role == "Employee") {
            outputFile.write(user.department.data(), DEPARTMENT_LENGTH);
        }
    }

    outputFile.close();
    std::cout << "System data written to output.txt\n";
}
