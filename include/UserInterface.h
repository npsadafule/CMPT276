#ifndef USERINTERFACE_H
#define USERINTERFACE_H

// ============================================
// Function Declarations
// ============================================
void start();
int readIntegerInput(int min, int max);
void activateUI();
void shutdown();
void displayMainMenu();
void displayProductMaintenance();
void displayChangeRequestMaintenance();
void displayChangeItemMaintenance();
void displayReportGeneration();

#endif // USERINTERFACE_H
