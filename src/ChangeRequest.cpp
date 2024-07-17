#include "ChangeRequest.h"
#include <iostream>
#include <fstream>
#include <cstring>

// File handling functions
extern std::fstream changeRequestFile;

// ============================================
// Function Implementations
// ============================================

// ---------------------------------------------------------
// Function: openChangeRequestFile
void openChangeRequestFile() {
    changeRequestFile.open("changeRequests.dat", std::ios::in | std::ios::out | std::ios::binary | std::ios::app);

    // Check if file opening worked properly, exit if it didn't
    if (!changeRequestFile.is_open()) exit(1);
}

// ---------------------------------------------------------
// Function: closeChangeRequestFile
void closeChangeRequestFile() {
    if (changeRequestFile.is_open()) {
        changeRequestFile.close();
    }
}

// ---------------------------------------------------------
// Function: writeChangeRequest
void writeChangeRequest(const ChangeRequest& changeRequest) {
    if (!changeRequestFile.is_open()) return;

    // Get the character address of the product struct, write it a byte at a time (char),
    // writing "sizeof(Product)" amount of bytes  
    // Note: fixed-length writing as Product is a struct and attribute type fixes the struct size
    changeRequestFile.write(reinterpret_cast<const char*>(&changeRequest), sizeof(ChangeRequest));

    // Check if we ran out of disk space; exit if we have
    if (!changeRequestFile.good()) exit(1);
}

// ---------------------------------------------------------
// Function: seekToBeginningOfChangeRequestFile
void seekToBeginningOfChangeRequestFile() {
    if (!changeRequestFile.is_open()) return;

    // Reset internal flags
    changeRequestFile.clear();

    // Set the position in the input sequence to the beginning of the file
    // Zero offest from the beginning of the file
    changeRequestFile.seekg(0, std::ios::beg);
}

// ---------------------------------------------------------
// Function: getNextChangeRequest
bool getNextChangeRequest(ChangeRequest& changeRequest) {
    if (!changeRequestFile.is_open()) return false;
    changeRequestFile.read(reinterpret_cast<char*>(&changeRequest), sizeof(ChangeRequest));
    return !changeRequestFile.fail();
}

// ---------------------------------------------------------
// Function: retrieveChangeRequestByKey
bool retrieveChangeRequestByKey(const char* filename, const char* reqName, const int changeID, ChangeRequest& changeRequest) {
    ChangeRequest tmpCR;

    seekToBeginningOfChangeRequestFile();

    while (changeRequestFile.read(reinterpret_cast<char*>(&tmpCR), sizeof(ChangeRequest))) {
        // If in the inFile, there exists an element that matches what we hope to retrieve
        if ((std::strcmp(tmpCR.requesterName, reqName) == 0) && (tmpCR.changeID == changeID)) {

            // Store the change request into the change request outside of the function
            std::strcpy(changeRequest.requesterName, tmpCR.requesterName);
            changeRequest.changeID = tmpCR.changeID;
            std::strcpy(changeRequest.reportedRelease, tmpCR.reportedRelease);
            std::strcpy(changeRequest.reportedDate, tmpCR.reportedDate);
            std::strcpy(changeRequest.priority, tmpCR.priority);

            return true; // Change request found
        }
    }
	changeRequestFile.clear();

    return false; // Product not found
}

// ---------------------------------------------------------
// Function: createChangeRequest
void createChangeRequest(const char* requesterName,
                         const int changeID,
                         const char* reportedRelease,
                         const char* reportedDate,
                         const char* priority) {
    // Create the change request
    ChangeRequest tmpCR = {};

    // Store input strings to their corresponding attributes
    std::strcpy(tmpCR.requesterName, requesterName);
    tmpCR.changeID = changeID;
    std::strcpy(tmpCR.reportedRelease, reportedRelease);
    std::strcpy(tmpCR.reportedDate, reportedDate);
    std::strcpy(tmpCR.priority, priority);

    // Write it to file
    bool CRExists = false;

    ChangeRequest tmpReadCR;

    seekToBeginningOfChangeRequestFile();

    // Read each requester from the file and compare its name with the target name
    while (changeRequestFile.read(reinterpret_cast<char*>(&tmpReadCR), sizeof(ChangeRequest))) {
        if ((std::strcmp(tmpReadCR.requesterName, requesterName) == 0) && (tmpReadCR.changeID == changeID)) {
            CRExists = true;
        }
    }
    changeRequestFile.clear();

    // If the requester doesn't exist, append it to the end of the file
    if (!CRExists) {
        writeChangeRequest(tmpCR);
    }    
}

// ---------------------------------------------------------
// Function: queryChangeRequest
void queryChangeRequest(const std::string& requesterName, const int changeID) {
    ChangeRequest changeRequest;
    openChangeRequestFile();
    seekToBeginningOfChangeRequestFile();
    while (getNextChangeRequest(changeRequest)) {
        if (std::strcmp(changeRequest.requesterName, requesterName.c_str()) == 0 && changeRequest.changeID == changeID) {
            std::cout << "Requester Name: " << changeRequest.requesterName
                      << "\nChange ID: " << changeRequest.changeID
                      << "\nReported Release: " << changeRequest.reportedRelease
                      << "\nReported Date: " << changeRequest.reportedDate
                      << "\nPriority: " << changeRequest.priority << std::endl;
            closeChangeRequestFile();
            return;
        }
    }
    std::cerr << "Change Request not found. Please try again.\n";
    closeChangeRequestFile();
}

// ---------------------------------------------------------
// Function: updateChangeRequest
void updateChangeRequest(const std::string& requesterName, const int changeID, const std::string& newPriority) {
    ChangeRequest changeRequest;
    std::fstream tempFile("temp.dat", std::ios::out | std::ios::binary);
    openChangeRequestFile();
    seekToBeginningOfChangeRequestFile();
    bool found = false;

    while (getNextChangeRequest(changeRequest)) {
        if (std::strcmp(changeRequest.requesterName, requesterName.c_str()) == 0 && changeRequest.changeID == changeID) {
            std::strcpy(changeRequest.priority, newPriority.c_str());
            found = true;
        }
        tempFile.write(reinterpret_cast<const char*>(&changeRequest), sizeof(ChangeRequest));
    }
    
    closeChangeRequestFile();
    tempFile.close();
    
    remove("changeRequests.dat");
    rename("temp.dat", "changeRequests.dat");

    if (found) {
        std::cout << "Change Request updated successfully.\n";
    } else {
        std::cerr << "Change Request not found. Please try again.\n";
    }
}
