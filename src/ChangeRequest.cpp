#include "ChangeRequest.h"
#include <iostream>
#include <fstream>

// File handling functions
std::fstream changeRequestFile;

// ============================================
// Function Implementations
// ============================================

// ---------------------------------------------------------
// Function: openChangeRequestFile
void openChangeRequestFile() {
    changeRequestFile.open("changeRequests.dat", std::ios::in | std::ios::out | std::ios::binary);
    if (!changeRequestFile.is_open()) {
        std::cerr << "Failed to open changeRequests.dat file.\n";
    }
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
    changeRequestFile.write(reinterpret_cast<const char*>(&changeRequest), sizeof(ChangeRequest));
}

// ---------------------------------------------------------
// Function: seekToBeginningOfChangeRequestFile
void seekToBeginningOfChangeRequestFile() {
    if (!changeRequestFile.is_open()) return;
    changeRequestFile.clear();
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
// Function: createChangeRequest
void createChangeRequest(const std::string& profileName, const std::string& productName, const std::string& changeID, const std::string& description, const std::string& anticipatedReleaseID) {
    ChangeRequest changeRequest = {profileName, productName, changeID, description, "Reported", anticipatedReleaseID};
    openChangeRequestFile();
    seekToBeginningOfChangeRequestFile();
    writeChangeRequest(changeRequest);
    closeChangeRequestFile();
    std::cout << "Change Request ID is " << changeID << ". The Change Request was successfully added.\n";
}

// ---------------------------------------------------------
// Function: queryChangeRequest
void queryChangeRequest(const std::string& productName, const std::string& changeID) {
    ChangeRequest changeRequest;
    openChangeRequestFile();
    seekToBeginningOfChangeRequestFile();
    while (getNextChangeRequest(changeRequest)) {
        if (changeRequest.productName == productName && changeRequest.changeID == changeID) {
            std::cout << "Product: " << productName << "\nDescription: " << changeRequest.description << "\nChange ID: " << changeRequest.changeID << "\nState: " << changeRequest.state << "\nAnticipated Release ID: " << changeRequest.anticipatedReleaseID << "\n";
            closeChangeRequestFile();
            return;
        }
    }
    std::cerr << "Change Request not found. Please try again.\n";
    closeChangeRequestFile();
}


// ---------------------------------------------------------
// Function: updateChangeRequest
void updateChangeRequest(const std::string& productName, const std::string& changeID, const std::string& newState) {
    ChangeRequest changeRequest;
    std::fstream tempFile("temp.dat", std::ios::out | std::ios::binary);
    openChangeRequestFile();
    seekToBeginningOfChangeRequestFile();
    while (getNextChangeRequest(changeRequest)) {
        if (changeRequest.productName == productName && changeRequest.changeID == changeID) {
            changeRequest.state = newState;
        }
        tempFile.write(reinterpret_cast<const char*>(&changeRequest), sizeof(ChangeRequest));
    }
    closeChangeRequestFile();
    tempFile.close();
    remove("changeRequests.dat");
    rename("temp.dat", "changeRequests.dat");
    std::cout << "Change Request updated successfully.\n";
}
