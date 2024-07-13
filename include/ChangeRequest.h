#ifndef CHANGEREQUEST_H
#define CHANGEREQUEST_H

#include <string>
#include "Product.h"

// ============================================
// Data structures
// ============================================
struct ChangeRequest {
    char productName[PRODUCT_NAME_LENGTH];
    std::string changeID;
    std::string description;
    std::string state;
    std::string anticipatedReleaseID;
};

// ============================================
// Function Declarations
// ============================================
void openChangeRequestFile();
void closeChangeRequestFile();
void writeChangeRequest(const ChangeRequest& changeRequest);
void seekToBeginningOfChangeRequestFile();
bool getNextChangeRequest(ChangeRequest& changeRequest);
void createChangeRequest(const std::string& profileName, const std::string& productName, const std::string& changeID, const std::string& description, const std::string& anticipatedReleaseID);
void queryChangeRequest(const std::string& productName, const std::string& changeID);
void updateChangeRequest(const std::string& productName, const std::string& changeID, const std::string& newState);

#endif // CHANGEREQUEST_H
