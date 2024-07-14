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
void initRequester(std::fstream& requesterFile);
void initProduct(std::fstream& productFile, std::fstream& productReleaseFile);
void initChangeRequest();
void initChangeItem(std::fstream& changeItemFile);
void initReportGen();
void start();

#endif // SYSTEMCONTROLLER_H
