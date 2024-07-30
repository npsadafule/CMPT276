// ============================================
// Module Name: UserInterface.h
// ============================================
// Version History:
// Rev. 3 - 2024/07/30 - Group 7
	// Kenneth Tan: Edited comments to match Assignment 5 requirements.
// Rev. 2 - 2024/07/17 - Group 7
// Rev. 1 - 2024/07/01 - Group 7
// ============================================


#ifndef USERINTERFACE_H
#define USERINTERFACE_H

// Global function type pointers
typedef void (*MenuFuncPtr)();

// ============================================
// Function Declarations
// ============================================
// ---------------------------------------------------------
// Starts the user interface
void start();

// ---------------------------------------------------------
// Reads an integer input from the user
int readIntegerInput(
    // Parameter: func (The function to call for displaying the menu)
    // Parameter: min (The minimum acceptable value)
    // Parameter: max (The maximum acceptable value)
    // Returns: int (The user's input within the specified range)
    MenuFuncPtr func,
    int min,
    int max
);

// ---------------------------------------------------------
// Activates the user interface
void activateUI();

// ---------------------------------------------------------
// Shuts down the user interface
void shutdown();

// ---------------------------------------------------------
// Displays the main menu
void displayMainMenu();

// ---------------------------------------------------------
// Displays the product maintenance menu
void displayProductMaintenance();

// ---------------------------------------------------------
// Displays the change request maintenance menu
void displayChangeRequestMaintenance();

// ---------------------------------------------------------
// Displays the change item maintenance menu
void displayChangeItemMaintenance();

// ---------------------------------------------------------
// Displays the report generation menu
void displayReportGeneration();

#endif // USERINTERFACE_H