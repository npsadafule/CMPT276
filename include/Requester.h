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

// Opens the Requester file
void openRequesterFile();

// Closes the Requester file
void closeRequesterFile();

// Writes a Requester to the file
// Parameter: requester (The Requester to write)
void writeRequester(const Requester& requester);

// Seeks to the beginning of the Requester file
void seekToBeginningOfRequesterFile();

// Displays a Requester
// Parameter: requester (The Requester to display)
void displayRequester(const Requester& requester);

// Displays the first 20 or fewer Requesters in the file
// Parameter: page (The page number to display)
// Parameter: filename (The name of the file to display Requesters from)
// Returns: int (The number of Requesters displayed)
int requesterFileDisplay20OrLess(int page, const char* filename);

// Retrieves a Requester by its primary key
// Parameter: filename (The name of the file to retrieve the Requester from)
// Parameter: reqName (The primary key of the Requester)
// Parameter: requester (The Requester object to store the retrieved data)
// Returns: bool (true if retrieval was successful, false otherwise)
bool retrieveRequesterByKey(const char* filename, const char* reqName, Requester& requester);

// Creates a new Requester
// Parameter: reqName (The name of the Requester)
// Parameter: phoneNumber (The phone number of the Requester)
// Parameter: email (The email address of the Requester)
// Parameter: department (The department of the Requester)
void createRequester(const char* reqName,
					 const char* phoneNumber,
					 const char* email,
					 const char* department);
#endif // REQUESTER_H
