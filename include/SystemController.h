#ifndef SYSTEMCONTROLLER_H
#define SYSTEMCONTROLLER_H

#include <vector>
#include <map>
#include "Product.h"
#include "Requester.h"
#include "ChangeRequest.h"

// Extern declarations for global variables
extern std::vector<Product> products;
// extern std::vector<User> users;
extern std::map<std::string, ChangeRequest> changeRequests;

// ============================================
// Function Declarations
// ============================================

// Initializes the Requester module
void initRequester();


// Initializes the Product module
void initProduct();

// Initializes the ChangeRequest module
void initChangeRequest();

// Initializes the ChangeItem module
void initChangeItem();

// Initializes the Report generation module
void initReportGen();

// Initializes the Highest ChangeID module
void initHighestCID();

// Starts the system controller
void start();

// Shuts down the system controller
void shutdown();

#endif // SYSTEMCONTROLLER_H
