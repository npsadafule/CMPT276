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
// Opens the requester file in binary mode for reading, writing, and appending.
// Exits the program if the file fails to open.
void openRequesterFile() {
    requesterFile.open("requestersFile.dat", std::ios::in | std::ios::out | std::ios::binary | std::ios::app);

	// Check if file opening worked properly, exit if it didn't
	if (!requesterFile.is_open()) exit(1);
}

// ---------------------------------------------------------
// Function: closeRequesterFile
// Closes the requester file if it is open.
void closeRequesterFile() {
    if (requesterFile.is_open()) {
        requesterFile.close();
    }
}

// ---------------------------------------------------------
// Function: writeRequester
// Writes a Requester object to the requester file.
// Exits the program if the file encounters an error during writing.
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
// Sets the file pointer to the beginning of the requester file.
void seekToBeginningOfRequesterFile() {
    if (!requesterFile.is_open()) return;

	// Reset internal flags
    requesterFile.clear();

	// Set the position in the input sequence to the beginning of the file
	// Zero offest from the beginning of the file
    requesterFile.seekg(0, std::ios::beg);
}
// ---------------------------------------------------------
// Function: displayRequester
// Displays the details of a Requester object to the standard output.
void displayRequester(const Requester& requester) {
	std::cout << requester.reqName << 
					 ", " << requester.phoneNumber << 
					 ", " << requester.email <<
					 ", " << requester.department;
}

// ---------------------------------------------------------
// Function: requesterFileDisplay20OrLess
// Displays up to 20 Requester objects from the specified page of the requester file.
// Returns the number of Requesters displayed or -1 if the file cannot be opened.
// Parameter: page (The page number to display)
// Parameter: filename (The name of the requester file)
int requesterFileDisplay20OrLess(int page, const char* filename) {
	const int MAX_READS = 20;

	Requester tmpReq;

    std::ifstream inFile(filename, std::ios::binary);
    if (!inFile) {
        std::cerr << "Failed to open requesters file for reading!" << std::endl;
        return -1;
    }

	// Get to the page
	for (int i=0; i<page-1; i++)
	{		
		// Read 20 items
		int counter = 0;
		while (inFile.read(reinterpret_cast<char*>(&tmpReq), sizeof(Requester)) &&
			counter < MAX_READS) {
			counter++;
		}
	}

	// Print the page if valid
	if (inFile.fail()) {
		inFile.clear();
		std::cout << "The page you requested does not exist!" << std::endl;
		return -1;
	}
	else {
		int counter = 0;
		while (inFile.read(reinterpret_cast<char*>(&tmpReq), sizeof(Requester)) &&
			counter < MAX_READS) {
			std::cout << std::to_string(counter+1) << ") ";
			displayRequester(tmpReq);
			std::cout << std::endl;
			counter++;
		}
		return counter;
	}
}

// ---------------------------------------------------------
// Function: retrieveRequesterByKey
// Retrieves a Requester object from the requester file by matching reqName.
// Returns true and stores the retrieved Requester in 'requester' if found; otherwise, returns false.
// Parameter: filename (The name of the requester file)
// Parameter: reqName (The name of the Requester to retrieve)
// Parameter: requester (The Requester object to store the retrieved data)
bool retrieveRequesterByKey(const char* filename, const char* reqName, Requester& requester) {
	Requester tmpRequester;

	seekToBeginningOfRequesterFile();

	std::ifstream inFile(filename, std::ios::binary);
    if (!inFile) {
        std::cerr << "Failed to open requesters file for reading!" << std::endl;
        return false;
    }

    while (inFile.read(reinterpret_cast<char*>(&tmpRequester), sizeof(Requester))) {
		// If in the inFile, there exists an element that matches what we hope to retrieve
        if (std::strcmp(tmpRequester.reqName, reqName) == 0) {
			inFile.close();
			
			// Store the product into the product outside of the function
			std::strcpy(requester.reqName, tmpRequester.reqName);
			std::strcpy(requester.phoneNumber, tmpRequester.phoneNumber);
			std::strcpy(requester.email, tmpRequester.email);
			std::strcpy(requester.department, tmpRequester.department);

            return true; // Product found
        }
    }

	inFile.close();
    return false; // Product not found
}

// ---------------------------------------------------------
// Function: createRequester
// Creates a new Requester object with the provided details and writes it to the requester file if it doesn't already exist.
// Parameter: reqName (The name of the Requester)
// Parameter: phoneNumber (The phone number of the Requester)
// Parameter: email (The email address of the Requester)
// Parameter: department (The department of the Requester)
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

	std::ifstream inFile("requestersFile.dat", std::ios::binary);
    if (!inFile) {
        std::cerr << "Failed to open requester file for reading!" << std::endl;
        exit(1);
    }

    // Read each requester from the file and compare its name with the target name
    while (inFile.read(reinterpret_cast<char*>(&tmpReadReq), sizeof(Requester))) {
        if (std::strcmp(tmpReadReq.reqName, reqName) == 0) {
			requesterExists = true;
        }
    }
	inFile.close();
	
	// If the requester doesn't exist, append it to the end of the file
    if (!requesterExists) {
		writeRequester(tmpReq);
	}	
}

