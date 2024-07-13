#ifndef CHANGEREQUEST_H
#define CHANGEREQUEST_H

#include <string>

// ============================================
// Data structures
// ============================================
struct ChangeRequest {
    std::string profileName;
    std::string productName; // needs to be removed
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
