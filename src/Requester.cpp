#include "Requester.h"
#include <fstream>
#include <vector>
#include <iostream>

// Global variable definition
// extern std::vector<User> users;
extern std::fstream requesterFile;

// ============================================
// Function Implementations: Product Release
// ============================================

// ---------------------------------------------------------
// Function: openRequesterFile
void openRequesterFile() {
    requesterFile.open("requestersFile.dat", std::ios::in | std::ios::out | std::ios::binary | std::ios::app);

	// Check if file opening worked properly, exit if it didn't
	if (!requesterFile.is_open()) exit(1);
}

// ---------------------------------------------------------
// Function: closeRequesterFile
void closeRequesterFile() {
    if (requesterFile.is_open()) {
        requesterFile.close();
    }
}

// ---------------------------------------------------------
// Function: writeRequester
void writeRequester(const Requester& requester) {
    if (!requesterFile.is_open()) return;

	// Get the character address of the product struct, write it a byte at a time (char),
	// writing "sizeof(Product)" amount of bytes  
	// Note: fixed-length writing as Product is a struct and attribute type fixes the struct size
	requesterFile.write(reinterpret_cast<const char*>(&requester), sizeof(Requester));

	// Check if we ran out of disk space; exit if we have
	if (!requesterFile.good()) exit(1);
}

// ---------------------------------------------------------
// Function: seekToBeginningOfRequesterFile
void seekToBeginningOfRequesterFile() {
    if (!requesterFile.is_open()) return;

	// Reset internal flags
    requesterFile.clear();

	// Set the position in the input sequence to the beginning of the file
	// Zero offest from the beginning of the file
    requesterFile.seekg(0, std::ios::beg);
}

void displayRequester(const Requester& requester) {
	std::cout << requester.reqName << 
					 ", " << requester.phoneNumber << 
					 ", " << requester.email <<
					 ", " << requester.department;
}


// For retrieving a particular product with a particular key
bool retrieveRequesterByKey(const char* filename, const char* reqName, Requester& requester) {
	Requester tmpRequester;

	seekToBeginningOfRequesterFile();

    while (requesterFile.read(reinterpret_cast<char*>(&tmpRequester), sizeof(Requester))) {
		// If in the inFile, there exists an element that matches what we hope to retrieve
        if (std::strcmp(tmpRequester.reqName, reqName) == 0) {
			
			// Store the product into the product outside of the function
			std::strcpy(requester.reqName, tmpRequester.reqName);
			std::strcpy(requester.phoneNumber, tmpRequester.phoneNumber);
			std::strcpy(requester.email, tmpRequester.email);
			std::strcpy(requester.department, tmpRequester.department);

            return true; // Product found
        }
    }
	requesterFile.clear();

    return false; // Product not found
}

// ---------------------------------------------------------
// Function: createProductRelease
void createRequester(const char* reqName,
					 const char* phoneNumber,
					 const char* email,
					 const char* department) {	// Variables
	// Create the requester
	Requester tmpReq = {};
	
	// Store input strings to their corresponding attributes
	std::strcpy(tmpReq.reqName, reqName);
	std::strcpy(tmpReq.phoneNumber, phoneNumber);
	std::strcpy(tmpReq.email, email);
	std::strcpy(tmpReq.department, department);
	
	// Write it to file
	bool requesterExists = false;

    Requester tmpReadReq;

	seekToBeginningOfRequesterFile();

    // Read each requester from the file and compare its name with the target name
    while (requesterFile.read(reinterpret_cast<char*>(&tmpReadReq), sizeof(Requester))) {
        if (std::strcmp(tmpReadReq.reqName, reqName) == 0) {
			requesterExists = true;
        }
    }
	requesterFile.clear();

	// If the requester doesn't exist, append it to the end of the file
    if (!requesterExists) {
		writeRequester(tmpReq);
	}	
}

