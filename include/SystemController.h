#ifndef SYSTEMCONTROLLER_H
#define SYSTEMCONTROLLER_H

#include <vector>
#include <map>
#include "Product.h"
#include "User.h"
#include "ChangeRequest.h"

// Extern declarations for global variables
extern std::vector<Product> products;
extern std::vector<User> users;
extern std::map<std::string, ChangeRequest> changeRequests;

// ============================================
// Function Declarations
// ============================================
void initProduct();
void initChangeRequest();
void initChangeItem();
void initReportGen();
void start();

#endif // SYSTEMCONTROLLER_H
