#include "UserInterface.h"
#include "Product.h"
#include "ChangeRequest.h"
#include "Report.h"
#include "Requester.h"
#include "ProcessCoordinator.h"
#include "SystemController.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>
#include <cstring>

// Global variables
extern std::vector<Product> products;
// extern std::vector<User> users;
extern std::map<std::string, ChangeRequest> changeRequests;

// Static variables
typedef void (*MenuFuncPtr)();

// Function Declarations
// ============================================

// ---------------------------------------------------------
// Function: start
void start();

// ---------------------------------------------------------
// Function to read an integer input within a specified range
int readIntegerInput(int min, int max) {
    int choice;

    // Prompt the user
    std::cout << "Enter the number you want [" << min << "-" << max << "]: ";

    // Read the integer input and validate
    while (!(std::cin >> choice) || choice < min || choice > max) {
        std::cin.clear(); // Clear the error flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore invalid input
        std::cout << "Invalid input. Please enter a number between " << min << " and " << max << ".\n";
        std::cout << "Enter the number you want [" << min << "-" << max << "]: ";
    }

    // Clear input buffer
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return choice;
}

// ---------------------------------------------------------
// Function: activateUI
void activateUI() {
    int choice = -1;
    do {
      //   system("clear");
        std::cout << "\n====== Main Menu ======\n";
        std::cout << "1) Product Maintenance\n";
        std::cout << "2) Change Request Maintenance\n";
        std::cout << "3) Change Item Maintenance\n";
        std::cout << "4) Report Generation\n";
        std::cout << "0) Exit\n";
        choice = readIntegerInput(0,4);

        switch (choice) {
            case 1: 
            //     system("clear");
                std::cout << "\n====== Product Maintenance ======\n";
                std::cout << "1) Create a Product\n";
                std::cout << "2) Create a Release of a Product\n";
                std::cout << "0) Return to Main Menu\n";
                choice = readIntegerInput(0,2);
                handleProductMaintenance(choice); break;
        
            case 2: 
            //     system("clear");
                std::cout << "\n====== Change Request Maintenance ======\n";
                std::cout << "1) Add a new change request\n";
                std::cout << "0) Go back to Main Menu\n";
				choice = readIntegerInput(0,1);
                handleChangeRequestMaintenance(choice); break;
            case 3: 
            //     system("clear");
                std::cout << "\n====== Change Item Maintenance ======\n";
                std::cout << "1) Query Change Item to Screen\n";
                std::cout << "2) Update/Assess Change Item\n";
                std::cout << "0) Return to Main Menu\n";
				choice = readIntegerInput(0,2);
                handleChangeItemMaintenance(choice); break;
            case 4: 
            //     system("clear");
                std::cout << "\n====== Report Generation ======\n";
                std::cout << "1) Generate Report #1\n";
                std::cout << "2) Generate Report #2\n";
                std::cout << "0) Return to Main Menu\n";
				choice = readIntegerInput(0,2);
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
