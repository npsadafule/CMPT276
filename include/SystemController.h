// ============================================
// Module Name: SystemController.h
// ============================================
// Version History:
// Rev. 1 - 2024/07/01 - Neel Sadafule
// ============================================

#ifndef SYSTEMCONTROLLER_H
#define SYSTEMCONTROLLER_H

#include <vector>
#include <map>
#include "Product.h"
#include "User.h"

// Extern declarations for global variables
extern std::vector<Product> products;
extern std::vector<User> users;
extern std::map<std::string, std::string> changeRequests;

// ============================================
// Function Declarations
// ============================================

// ---------------------------------------------
// Function: initProduct
// Description: Initializes the product module.
// ---------------------------------------------
void initProduct();

// ---------------------------------------------
// Function: initChangeRequest
// Description: Initializes the change request module.
// ---------------------------------------------
void initChangeRequest();

// ---------------------------------------------
// Function: initChangeItem
// Description: Initializes the change item module.
// ---------------------------------------------
void initChangeItem();

// ---------------------------------------------
// Function: initReportGen
// Description: Initializes the report generation module.
// ---------------------------------------------
void initReportGen();

// ---------------------------------------------
// Function: start
// Description: Initializes the application by reading data from files.
// ---------------------------------------------
void start();

#endif // SYSTEMCONTROLLER_H
