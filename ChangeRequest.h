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

// ---------------------------------------------
// Function: createChangeRequest
// Description: Creates a new change request for an existing product.
// Parameters:
// - profileName: The name of the user profile (in).
// - productName: The name of the product (in).
// - changeID: The ID of the change request (in).
// - description: Description of the change request (in).
// - anticipatedReleaseID: The anticipated release ID (in).
// ---------------------------------------------
void createChangeRequest(const std::string& profileName, const std::string& productName, const std::string& changeID, const std::string& description, const std::string& anticipatedReleaseID);

// ---------------------------------------------
// Function: queryChangeItem
// Description: Queries and displays the details of a change item.
// Parameters:
// - productName: The name of the product (in).
// - changeID: The ID of the change request (in).
// ---------------------------------------------
void queryChangeItem(const std::string& productName, const std::string& changeID);

// ---------------------------------------------
// Function: updateChangeItem
// Description: Updates the state of a change item.
// Parameters:
// - productName: The name of the product (in).
// - changeID: The ID of the change request (in).
// - newState: The new state of the change request (in).
// ---------------------------------------------
void updateChangeItem(const std::string& productName, const std::string& changeID, const std::string& newState);

#endif // CHANGEREQUEST_H
