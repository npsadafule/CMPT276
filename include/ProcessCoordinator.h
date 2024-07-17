#ifndef PROCESSCOORDINATOR_H
#define PROCESSCOORDINATOR_H

// ============================================
// Function Declarations
// ============================================

// Confirms the addition of a product
void confirmAddingProduct();

// Asks if the user wants to add another product
void doYouWantAnotherProduct();

// Confirms the addition of a product release
void confirmAddingProdRel();

// Asks if the user wants to add another product release
void doYouWantAnotherProdRel();

// For use for A5 release
// Provides options for the requester
void requesterOptions();

// Allows the user to choose a search option
void reqSearchChoice();

// Handles product maintenance
// Parameter: choice (The user's choice for product maintenance)
void handleProductMaintenance(int choice);

// Handles change request maintenance
// Parameter: choice (The user's choice for change request maintenance)
void handleChangeRequestMaintenance(int choice);

// Handles change item maintenance
// Parameter: choice (The user's choice for change item maintenance)
void handleChangeItemMaintenance(int choice);

// Handles report generation
// Parameter: choice (The user's choice for report generation)
void handleReportGeneration(int choice);

// Displays help information
void displayHelp();



#endif // PROCESSCOORDINATOR_H
