#ifndef REPORT_H
#define REPORT_H

#include <string>
#include "Product.h"

// ============================================
// Module Name: Report.h
// ============================================

// Version History:
// Rev. 1 - 2024/07/01 - Neel Sadafule

// Function Declarations
// ============================================

/**
 * @brief Generates Report #1.
 * 
 * @param productName Name of the product for which the report is generated.
 */
void generateReport1(const std::string& productName);

/**
 * @brief Generates Report #2.
 * 
 * @param changeID Change ID for which the report is generated.
 */
void generateReport2(const std::string& changeID);

#endif // REPORT_H
