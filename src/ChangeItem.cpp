// ============================================
// Module Name: ChangeItem.cpp
// ============================================
// Version History:
// Rev. 2 - 2024/07/17 - Group 7
// ============================================

// Overall internal design issues:
// This module implements ChangeItems. So, it uses the "ChangeItem" struct, imported from ChangeItem.h (see it for detailed list of attributes). It uses linear search to find products within files based on a criteria of attributes (e.g., primary key (single or compound)).

// Memory/Speed/Complexity Trade-offs: 
// Memory use is optimized by handling file I/O operations directly, which can be slower but avoids loading large data sets into memory.
// Representation Choices: Using fixed-size structs to handle ChangeItem data for predictable file I/O operations.
// Alternatives: Could use dynamic memory allocation for more flexible data handling, but with added complexity and potential memory leaks.

#include "ChangeItem.h"
#include "Product.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <cstring>

// Global variable exertns
extern std::vector<Product> products;
extern std::fstream changeItemFile;
extern std::fstream highestCIDFile;

// ============================================
// Function Implementations
// ============================================
// ---------------------------------------------------------
const char* intToCString(int number) {
    // Converts an integer to a C-style string
    static std::string str; // static to ensure memory is not deallocated after function exits
    str = std::to_string(number);
    return str.c_str();
}

// ---------------------------------------------------------
void openChangeItemFile() {
    // Opens the change item file
    // Exits the program if the file cannot be opened
    changeItemFile.open("changeItems.dat", std::ios::in | std::ios::out | std::ios::binary | std::ios::app);
    
	// Check if file opening worked properly, exit if it didn't
	if (!changeItemFile.is_open()) exit(1);
}


// ---------------------------------------------------------
// Function: closeProductFile
void closeChangeItemFile() {
    // Closes the change item file if it is open
    if (changeItemFile.is_open()) {
        changeItemFile.close();
    }
}

// ---------------------------------------------------------
// Function: writeProduct
void writeChangeItem(const ChangeItem& changeItem) {
    // Writes a change item to the change item file
    // Parameter: changeItem (The change item to write)
    if (!changeItemFile.is_open()) return;

	// Get the character address of the product struct, write it a byte at a time (char),
	// writing "sizeof(Product)" amount of bytes  
	// Note: fixed-length writing as Product is a struct and attribute type fixes the struct size
    changeItemFile.write(reinterpret_cast<const char*>(&changeItem), sizeof(ChangeItem));

	// Check if we ran out of disk space; exit if we have
	if (!changeItemFile.good()) exit(1);
}

// ---------------------------------------------------------
// Function: seekToBeginningOfProductFile
void seekToBeginningOfChangeItemFile() {
    // Sets the file position to the beginning of the change item file
    if (!changeItemFile.is_open()) return;

	// Reset internal flags
    changeItemFile.clear();

	// Set the position in the input sequence to the beginning of the file
	// Zero offest from the beginning of the file
    changeItemFile.seekg(0, std::ios::beg);
}

// ---------------------------------------------------------
void displayChangeItem(const ChangeItem& changeItem) {
    // For bringing up lists of products for reports
    // Displays a change item
    // Parameter: changeItem (The change item to display)
	std::cout << intToCString(changeItem.changeID) << 
				  ", " << changeItem.productName << 
				  ", " << changeItem.description << 
				  ", " << changeItem.anticipatedReleaseID <<
				  ", " << changeItem.state << std::endl;
}

// ---------------------------------------------------------
void changeItemFileDisplay20OrLess(const char* filename) {
    // Displays up to 20 change items from a file
    // Parameter: filename (The name of the file to read change items from)
    const int MAX_READS = 20;

	ChangeItem tmpCI;

	int counter = 0;
    // Loop by the size of ChangeItem and while the loop counter is less than MAX_READS to display change items
    while (changeItemFile.read(reinterpret_cast<char*>(&tmpCI), sizeof(ChangeItem)) &&
		   counter < MAX_READS) {
		displayChangeItem(tmpCI);
		counter++;
    }
	changeItemFile.clear();
}

// ---------------------------------------------------------
bool retrieveChangeItemByKey(const char* filename, int changeID, ChangeItem& changeItem) {
    // For retrieving a particular product with a particular name
    // Retrieves a change item by its ID
    // Parameter: filename (The name of the file to read change items from)
    // Parameter: changeID (The ID of the change item to retrieve)
    // Parameter: changeItem (The change item object to store the retrieved data)
    // Returns: bool (true if retrieval was successful, false otherwise)
	ChangeItem tmpChangeItem;

	seekToBeginningOfChangeItemFile();

    // Read each product from the file and compare its name with the target name
    while (changeItemFile.read(reinterpret_cast<char*>(&tmpChangeItem), sizeof(ChangeItem))) {
        if (tmpChangeItem.changeID == changeID) {
			
			// Store the product into the product outside of the function
			changeItem.changeID = tmpChangeItem.changeID;
			std::strcpy(changeItem.productName, tmpChangeItem.productName);
			std::strcpy(changeItem.description, tmpChangeItem.description);
			std::strcpy(changeItem.anticipatedReleaseID, tmpChangeItem.anticipatedReleaseID);
			std::strcpy(changeItem.state, tmpChangeItem.state);

            return true; // Product found
        }
    }
	changeItemFile.clear();

    return false; // Product not found
}

