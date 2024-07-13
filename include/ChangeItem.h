// ============================================
// Module Name: ChangeItem.h
// ============================================
// Version History:
// Rev. 1 - 2024/07/01 - Group 7
// ============================================

#ifndef CHANGEITEM_H
#define CHANGEITEM_H

#include <cstring>
#include "Product.h"

// Global constant definitions
const int CHANGE_DESC_LENGTH = 150 +1;
const int CHANGE_ID_LENGTH = 6 +1;
const int STATE_LENGTH = 10 +1;


// ============================================
// Data structures
// ============================================
struct ChangeItem {
 	char productName[PRODUCT_NAME_LENGTH];
    char changeID[CHANGE_ID_LENGTH];
    char description[CHANGE_DESC_LENGTH];
    char state[STATE_LENGTH];
    char anticipatedReleaseID[RELEASE_ID_LENGTH];
};

// ============================================
// Function Declarations
// ============================================

// ---------------------------------------------------------
// Function: queryChangeItem
// void queryChangeItem(
// const std::string& productName, // in
// const std::string& changeID // in

// );

// ---------------------------------------------------------
// Function: updateChangeItem
// void updateChangeItem(
// const std::string& productName, // in
// const std::string& changeID, // in
// const std::string& newState // in
// );

#endif // CHANGEITEM_H