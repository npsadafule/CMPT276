// ============================================
// Module Name: Requester.h
// ============================================
// Version History:
// Rev. 1 - 2024/07/17 - Group 7
// ============================================

#ifndef REQUESTER_H
#define REQUESTER_H

#include <string>

// Global constnats
// Note: based on A3 (not A2)
const int REQ_NAME_LENGTH = 30 +1;
const int PHONE_NUMBER_LENGTH = 10 +1; // Just storing numbers
const int EMAIL_LENGTH = 24 +1;
const int DEPARTMENT_LENGTH = 12 +1;

// ============================================
// Data structures
// ============================================
struct Requester {
    char reqName[REQ_NAME_LENGTH]; // primary key
    char phoneNumber[PHONE_NUMBER_LENGTH]; // customer enters only the numbers
    char email[EMAIL_LENGTH];
    char department[DEPARTMENT_LENGTH]; // rolled-up
};

// ============================================
// Function Declarations: Product Release
// ============================================

// ---------------------------------------------------------
// Opens the Requester file
void openRequesterFile();

// ---------------------------------------------------------
// Closes the Requester file
void closeRequesterFile();

// ---------------------------------------------------------
// Writes a Requester to the file
void writeRequester(
    // Parameter: requester (The Requester to write)
    const Requester& requester  // in
);

// ---------------------------------------------------------
// Seeks to the beginning of the Requester file
void seekToBeginningOfRequesterFile();  // in

// ---------------------------------------------------------
// Displays a Requester
void displayRequester(
    // Parameter: requester (The Requester to display)
    const Requester& requester  // in
);

// ---------------------------------------------------------
// Displays the first 20 or fewer Requesters in the file
int requesterFileDisplay20OrLess(
    // Parameter: page (The page number to display)
    // Parameter: filename (The name of the file to display Requesters from)
    // Returns: int (The number of Requesters displayed)
    int page,
    const char* filename  // in
);

// ---------------------------------------------------------
bool retrieveRequesterByKey(
    // Retrieves a Requester by its primary key
    // Parameter: filename (The name of the file to retrieve the Requester from)
    // Parameter: reqName (The primary key of the Requester)
    // Parameter: requester (The Requester object to store the retrieved data)
    // Returns: bool (true if retrieval was successful, false otherwise)
    const char* filename,  // in
    const char* reqName,  // in
    Requester& requester  // out
);

// ---------------------------------------------------------
// Creates a new Requester
// Parameter: reqName (The name of the Requester)
// Parameter: phoneNumber (The phone number of the Requester)
// Parameter: email (The email address of the Requester)
// Parameter: department (The department of the Requester)
void createRequester(const char* reqName,  // in
					 const char* phoneNumber,  // in
					 const char* email,  // in
					 const char* department);  // in
#endif // REQUESTER_H