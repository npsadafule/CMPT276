// ============================================
// Module Name: Report.h
// ============================================
// Version History:
// Rev. 1 - 2024/07/01 - Neel Sadafule
// ============================================

#ifndef REPORT_H
#define REPORT_H

#include <string>

// ============================================
// Function Declarations
// ============================================

// ---------------------------------------------
// Function: generateReport1
// Description: Generates a report listing all change items for a product that are not done or cancelled.
// Parameters:
// - productName: The name of the product (in).
// ---------------------------------------------
void generateReport1(const std::string& productName);

// ---------------------------------------------
// Function: generateReport2
// Description: Generates a report listing customers/staff who need to be informed when a particular change has been implemented.
// Parameters:
// - changeID: The ID of the change request (in).
// ---------------------------------------------
void generateReport2(const std::string& changeID);

#endif // REPORT_H
