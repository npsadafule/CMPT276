// ============================================
// Module Name: ChangeRequest.h
// ============================================
// Version History:
// Rev. 3 - 2024/07/30 - Group 7
	//	Kenneth Tan: Edited comments to match Assignment 5 requirements, fixed bugs and removed unused parameters.
// Rev. 2 - 2024/07/17 - Group 7
// Rev. 1 - 2024/07/01 - Group 7
// ============================================

#ifndef CHANGEREQUEST_H
#define CHANGEREQUEST_H

#include "Product.h"
#include "ChangeItem.h"
#include "Requester.h"
#include <string>

// Global constant variables
const int REP_DATE_LENGTH = 10 +1;
const int PRIORITY_LENGTH = 1 +1;

// ============================================
// Data structures
// ============================================
struct ChangeRequest {
    char requesterName[REQ_NAME_LENGTH]; // primary key, foreign
    int changeID; // primary key, foreign
    char reportedRelease[RELEASE_ID_LENGTH]; // foreign
    char reportedDate[REP_DATE_LENGTH]; // the day the request was made
    char priority[PRIORITY_LENGTH];
};

// ============================================
// Function Declarations
// ============================================
// ---------------------------------------------------------
// Opens the ChangeRequest file
void openChangeRequestFile();

// ---------------------------------------------------------
// Closes the ChangeRequest file
void closeChangeRequestFile();

// ---------------------------------------------------------
// Writes a ChangeRequest to the file
void writeChangeRequest(
    // Parameter: changeRequest (The ChangeRequest to write)
    const ChangeRequest& changeRequest  // in
);

// ---------------------------------------------------------
// Seeks to the beginning of the ChangeRequest file
void seekToBeginningOfChangeRequestFile();

// ---------------------------------------------------------
// Retrieves the next ChangeRequest from file
bool getNextChangeRequest(
    ChangeRequest& changeRequest
);

// No display functions (display functions would go here based on other modules).

// ---------------------------------------------------------
bool retrieveChangeRequestByKey(
    // Retrieves a ChangeRequest by its primary key
    // Parameter: filename (The name of the file to retrieve the ChangeRequest from)
    // Parameter: reqName (The primary key of the requester)
    // Parameter: changeID (The primary key of the ChangeItem)
    // Parameter: changeRequest (The ChangeRequest object to store the retrieved data)
    // Returns: bool (true if retrieval was successful, false otherwise)
    const char* reqName,    // in
    const int changeID,    // in
    ChangeRequest& changeRequest    // out
);

// ---------------------------------------------------------
void createChangeRequest(const char* requesterName,
                        // Creates a new ChangeRequest
                        // Parameter: requesterName (The name of the requester)
                        // Parameter: changeID (The ID of the ChangeItem)
                        // Parameter: reportedRelease (The reported release ID)
                        // Parameter: reportedDate (The date the request was reported)
                        // Parameter: priority (The priority of the request)
						 const int changeID,    // in
						 const char* reportedRelease,    // in
						 const char* reportedDate,    // in
						 const char* priority    // in
);

// ---------------------------------------------------------
void queryChangeRequest(
    // Queries a ChangeRequest
    // Parameter: productName (The name of the product)
    // Parameter: changeID (The ID of the ChangeItem)
    const std::string& productName,    // in
    const std::string& changeID    // in
);

// ---------------------------------------------------------
void updateChangeRequest(
    // Updates the state of a ChangeRequest
    // Parameter: productName (The name of the product)
    // Parameter: changeID (The ID of the ChangeItem)
    // Parameter: newState (The new state of the ChangeRequest)
    const std::string& productName,    // in
    const std::string& changeID,    // in
    const std::string& newState    // in
);

#endif // CHANGEREQUEST_H