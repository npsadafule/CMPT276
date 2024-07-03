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

// ---------------------------------------------------------
// Function: initProduct
void initProduct();

// ---------------------------------------------------------
// Function: initChangeRequest
void initChangeRequest();

// ---------------------------------------------------------
// Function: initChangeItem
void initChangeItem();

// ---------------------------------------------------------
// Function: initReportGen
void initReportGen();

// ---------------------------------------------------------
// Function: start
void start();

#endif // SYSTEMCONTROLLER_H
