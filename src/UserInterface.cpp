// ============================================
// Module Name: UserInterface.cpp
// ============================================
// Version History:
// Rev. 3 - 2024/07/30 - Group 7
	// Kenneth Tan: Edited comments to match Assignment 5 requirements.
// Rev. 2 - 2024/07/17 - Group 7
// Rev. 1 - 2024/07/01 - Group 7
// ============================================

// Overall internal design issues:
// This module implements UserInterface.h, following our central control design from our 
// Architectural Design Document. Specifically, it handles all menu selection to start 
// execution of a user command or to shutdown ITS. Switch cases are used to handle different 
// layers of menus (i.e., menu, submenu) and do-while loops are used freqeuntly to ensure 
// proper user input.

#include "UserInterface.h"
#include "ProcessCoordinator.h"
#include "SystemController.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>
#include <cstring>

// Function Declarations
// ============================================
// ---------------------------------------------------------
// Function: start
void start(
	// Initializes the system and begins the user interface.
);

// ---------------------------------------------------------
int readIntegerInput(MenuFuncPtr func, int min, int max) {
    // Function to read an integer input within a specified range
    // Parameter: func (Function pointer to display the menu)
    // Parameter: min (Minimum allowed input value)
    // Parameter: max (Maximum allowed input value)
    // Returns: int (Validated integer input within the specified range)
    int choice;

    // Prompt the user
    func();
    std::cout << "Choose an option [" << min << "-" << max << "] and press ENTER: ";

    // Read the integer input and validate
    while (!(std::cin >> choice) || choice < min || choice > max) {
        std::cin.clear(); // Clear the error flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore invalid input
        std::cout << "Invalid input. Please enter a number between " << min << " and " << max << ".\n";
        func();
        std::cout << "Choose an option [" << min << "-" << max << "] and press ENTER: ";
    }

    // Clear input buffer
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return choice;
}

// ---------------------------------------------------------
// Function: displayMainMenu
void displayMainMenu() {
    // Displays the main menu options.  
    std::cout << "\n====== Main Menu ======\n";
    std::cout << "1) Product Maintenance\n";
    std::cout << "2) Change Request Maintenance\n";
    std::cout << "3) Change Item Maintenance\n";
    std::cout << "4) Report Generation\n";
    std::cout << "0) Exit\n";
}

// ---------------------------------------------------------
// Function: displayProductMaintenance
void displayProductMaintenance() {
    // Displays the options for product maintenance.
    std::cout << "\n====== Product Maintenance ======\n";
    std::cout << "1) Create a Product\n";
    std::cout << "2) Create a Release of a Product\n";
    std::cout << "0) Return to Main Menu\n";
}

// ---------------------------------------------------------
// Function: displayChangeRequestMaintenance
void displayChangeRequestMaintenance() {
    // Displays the options for change request maintenance.
    std::cout << "\n====== Change Request Maintenance ======\n";
    std::cout << "1) Add a new change request\n";
    std::cout << "0) Go back to Main Menu\n";
}

// ---------------------------------------------------------
// Function: displayChangeItemMaintenance
void displayChangeItemMaintenance() {
    // Displays the options for change item maintenance.
    std::cout << "\n====== Change Item Maintenance ======\n";
    std::cout << "1) Query Change Item to Screen\n";
    std::cout << "2) Update/Assess Change Item\n";
    std::cout << "0) Return to Main Menu\n";
}

// ---------------------------------------------------------
// Function: displayReportGeneration
void displayReportGeneration() {
    // Displays the options for report generation.
    std::cout << "\n====== Report Generation ======\n";
    std::cout << "1) Generate Report #1:\n"
				 "List of All Change Items for a Particular Product that are Not Done and Not Cancelled\n";
    std::cout << "2) Generate Report #2\n"
				 "List of Customers/Staff Who Need to Be Informed When a Particular Change Has\n"
				 "Been Implemented, and in What ProductRelease ID\n";
    std::cout << "0) Return to Main Menu\n";
}

// ---------------------------------------------------------
// Function: activateUI
void activateUI() {
    // Activates the user interface, allowing the user to interact with the system.
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