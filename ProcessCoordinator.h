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
// Function: startMainMenu
// Description: Starts the main menu loop.
// ---------------------------------------------

void handleProductMaintenance(int choice);
void handleChangeRequestMaintenance(int choice);
void handleChangeItemMaintenance(int choice);
void handleReportGeneration(int choice);
void displayHelp();

#endif