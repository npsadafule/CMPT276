// ============================================
// Module Name: Requester.cpp
// ============================================
// Version History:
// Rev. 1 - 2024/07/17 - Group 7
// ============================================
// ---------------------------------------------------------
// Overall internal design issues:
// This module implements Requesters. So, it uses the "Requester" struct, imported from ChangeItem.h (see it for detailed list of attributes). It uses linear search to find products within files based on a criteria of attributes (e.g., primary key (single or compound)).

#include "Requester.h"
#include <fstream>
#include <vector>
#include <iostream>

// Global variable definition
int reqPages;
// extern std::vector<User> users;
extern std::fstream requesterFile;

// ============================================
// Function Implementations: Product Release
// ============================================


// ---------------------------------------------------------
// Function: openRequesterFile
void openRequesterFile() {
    // Opens the requester file in binary mode for reading, writing, and appending.
    // Exits the program if the file fails to open.
    requesterFile.open("requestersFile.dat", std::ios::in | std::ios::out | std::ios::binary | std::ios::app);

	// Check if file opening worked properly, exit if it didn't
	if (!requesterFile.is_open()) exit(1);
}

// ---------------------------------------------------------
// Function: closeRequesterFile
void closeRequesterFile() {
    // Closes the requester file if it is open.
    if (requesterFile.is_open()) {
        requesterFile.close();
    }
}

// ---------------------------------------------------------
// Function: writeRequester
void writeRequester(const Requester& requester) {
    // Writes a Requester object to the requester file.
    // Exits the program if the file encounters an error during writing.
    if (!requesterFile.is_open()) return;

	// Get the character address of the product struct, write it a byte at a time (char),
	// writing "sizeof(Product)" amount of bytes  
	// Note: fixed-length writing as Product is a struct and attribute type fixes the struct size
	requesterFile.write(reinterpret_cast<const char*>(&requester), sizeof(Requester));
	requesterFile.flush();

	// Check if we ran out of disk space; exit if we have
	if (!requesterFile.good()) exit(1);
}

// ---------------------------------------------------------
// Function: seekToBeginningOfRequesterFile
void seekToBeginningOfRequesterFile() {
    // Sets the file pointer to the beginning of the requester file.
    if (!requesterFile.is_open()) return;

	// Reset internal flags
    requesterFile.clear();

	// Set the position in the input sequence to the beginning of the file
	// Zero offest from the beginning of the file
    requesterFile.seekg(0, std::ios::beg);
}
// ---------------------------------------------------------
// Function: displayRequester
void displayRequester(const Requester& requester) {
    // Displays the details of a Requester object to the standard output.
	std::cout << requester.reqName << std::endl;
}

// ---------------------------------------------------------
// Function: requesterFileDisplay20OrLess
int requesterFileDisplay20OrLess(int& page) {
    // Displays up to 20 Requester objects from the specified page of the requester file.
    // Returns the number of Requesters displayed or -1 if the file cannot be opened.
    // Parameter: page (The page number to display)
    // Parameter: filename (The name of the requester file)
	const int ITEMS_PER_PAGE = 20;
	int error = -1; // Set to 1 if no previous pages exist; set to 2 if no next pages exist

	Requester tmpReq;

	// Find the total number of items on file
	seekToBeginningOfRequesterFile();
	int counter = 0;
	while (requesterFile.read(reinterpret_cast<char*>(&tmpReq), sizeof(Requester))) {
		counter++;
	}	
	requesterFile.clear();
	// std::cout << "total entries " << std::to_string(counter) << std::endl;

	// Calculate the total number of pages
	reqPages = (counter + ITEMS_PER_PAGE-1) / ITEMS_PER_PAGE;
	// std::cout << "total pages " << std::to_string(reqPages) << std::endl;

	// Determine if the provided page is valid
	if ((page < 1) || (page > reqPages)) {
		if (page < 1) {
			page++;
			error = 1;
		} else {
			page--;
			error = 2;
		}
	} 

	// Display the selected page
	// Loop forward by the number of pages on the file so that the next read is the
	// desired page
	seekToBeginningOfRequesterFile();
	requesterFile.seekp((page-1)*ITEMS_PER_PAGE*sizeof(Requester),std::ios::cur);
	// std::cout << "end of getting to page" << std::endl;

	// Print the page
	int pageRecordsCount = 0;
	while (requesterFile.read(reinterpret_cast<char*>(&tmpReq), sizeof(Requester)) && 
		  (pageRecordsCount < ITEMS_PER_PAGE)) {
		std::cout << std::to_string(pageRecordsCount+1) << ") ";
		displayRequester(tmpReq);
		pageRecordsCount++;
	}
	requesterFile.clear();
	// std::cout << "end of printing page" << std::endl;

	// Print any errors
	if (error == 1) {
		std::cout << "No previous pages exist!" << std::endl;
	} else if (error == 2) {
		std::cout << "No next pages exist!" << std::endl;
	}
	
	return pageRecordsCount;
}

// ---------------------------------------------------------
// Function: retrieveRequesterByKey
bool retrieveRequesterByKey(const char* filename, const char* reqName, Requester& requester) {
    // Retrieves a Requester object from the requester file by matching reqName.
    // Returns true and stores the retrieved Requester in 'requester' if found; otherwise, returns false.
    // Parameter: filename (The name of the requester file)
    // Parameter: reqName (The name of the Requester to retrieve)
    // Parameter: requester (The Requester object to store the retrieved data)
	Requester tmpRequester;

	seekToBeginningOfRequesterFile();

    while (requesterFile.read(reinterpret_cast<char*>(&tmpRequester), sizeof(Requester))) {
		// If in the requesterFile, there exists an element that matches what we hope to retrieve
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
// Function: createRequester
void createRequester(const char* reqName,
    // Creates a new Requester object with the provided details and writes it to the requester file if it doesn't already exist.
    // Parameter: reqName (The name of the Requester)
    // Parameter: phoneNumber (The phone number of the Requester)
    // Parameter: email (The email address of the Requester)
    // Parameter: department (The department of the Requester)
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