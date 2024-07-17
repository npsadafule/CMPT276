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

// Opens the ChangeRequest file
void openChangeRequestFile();


// Closes the ChangeRequest file
void closeChangeRequestFile();

// Writes a ChangeRequest to the file
// Parameter: changeRequest (The ChangeRequest to write)
void writeChangeRequest(const ChangeRequest& changeRequest);

// Seeks to the beginning of the ChangeRequest file
void seekToBeginningOfChangeRequestFile();

// ---------------------------------------------------------
// Function: getNextChangeRequest
// Retrieves the next change request from the file
// Parameter: changeRequest (The change request object to store the retrieved data)
// Returns: bool (true if retrieval was successful, false otherwise)
bool getNextChangeRequest(ChangeRequest& changeRequest);

// Retrieves a ChangeRequest by its primary key
// Parameter: filename (The name of the file to retrieve the ChangeRequest from)
// Parameter: reqName (The primary key of the requester)
// Parameter: changeID (The primary key of the ChangeItem)
// Parameter: changeRequest (The ChangeRequest object to store the retrieved data)
// Returns: bool (true if retrieval was successful, false otherwise)
bool retrieveChangeRequestByKey(const char* filename, const char* reqName, const int changeID, ChangeRequest& changeRequest);

// Creates a new ChangeRequest
// Parameter: requesterName (The name of the requester)
// Parameter: changeID (The ID of the ChangeItem)
// Parameter: reportedRelease (The reported release ID)
// Parameter: reportedDate (The date the request was reported)
// Parameter: priority (The priority of the request)
void createChangeRequest(const char* requesterName,
						 const int changeID,
						 const char* reportedRelease,
						 const char* reportedDate,
						 const char* priority);

// For case scenarios NOT DONE
// Queries a ChangeRequest
// Parameter: productName (The name of the product)
// Parameter: changeID (The ID of the ChangeItem)
void queryChangeRequest(const std::string& productName, const std::string& changeID);

// Updates the state of a ChangeRequest
// Parameter: productName (The name of the product)
// Parameter: changeID (The ID of the ChangeItem)
// Parameter: newState (The new state of the ChangeRequest)
void updateChangeRequest(const std::string& productName, const std::string& changeID, const std::string& newState);

#endif // CHANGEREQUEST_H
