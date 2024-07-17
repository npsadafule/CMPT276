#ifndef USERINTERFACE_H
#define USERINTERFACE_H

// Global function type pointers
typedef void (*MenuFuncPtr)();

// ============================================
// Function Declarations
// ============================================

// Starts the user interface
void start();

// Reads an integer input from the user
// Parameter: func (The function to call for displaying the menu)
// Parameter: min (The minimum acceptable value)
// Parameter: max (The maximum acceptable value)
// Returns: int (The user's input within the specified range)
int readIntegerInput(MenuFuncPtr func, int min, int max);

// Activates the user interface
void activateUI();

// Shuts down the user interface
void shutdown();

// Displays the main menu
void displayMainMenu();

// Displays the product maintenance menu
void displayProductMaintenance();

// Displays the change request maintenance menu
void displayChangeRequestMaintenance();

// Displays the change item maintenance menu
void displayChangeItemMaintenance();

// Displays the report generation menu
void displayReportGeneration();

#endif // USERINTERFACE_H
