#ifndef USERINTERFACE_H
#define USERINTERFACE_H

// Global function type pointers
typedef void (*MenuFuncPtr)();

// ============================================
// Function Declarations
// ============================================
void start();
int readIntegerInput(MenuFuncPtr func, int min, int max);
void activateUI();
void shutdown();
void displayMainMenu();
void displayProductMaintenance();
void displayChangeRequestMaintenance();
void displayChangeItemMaintenance();
void displayReportGeneration();

#endif // USERINTERFACE_H
