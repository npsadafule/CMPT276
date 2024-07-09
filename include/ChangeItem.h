// ============================================
// Module Name: ChangeItem.h
// ============================================
// Version History:
// Rev. 1 - 2024/07/01 - Group 7
// ============================================

#ifndef CHANGEITEM_H
#define CHANGEITEM_H

#include <string>

// ============================================
// Data structures
// ============================================
struct ChangeItem {
    std::string description;
    std::string changeID;
    std::string state;
    std::string anticipatedReleaseID;
};

// ============================================
// Function Declarations
// ============================================

// ---------------------------------------------------------
// Function: queryChangeItem
void queryChangeItem(
const std::string& productName, // in
const std::string& changeID // in

);

// ---------------------------------------------------------
// Function: updateChangeItem
void updateChangeItem(
const std::string& productName, // in
const std::string& changeID, // in
const std::string& newState // in
);

#endif // CHANGEITEM_H