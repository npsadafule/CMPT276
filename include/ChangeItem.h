// ============================================
// Module Name: ChangeItem.h
// ============================================
// Version History:
// Rev. 2 - 2024/07/17 - Group 7
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
	char productName[PRODUCT_NAME_LENGTH]; // foreign to product
    char description[CHANGE_DESC_LENGTH];
    char anticipatedReleaseID[RELEASE_ID_LENGTH]; // foreign to product release
    char state[STATE_LENGTH]; // Options: Reported, Assessed, InProgress, Done, Cancelled
};

// ============================================
// Function Declarations
// ============================================

// ---------------------------------------------------------
// Converts an integer to a C-style string
const char* intToCString(
    // Parameter: number (The integer to convert)
    // Returns: const char* (The resulting C-style string)
    // Essentially for displaying changeIDs
    int number
); 

// ---------------------------------------------------------
// Opens the ChangeItem file
void openChangeItemFile();

// ---------------------------------------------------------
// Closes the ChangeItem file
void closeChangeItemFile();

// ---------------------------------------------------------
// Writes a ChangeItem to the file
void writeChangeItem(
    // Parameter: changeItem (The ChangeItem to write)
    const ChangeItem& changeItem    // in
);

// ---------------------------------------------------------
// Seeks to the beginning of the ChangeItem file
void seekToBeginningOfChangeItemFile();

// ---------------------------------------------------------
// Displays a ChangeItem
void displayChangeItem(
    // Parameter: changeItem (The ChangeItem to display)
    const ChangeItem& changeItem    // in
);

// ---------------------------------------------------------
// Displays the first 20 or fewer ChangeItems in the file
void changeItemFileDisplay20OrLess(
    // Parameter: filename (The name of the file to display ChangeItems from)
    const char* filename    // in
);

// ---------------------------------------------------------
// Retrieves a ChangeItem by its primary key
bool retrieveChangeItemByKey(
    // Parameter: filename (The name of the file to retrieve the ChangeItem from)
    // Parameter: changeID (The primary key of the ChangeItem)
    // Parameter: changeItem (The ChangeItem object to store the retrieved data)
    // Returns: bool (true if retrieval was successful, false otherwise)
    const char* filename,   // in
    int changeID,   // in
    ChangeItem& changeItem  // out
);

// ---------------------------------------------------------
// Creates a new ChangeItem
void createChangeItem(int changeID,
                        // Parameter: changeID (The ID of the ChangeItem)
                        // Parameter: productName (The name of the product associated with the ChangeItem)
                        // Parameter: description (The description of the ChangeItem)
                        // Parameter: anticipatedReleaseID (The anticipated release ID for the ChangeItem)
                        // Parameter: state (The state of the ChangeItem)
					  const char* productName,   // in
					  const char* description,   // in     
					  const char* anticipatedReleaseID,   // in
					  const char* state   // in
);

// ---------------------------------------------------------
// Retrieves a ChangeItem by its primary key and product
bool retrieveChangeItemByKeyAndProduct(
    // Parameter: filename (The name of the file to retrieve the ChangeItem from)
    // Parameter: changeID (The primary key of the ChangeItem)
    // Parameter: changeItem (The ChangeItem object to store the retrieved data)
    // Parameter: product (The product associated with the ChangeItem)
    // Returns: bool (true if retrieval was successful, false otherwise)
    const char* filename,   // in
    int changeID,   // in
    ChangeItem& changeItem,   // out
    char* product   // in
);

// ---------------------------------------------------------
// Updates an existing ChangeItem
bool updateChangeItem(
    // Parameter: origChangeID (The original ID of the ChangeItem)
    // Parameter: changeItem (The ChangeItem with updated information)
    // Returns: bool (true if update was successful, false otherwise)
    int origChangeID,
    ChangeItem& changeItem
);

// ---------------------------------------------------------
// Closes the file storing the highest ChangeItem ID
void closeHighestCID();

// ---------------------------------------------------------
// Seeks to the beginning of the file storing the highest ChangeItem ID
void seekToBeginningOfHighestCIDFile();

// ---------------------------------------------------------
// Stores the highest ChangeItem ID
void storeHighestCID();

#endif // CHANGEITEM_H