// ---------------------------------------------------------
// Function: createChangeItem
void createChangeItem(int changeID,
    // Creates a new change item
    // Parameter: changeID (The ID of the change item)
    // Parameter: productName (The name of the product associated with the change item)
    // Parameter: description (The description of the change item)
    // Parameter: anticipatedReleaseID (The anticipated release ID for the change item)
    // Parameter: state (The state of the change item)
					  const char* productName,
					  const char* description,
					  const char* anticipatedReleaseID,
					  const char* state) { 
	// Create a temp change item to be written
    ChangeItem tmpCI = {};
	
	// // Store the attributes into tmpCI's fields
	tmpCI.changeID = changeID;
	std::strcpy(tmpCI.productName, productName);
	std::strcpy(tmpCI.description, description);
	std::strcpy(tmpCI.anticipatedReleaseID, anticipatedReleaseID);
	std::strcpy(tmpCI.state, state);

	// //std::cout << "createProduct: the product we received was named " << product.name << std::endl;

	// Check if the product is on the file
	bool changeItemExists = false;

	ChangeItem tmpReadCI;

	seekToBeginningOfChangeItemFile();

        // Loop forward by the size of change items to retrieve all records on file
	while (changeItemFile.read(reinterpret_cast<char*>(&tmpReadCI), sizeof(ChangeItem))) {
        if (tmpReadCI.changeID == tmpCI.changeID) {
			changeItemExists = true;
        }
    }
	changeItemFile.clear();

	// If the change item doesn't exist, append it to the end of the file
    if (!changeItemExists) {
		writeChangeItem(tmpCI);
	}	

	// Update highest CID on file if neede
	storeHighestCID();
}

// ---------------------------------------------------------
bool retrieveChangeItemByKeyAndProduct(const char* filename, int changeID, ChangeItem& changeItem, char* product) {
    // For retrieving a particular product with a particular name
    // Retrieves a change item by its ID and product name
    // Parameter: filename (The name of the file to read change items from)
    // Parameter: changeID (The ID of the change item to retrieve)
    // Parameter: changeItem (The change item object to store the retrieved data)
    // Parameter: product (The name of the product)
    // Returns: bool (true if retrieval was successful, false otherwise)
	seekToBeginningOfChangeItemFile();

    // Read each product from the file and compare its name with the target name
    while (changeItemFile.read(reinterpret_cast<char*>(&changeItem), sizeof(ChangeItem))) {
        // If in the changeItemFile, there exists an element that matches what we hope to retrieve
        if ((std::strcmp(changeItem.productName, product) == 0) &&
			(changeItem.changeID == changeID)) {
			
            return true; // release ID found
        }
    }
    changeItemFile.clear();
    return false; // Product not found
}

// ---------------------------------------------------------
bool updateChangeItem(int origChangeID, ChangeItem& changeItem) {
    // Updates an existing change item
    // Parameter: origChangeID (The original change ID of the change item to update)
    // Parameter: changeItem (The updated change item data)
    // Returns: bool (true if update was successful, false otherwise)
	// For reading
	ChangeItem readCI;

	seekToBeginningOfChangeItemFile();

    // Find the position of the change item in the file
    while (changeItemFile.read(reinterpret_cast<char*>(&readCI), sizeof(ChangeItem))) {
        if (readCI.changeID == origChangeID) {
			std::streampos position = changeItemFile.tellg(); // Get current position

			// Move the changeItemFile pointer back to the beginning of the found item
			changeItemFile.seekp(position - std::streamoff(sizeof(ChangeItem)));

			// Write the updated ChangeItem back to the changeItemFile
			changeItemFile.write(reinterpret_cast<const char*>(&changeItem), sizeof(ChangeItem));

			// Validate what we inserted
			changeItemFile.seekp(position - std::streamoff(sizeof(ChangeItem)));
			changeItemFile.read(reinterpret_cast<char*>(&readCI), sizeof(ChangeItem));

			// Check if write was successful
			if (!changeItemFile) {
				std::cerr << "Failed to write updated ChangeItem!" << std::endl;
				changeItemFile.close();
				return false;
			}			
        }
    }
	changeItemFile.clear();

	// Update highest CID on file if needed
	storeHighestCID();

	// Write was successful
	return true;
}

// ---------------------------------------------------------
void closeHighestCID() {
    // Closes the highest change ID file if it is open
	if (highestCIDFile.is_open()) {
        highestCIDFile.close();
    }
}

// ---------------------------------------------------------
// Function: seekToBeginningOfProductFile
void seekToBeginningOfHighestCIDFile() {
    // Sets the file position to the beginning of the highest change ID file
    if (!highestCIDFile.is_open()) return;

	// Reset internal flags
    highestCIDFile.clear();

	// Set the position in the input sequence to the beginning of the file
	// Zero offest from the beginning of the file
    highestCIDFile.seekg(0, std::ios::beg);
}

// ---------------------------------------------------------
void storeHighestCID() {
    // Stores the highest change ID in a separate file
	// For reading
	ChangeItem readCI;
	ChangeItem highestCID;
	highestCID.changeID = -1; // -1 if no change item (i.e., no change IDs) exist on file

	seekToBeginningOfChangeItemFile();
	seekToBeginningOfHighestCIDFile();

    // Find the position of the change item in the file
    while (changeItemFile.read(reinterpret_cast<char*>(&readCI), sizeof(ChangeItem))) {
        // Store the highest 
		if (readCI.changeID > highestCID.changeID) {	
			highestCID.changeID = readCI.changeID;
        }
    }
	changeItemFile.clear();

	// Store highest CID
	highestCIDFile.write(reinterpret_cast<const char*>(&highestCID), sizeof(ChangeItem));

	// // Print the highest CID. (For testing).
	// std::cout << "The highest Change ID is " << std::to_string(highestCID.changeID) << std::endl;

}