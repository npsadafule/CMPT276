// ============================================
// Module Name: ProcessCoordinator.h
// ============================================
// Version History:
// Rev. 1 - 2024/07/01 - Group 7
// ============================================

#ifndef PROCESSCOORDINATOR_H
#define PROCESSCOORDINATOR_H

// ============================================
// Function Declarations
// ============================================

// ---------------------------------------------
// Function: handleProductMaintenance
// Description: Handles product maintenance options.
// Parameters:
// - choice: The menu choice selected by the user (in).
// ---------------------------------------------
void handleProductMaintenance(int choice);

// ---------------------------------------------
// Function: handleChangeRequestMaintenance
// Description: Handles change request maintenance options.
// Parameters:
// - choice: The menu choice selected by the user (in).
// ---------------------------------------------
void handleChangeRequestMaintenance(int choice);

// ---------------------------------------------
// Function: handleChangeItemMaintenance
// Description: Handles change item maintenance options.
// Parameters:
// - choice: The menu choice selected by the user (in).
// ---------------------------------------------
void handleChangeItemMaintenance(int choice);

// ---------------------------------------------
// Function: handleReportGeneration
// Description: Handles report generation options.
// Parameters:
// - choice: The menu choice selected by the user (in).
// ---------------------------------------------
void handleReportGeneration(int choice);

// ---------------------------------------------
// Function: displayHelp
// Description: Displays help information.
// ---------------------------------------------
void displayHelp();

#endif // PROCESSCOORDINATOR_H
