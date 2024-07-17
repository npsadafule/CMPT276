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

// Function Declarations
// ============================================

// ---------------------------------------------------------
// Function: start
// Initializes the system and begins the user interface.
void start();

// ---------------------------------------------------------
// Function to read an integer input within a specified range
// Parameter: func (Function pointer to display the menu)
// Parameter: min (Minimum allowed input value)
// Parameter: max (Maximum allowed input value)
// Returns: int (Validated integer input within the specified range)
int readIntegerInput(MenuFuncPtr func, int min, int max) {
    int choice;

    // Prompt the user
    func();
    std::cout << "Choose an option [" << min << "-" << max << "] and press ENTER: ";

    // Read the integer input and validate
    while (!(std::cin >> choice) || choice < min || choice > max) {
        std::cin.clear(); // Clear the error flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore invalid input
        func();
        std::cout << "\nInvalid input. Please enter a number between " << min << " and " << max << ".";
        std::cout << "Choose an option [" << min << "-" << max << "] and press ENTER: ";
    }

    // Clear input buffer
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return choice;
}

// ---------------------------------------------------------
// Function: displayMainMenu
// Displays the main menu options.
void displayMainMenu() {
    std::cout << "\n====== Main Menu ======\n";
    std::cout << "1) Product Maintenance\n";
    std::cout << "2) Change Request Maintenance\n";
    std::cout << "3) Change Item Maintenance\n";
    std::cout << "4) Report Generation\n";
    std::cout << "0) Exit\n";
}

// ---------------------------------------------------------
// Function: displayProductMaintenance
// Displays the options for product maintenance.
void displayProductMaintenance() {
    std::cout << "\n====== Product Maintenance ======\n";
    std::cout << "1) Create a Product\n";
    std::cout << "2) Create a Release of a Product\n";
    std::cout << "0) Return to Main Menu\n";
}

// ---------------------------------------------------------
// Function: displayChangeRequestMaintenance
// Displays the options for change request maintenance.
void displayChangeRequestMaintenance() {
    std::cout << "\n====== Change Request Maintenance ======\n";
    std::cout << "1) Add a new change request\n";
    std::cout << "0) Go back to Main Menu\n";
}

// ---------------------------------------------------------
// Function: displayChangeItemMaintenance
// Displays the options for change item maintenance.
void displayChangeItemMaintenance() {
    std::cout << "\n====== Change Item Maintenance ======\n";
    std::cout << "1) Query Change Item to Screen\n";
    std::cout << "2) Update/Assess Change Item\n";
    std::cout << "0) Return to Main Menu\n";
}

// ---------------------------------------------------------
// Function: displayReportGeneration
// Displays the options for report generation.
void displayReportGeneration() {
    std::cout << "\n====== Report Generation ======\n";
    std::cout << "1) Generate Report #1\n";
    std::cout << "2) Generate Report #2\n";
    std::cout << "0) Return to Main Menu\n";
}

// ---------------------------------------------------------
// Function: activateUI
// Activates the user interface, allowing the user to interact with the system.
void activateUI() {
    int choice = -1;
    int subchoice = -1;
    do {
        choice = readIntegerInput(displayMainMenu, 0, 4);
        switch (choice) {
            case 1:
                subchoice = readIntegerInput(displayProductMaintenance, 0, 2);
                if (subchoice != 0) {
                    handleProductMaintenance(subchoice);
                }
                break;
            case 2:
                subchoice = readIntegerInput(displayChangeRequestMaintenance, 0, 1);
                if (subchoice != 0) {
                    handleChangeRequestMaintenance(subchoice);
                }
                break;
            case 3:
                subchoice = readIntegerInput(displayChangeItemMaintenance, 0, 2);
                if (subchoice != 0) {
                    handleChangeItemMaintenance(subchoice);
                }
                break;
            case 4:
                subchoice = readIntegerInput(displayReportGeneration, 0, 2);
                if (subchoice != 0) {
                    handleReportGeneration(subchoice);
                }
                break;
            case 0:
                shutdown();
                std::cout << "Thank you for using the Issue Tracking System.\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);
}

// End of file
