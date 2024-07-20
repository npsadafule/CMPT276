// ============================================
// Module Name: ProcessCoordinator.h
// ============================================
// Version History:
// Rev. 2 - 2024/07/17 - Group 7
// ============================================

#ifndef PROCESSCOORDINATOR_H
#define PROCESSCOORDINATOR_H

// ============================================
// Function Declarations
// ============================================

// ---------------------------------------------------------
// Confirms the addition of a product
void confirmAddingProduct();

// ---------------------------------------------------------
// Asks if the user wants to add another product
void doYouWantAnotherProduct();

// ---------------------------------------------------------
// Confirms the addition of a product release
void confirmAddingProdRel();

// ---------------------------------------------------------
// Asks if the user wants to add another product release
void doYouWantAnotherProdRel();

// ---------------------------------------------------------
// Provides options for the requester
void requesterOptions(
    // For use for A5 release
);

// ---------------------------------------------------------
// Allows the user to choose a search option
void reqSearchChoice();

// ---------------------------------------------------------
// Handles product maintenance
void handleProductMaintenance(
    // Parameter: choice (The user's choice for product maintenance)
    int choice  //in
);

// ---------------------------------------------------------
// Handles change request maintenance
void handleChangeRequestMaintenance(
    // Parameter: choice (The user's choice for change request maintenance)
    int choice  //in
);

// ---------------------------------------------------------
// Handles change item maintenance
void handleChangeItemMaintenance(
    // Parameter: choice (The user's choice for change item maintenance)
    int choice  //in
);

// ---------------------------------------------------------
// Handles report generation
void handleReportGeneration(
    // Parameter: choice (The user's choice for report generation)
    int choice  //in
);

// ---------------------------------------------------------
// Displays help information
void displayHelp();



#endif // PROCESSCOORDINATOR_H