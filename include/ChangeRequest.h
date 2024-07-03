// ============================================
// Module Name: ChangeRequest.h
// ============================================
// Version History:
// Rev. 1 - 2024/07/01 - Neel Sadafule
// ============================================

#ifndef CHANGEREQUEST_H
#define CHANGEREQUEST_H

#include <string>

// ============================================
// Function Declarations
// ============================================

// ---------------------------------------------------------
// Function: createChangeRequest
void createChangeRequest(
    const std::string& profileName,        // in
    const std::string& productName,        // in
    const std::string& changeID,           // in
    const std::string& description,        // in
    const std::string& anticipatedReleaseID // in
);

// ---------------------------------------------------------
// Function: queryChangeItem
void queryChangeItem(
    const std::string& productName,    // in
    const std::string& changeID        // in
);

// ---------------------------------------------------------
// Function: updateChangeItem
void updateChangeItem(
    const std::string& productName,    // in
    const std::string& changeID,       // in
    const std::string& newState        // in
);

#endif // CHANGEREQUEST_H
