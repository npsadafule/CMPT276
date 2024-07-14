#ifndef USER_H
#define USER_H

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
void openRequesterFile();
void closeRequesterFile();
void writeRequester(const Requester& requester);
void seekToBeginningOfRequesterFile();
void displayRequester(const Requester& requester);
void requesterFileDisplay20OrLess(const char* filename);
bool retrieveRequesterByKey(const char* filename, const char* reqName, Requester& requester);
void createRequester(const char* reqName,
					 const char* phoneNumber,
					 const char* email,
					 const char* department);
#endif // USER_H
