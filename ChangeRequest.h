#ifndef CHANGEREQUEST_H
#define CHANGEREQUEST_H

#include <string>
#include <map>
#include "Product.h"

// ============================================
// Module Name: ChangeRequest.h
// ============================================

// Version History:
// Rev. 1 - 2024/07/01 - Neel Sadafule

// Function Declarations
// ============================================

/**
 * @brief Creates a new change request.
 * 
 * @param profileName Name of the user profile.
 * @param productName Name of the product.
 * @param changeID Unique identifier for the change request.
 * @param description Description of the change request.
 * @param anticipatedReleaseID Anticipated release ID for the change request.
 */
void createChangeRequest(const std::string& profileName, const std::string& productName, const std::string& changeID, const std::string& description, const std::string& anticipatedReleaseID);

/**
 * @brief Queries a change item and displays its details.
 * 
 * @param productName Name of the product.
 * @param changeID Unique identifier for the change item.
 */
void queryChangeItem(const std::string& productName, const std::string& changeID);

/**
 * @brief Updates the state of a change item.
 * 
 * @param productName Name of the product.
 * @param changeID Unique identifier for the change item.
 * @param newState New state to be set for the change item.
 */
void updateChangeItem(const std::string& productName, const std::string& changeID, const std::string& newState);

#endif // CHANGEREQUEST_H
