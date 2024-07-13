// ============================================
// Module Name: ChangeItem.h
// ============================================
// Version History:
// Rev. 1 - 2024/07/01 - Group 7
// ============================================

#ifndef CHANGEITEM_H
#define CHANGEITEM_H

#include <cstring>
#include "Product.h"

// Global constant definitions
const int CHANGE_DESC_LENGTH = 150 +1;
const int STATE_LENGTH = 10 +1;

// ============================================
// Data structures
// ============================================
struct ChangeItem {
 	int changeID; // 6 digits, the primary key
	char productName[PRODUCT_NAME_LENGTH];
    char description[CHANGE_DESC_LENGTH];
    char anticipatedReleaseID[RELEASE_ID_LENGTH];
    char state[STATE_LENGTH]; // Options: Reported, Assessed, InProgress, Done, Cancelled
};

// ============================================
// Function Declarations
// ============================================

const char* intToCString(int number); // Essentially for displaying changeIDs
void openChangeItemFile();
void closeChangeItemFile();
void writeChangeItem(const ChangeItem& changeItem);
void seekToBeginningOfChangeItemFile();
// bool getNextChangeItem(const ChangeItem& changeItem);
void displayChangeItem(const ChangeItem& changeItem);
void changeItemFileDisplay20OrLess(const char* filename);
bool retrieveChangeItemByKey(const char* filename, int changeID, ChangeItem& changeItem);
void createChangeItem(int changeID,
					  const char* productName,
					  const char* description,
					  const char* anticipatedReleaseID,
					  const char* state);
// ---------------------------------------------------------
// Function: queryChangeItem
// void queryChangeItem(
// const std::string& productName, // in
// const std::string& changeID // in

// );

// ---------------------------------------------------------
// Function: updateChangeItem
// void updateChangeItem(
// const std::string& productName, // in
// const std::string& changeID, // in
// const std::string& newState // in
// );

#endif // CHANGEITEM_H