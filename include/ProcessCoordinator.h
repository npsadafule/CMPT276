#ifndef PROCESSCOORDINATOR_H
#define PROCESSCOORDINATOR_H

// ============================================
// Function Declarations
// ============================================
void confirmAddingProduct();
void doYouWantAnotherProduct();

void confirmAddingProdRel();
void doYouWantAnotherProdRel();

void handleProductMaintenance(int choice);
void handleChangeRequestMaintenance(int choice);
void handleChangeItemMaintenance(int choice);
void handleReportGeneration(int choice);
void displayHelp();



#endif // PROCESSCOORDINATOR_H
