#include "ChangeRequest.h"
#include <iostream>
#include <fstream>

// File handling functions
extern std::fstream changeRequestFile;

// ============================================
// Function Implementations
// ============================================

// ---------------------------------------------------------
// Function: openChangeRequestFile
void openChangeRequestFile() {
	// // Note: trunc is ensuring that we test with an empty file: pre-condition followed
    // requesterFile.open("requestersFile.dat", std::ios::in | std::ios::out | std::ios::binary | std::ios::app);

	// // Check if file opening worked properly, exit if it didn't
	// if (!requesterFile.is_open()) exit(1);
}

// ---------------------------------------------------------
// Function: closeChangeRequestFile
void closeChangeRequestFile() {
    // if (requesterFile.is_open()) {
    //     requesterFile.close();
    // }
}

// ---------------------------------------------------------
// Function: writeChangeRequest
void writeChangeRequest(const ChangeRequest& changeRequest) {
 	// if (!requesterFile.is_open()) return;

	// // Get the character address of the product struct, write it a byte at a time (char),
	// // writing "sizeof(Product)" amount of bytes  
	// // Note: fixed-length writing as Product is a struct and attribute type fixes the struct size
	// requesterFile.write(reinterpret_cast<const char*>(&requester), sizeof(Requester));

	// // Check if we ran out of disk space; exit if we have
	// if (!requesterFile.good()) exit(1);_cast<const char*>(&changeRequest), sizeof(ChangeRequest));
}

// ---------------------------------------------------------
// Function: seekToBeginningOfChangeRequestFile
void seekToBeginningOfChangeRequestFile() {
 	// if (!requesterFile.is_open()) return;

	// // Reset internal flags
    // requesterFile.clear();

	// // Set the position in the input sequence to the beginning of the file
	// // Zero offest from the beginning of the file
    // requesterFile.seekg(0, std::ios::beg);
}

// ---------------------------------------------------------
// Function: getNextChangeRequest
// bool getNextChangeRequest(ChangeRequest& changeRequest) {
//     if (!changeRequestFile.is_open()) return false;
//     changeRequestFile.read(reinterpret_cast<char*>(&changeRequest), sizeof(ChangeRequest));
//     return !changeRequestFile.fail();
// }

bool retrieveChangeRequestByKey(const char* filename, const char* reqName, const int changeID, ChangeRequest& changeRequest) {
	// Requester tmpRequester;

	// seekToBeginningOfRequesterFile();

	// std::ifstream inFile(filename, std::ios::binary);
    // if (!inFile) {
    //     std::cerr << "Failed to open requesters file for reading!" << std::endl;
    //     return false;
    // }

    // while (inFile.read(reinterpret_cast<char*>(&tmpRequester), sizeof(Requester))) {
	// 	// If in the inFile, there exists an element that matches what we hope to retrieve
    //     if (std::strcmp(tmpRequester.reqName, reqName) == 0) {
	// 		inFile.close();
			
	// 		// Store the product into the product outside of the function
	// 		std::strcpy(requester.reqName, tmpRequester.reqName);
	// 		std::strcpy(requester.phoneNumber, tmpRequester.phoneNumber);
	// 		std::strcpy(requester.email, tmpRequester.email);
	// 		std::strcpy(requester.department, tmpRequester.department);

    //         return true; // Product found
    //     }
    // }

	// inFile.close();
    // return false; // Product not found
}

// ---------------------------------------------------------
// Function: createChangeRequest
void createChangeRequest(const char* requesterName,
						 const int changeID,
						 const char* reportedRelease,
						 const char* reportedDate,
						 const char* priority) {
    // // Create the requester
	// Requester tmpReq = {};
	
	// // Store input strings to their corresponding attributes
	// std::strcpy(tmpReq.reqName, reqName);
	// std::strcpy(tmpReq.phoneNumber, phoneNumber);
	// std::strcpy(tmpReq.email, email);
	// std::strcpy(tmpReq.department, department);
	
	// // Write it to file
	// bool requesterExists = false;

    // Requester tmpReadReq;

	// seekToBeginningOfRequesterFile();

	// std::ifstream inFile("requestersFile.dat", std::ios::binary);
    // if (!inFile) {
    //     std::cerr << "Failed to open requester file for reading!" << std::endl;
    //     exit(1);
    // }

    // // Read each requester from the file and compare its name with the target name
    // while (inFile.read(reinterpret_cast<char*>(&tmpReadReq), sizeof(Requester))) {
    //     if (std::strcmp(tmpReadReq.reqName, reqName) == 0) {
	// 		requesterExists = true;
    //     }
    // }
	// inFile.close();
	
	// // If the requester doesn't exist, append it to the end of the file
    // if (!requesterExists) {
	// 	writeRequester(tmpReq);
	// }	
}

// ---------------------------------------------------------
// Function: queryChangeRequest
void queryChangeRequest(const std::string& productName, const std::string& changeID) {
    // ChangeRequest changeRequest;
    // openChangeRequestFile();
    // seekToBeginningOfChangeRequestFile();
    // while (getNextChangeRequest(changeRequest)) {
    //     if (changeRequest.productName == productName && changeRequest.changeID == changeID) {
    //         std::cout << "Product: " << productName << "\nDescription: " << changeRequest.description << "\nChange ID: " << changeRequest.changeID << "\nState: " << changeRequest.state << "\nAnticipated Release ID: " << changeRequest.anticipatedReleaseID << "\n";
    //         closeChangeRequestFile();
    //         return;
    //     }
    // }
    // std::cerr << "Change Request not found. Please try again.\n";
    // closeChangeRequestFile();
}


// ---------------------------------------------------------
// Function: updateChangeRequest
void updateChangeRequest(const std::string& productName, const std::string& changeID, const std::string& newState) {
    // ChangeRequest changeRequest;
    // std::fstream tempFile("temp.dat", std::ios::out | std::ios::binary);
    // openChangeRequestFile();
    // seekToBeginningOfChangeRequestFile();
    // while (getNextChangeRequest(changeRequest)) {
    //     if (changeRequest.productName == productName && changeRequest.changeID == changeID) {
    //         changeRequest.state = newState;
    //     }
    //     tempFile.write(reinterpret_cast<const char*>(&changeRequest), sizeof(ChangeRequest));
    // }
    // closeChangeRequestFile();
    // tempFile.close();
    // remove("changeRequests.dat");
    // rename("temp.dat", "changeRequests.dat");
    // std::cout << "Change Request updated successfully.\n";
}
