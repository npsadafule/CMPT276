#ifndef CHANGEREQUEST_H
#define CHANGEREQUEST_H

#include "Product.h"
#include "ChangeItem.h"
#include "Requester.h"
#include <string>

// Global constant variables
const int REP_DATE_LENGTH = 10 +1;
const int PRIORITY_LENGTH =  10 +1; // TBD

// ============================================
// Data structures
// ============================================
struct ChangeRequest {
    char requesterName[REQ_NAME_LENGTH]; // primary key, foreign
    int changeID; // primary key, foreign
    char reportedRelease[RELEASE_ID_LENGTH]; // foreign
    char reportedDate[REP_DATE_LENGTH]; // the day the request was made
    char priority[PRIORITY_LENGTH]; // TBD how it will be used
};

// ============================================
// Function Declarations
// ============================================
void openChangeRequestFile();
void closeChangeRequestFile();
void writeChangeRequest(const ChangeRequest& changeRequest);
void seekToBeginningOfChangeRequestFile();
// bool getNextChangeRequest(ChangeRequest& changeRequest);
// No display functions (display functions would go here based on other modules).
bool retrieveChangeRequestByKey(const char* filename, const char* reqName, const int changeID, ChangeRequest& changeRequest);
void createChangeRequest(const char* requesterName,
						 const int changeID,
						 const char* reportedRelease,
						 const char* reportedDate,
						 const char* priority);

void queryChangeRequest(const std::string& productName, const std::string& changeID);
void updateChangeRequest(const std::string& productName, const std::string& changeID, const std::string& newState);

#endif // CHANGEREQUEST_H
