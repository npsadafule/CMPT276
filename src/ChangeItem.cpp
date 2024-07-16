// ============================================
// Module Name: ChangeItem.cpp
// ============================================
// Version History:
// Rev. 1 - 2024/07/01 - Group 7
// ============================================

#include "ChangeItem.h"
#include "Product.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>

// Global variable definitions
extern std::vector<Product> products;
extern std::fstream changeItemFile;

// ============================================
// Function Implementations
// ============================================

const char* intToCString(int number) {
    static std::string str; // static to ensure memory is not deallocated after function exits
    str = std::to_string(number);
    return str.c_str();
}

void openChangeItemFile() {
    changeItemFile.open("changeItems.dat", std::ios::in | std::ios::out | std::ios::binary | std::ios::app);
    
	// Check if file opening worked properly, exit if it didn't
	if (!changeItemFile.is_open()) exit(1);
}


// ---------------------------------------------------------
// Function: closeProductFile
void closeChangeItemFile() {
    if (changeItemFile.is_open()) {
        changeItemFile.close();
    }
}

// ---------------------------------------------------------
// Function: writeProduct
void writeChangeItem(const ChangeItem& changeItem) {
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
    if (!changeItemFile.is_open()) return;

	// Reset internal flags
    changeItemFile.clear();

	// Set the position in the input sequence to the beginning of the file
	// Zero offest from the beginning of the file
    changeItemFile.seekg(0, std::ios::beg);
}

// For bringing up lists of products for reports
void displayChangeItem(const ChangeItem& changeItem) {
	std::cout << intToCString(changeItem.changeID) << 
				  ", " << changeItem.productName << 
				  ", " << changeItem.description << 
				  ", " << changeItem.anticipatedReleaseID <<
				  ", " << changeItem.state << std::endl;
}

void changeItemFileDisplay20OrLess(const char* filename) {
	const int MAX_READS = 20;

	ChangeItem tmpCI;

    std::ifstream inFile(filename, std::ios::binary);
    if (!inFile) {
        std::cerr << "Failed to open file for reading!" << std::endl;
        return;
    }

	int counter = 0;
    while (inFile.read(reinterpret_cast<char*>(&tmpCI), sizeof(ChangeItem)) &&
		   counter < MAX_READS) {
		displayChangeItem(tmpCI);
		counter++;
    }
}

// For retrieving a particular product with a particular name
bool retrieveChangeItemByKey(const char* filename, int changeID, ChangeItem& changeItem) {
	ChangeItem tmpChangeItem;

	seekToBeginningOfChangeItemFile();

	std::ifstream inFile(filename, std::ios::binary);
    if (!inFile) {
        std::cerr << "Failed to open file for reading!" << std::endl;
        return false;
    }

    // Read each product from the file and compare its name with the target name
    while (inFile.read(reinterpret_cast<char*>(&tmpChangeItem), sizeof(ChangeItem))) {
        if (tmpChangeItem.changeID == changeID) {
            inFile.close();
			
			// Store the product into the product outside of the function
			changeItem.changeID = tmpChangeItem.changeID;
			std::strcpy(changeItem.productName, tmpChangeItem.productName);
			std::strcpy(changeItem.description, tmpChangeItem.description);
			std::strcpy(changeItem.anticipatedReleaseID, tmpChangeItem.anticipatedReleaseID);
			std::strcpy(changeItem.state, tmpChangeItem.state);

            return true; // Product found
        }
    }

    inFile.close();
    return false; // Product not found
}

// ---------------------------------------------------------
// Function: createChangeItem
void createChangeItem(int changeID,
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
	
	std::ifstream inFile("changeItems.dat", std::ios::binary);
    if (!inFile) {
        std::cerr << "Failed to open change item file for reading!" << std::endl;
        exit(1);
    }

	while (inFile.read(reinterpret_cast<char*>(&tmpReadCI), sizeof(ChangeItem))) {
        if (tmpReadCI.changeID == tmpCI.changeID) {
			changeItemExists = true;
        }
    }
	inFile.close();

	// If the change item doesn't exist, append it to the end of the file
    if (!changeItemExists) {
		writeChangeItem(tmpCI);
	}	
}

// For retrieving a particular product with a particular name
bool retrieveChangeItemByKeyAndProduct(const char* filename, int changeID, ChangeItem& changeItem, char* product) {
	seekToBeginningOfChangeItemFile();

	std::ifstream inFile(filename, std::ios::binary);
    if (!inFile) {
        std::cerr << "Failed to open file for reading!" << std::endl;
        return false;
    }

    // Read each product from the file and compare its name with the target name
    while (inFile.read(reinterpret_cast<char*>(&changeItem), sizeof(ChangeItem))) {
        // If in the inFile, there exists an element that matches what we hope to retrieve
        if ((std::strcmp(changeItem.productName, product) == 0) &&
			(changeItem.changeID == changeID)) {
			inFile.close();
            return true; // release ID found
        }
    }
    inFile.close();
    return false; // Product not found
}

// // ---------------------------------------------------------
// // Function: queryChangeItem
// void queryChangeItem(const char* product, const int changeID) {
	
// }

// void queryChangeItem(
// const std::string& productName, // in
// const std::string& changeID // in
// ) {
// // Description:
// // Queries and displays the details of a change item for a specified
// // product. If the product
// // or the change item does not exist, it displays an error message.
// auto it = std::find_if(products.begin(), products.end(), [&](const
// 	Product& p) { return p.name == productName; });
// if (it == products.end()) {
// 	std::cerr << "Product does not exist. Please try again.\n";
// 	return;
// }

// auto itemIt = it->changeItems.find(changeID);
// if (itemIt == it->changeItems.end()) {
// 	std::cerr << "Change Item does not exist. Please try again.\n";
// 	return;
// }


// const ChangeItem& item = itemIt->second;
// std::cout << "Product: " << productName << "\nDescription: " << item.
// 	description << "\nChange ID: " << item.changeID << "\nState: " <<
// 	item.state << "\nAnticipated Release ID: " << item.
// 	anticipatedReleaseID << "\n";
// }

// ---------------------------------------------------------
// Function: updateChangeItem
// void updateChangeItem(
// 	const std::string& productName, // in
// 	const std::string& changeID, // in
// 	const std::string& newState // in
// ) {
// 	// Description:
// 	// Updates the state of a change item for a specified product. If the
// 	// product or the change
// 	// item does not exist, it displays an error message.
// 	auto it = std::find_if(products.begin(), products.end(), [&](const
// 	Product& p) { return p.name == productName; });
// 	if (it == products.end()) {
// 	std::cerr << "Product does not exist. Please try again.\n";
// 	return;
// 	}

// 	auto itemIt = it->changeItems.find(changeID);
// 	if (itemIt == it->changeItems.end()) {
// 	std::cerr << "Change Item does not exist. Please try again.\n";
// 	return;
// 	}

// 	ChangeItem& item = itemIt->second;
// 	item.state = newState;
// 	std::cout << "Change Item updated successfully.\n";
// }