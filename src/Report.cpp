// ============================================
// Module Name: Report.cpp
// ============================================
// Version History:
// Rev. 2 - 2024/07/17 - Group 7
// ============================================

#include "Report.h"
#include "Product.h"
#include "Requester.h"
#include "ChangeRequest.h"
#include "ChangeItem.h"
#include <iostream>
#include <fstream>

// Global file handling functions
std::fstream reportFile;
extern std::fstream changeItemFile;
extern std::fstream requesterFile;
extern std::fstream changeRequestFile;

// ============================================
// Function Implementations
// ============================================


// ---------------------------------------------------------
// Function: openReportFile
void openReportFile() {
    // Opens the report file for reading and writing in binary mode
    // Prints an error message to standard error if the file fails to open
    reportFile.open("reports.dat", std::ios::in | std::ios::out | std::ios::binary);
    if (!reportFile.is_open()) {
        std::cerr << "Failed to open reports.dat file.\n";
    }
}

// ---------------------------------------------------------
// Function: closeReportFile
void closeReportFile() {
    // Closes the report file if it is open
    if (reportFile.is_open()) {
        reportFile.close();
    }
}

// ---------------------------------------------------------
// Function: writeReport
void writeReport(const Report& report) {
    // Writes a Report object to the report file
    // Returns immediately if the file is not open
    if (!reportFile.is_open()) return;
    reportFile.write(reinterpret_cast<const char*>(&report), sizeof(Report));
}

// ---------------------------------------------------------
// Function: seekToBeginningOfReportFile
void seekToBeginningOfReportFile() {
    // Seeks to the beginning of the report file
    // Returns immediately if the file is not open
    if (!reportFile.is_open()) return;
    reportFile.clear();
    reportFile.seekg(0, std::ios::beg);
}

// ---------------------------------------------------------
// Function: getNextReport
bool getNextReport(Report& report) {
    // Reads the next Report object from the report file
    // Returns true if the read operation is successful, false otherwise
    // Returns false immediately if the file is not open
    if (!reportFile.is_open()) return false;
    return reportFile.read(reinterpret_cast<char*>(&report), sizeof(Report)).good();
}

// ---------------------------------------------------------
// Function: generateReport1
void generateReport1(const std::string& productName) {
    // Generates a report listing all change items for a specific product that are not done and not cancelled
    // Prints the report to standard output
    ChangeItem changeItem;
    openChangeItemFile();
    seekToBeginningOfChangeItemFile();
    
    std::cout << "Report #1: List of All Change Items for " << productName << " that are Not Done and Not Cancelled\n";
    bool found = false;
    while (changeItemFile.read(reinterpret_cast<char*>(&changeItem), sizeof(ChangeItem))) {
        if (std::strcmp(changeItem.productName, productName.c_str()) == 0 &&
            std::strcmp(changeItem.state, "Done") != 0 && 
            std::strcmp(changeItem.state, "Cancelled") != 0) {
            std::cout << "ID: " << changeItem.changeID 
                      << ", Description: " << changeItem.description 
                      << ", State: " << changeItem.state 
                      << ", Anticipated Release ID: " << changeItem.anticipatedReleaseID << "\n";
            found = true;
        }
    }
    if (!found) {
        std::cerr << "No matching change items found for product: " << productName << ".\n";
    }
    closeChangeItemFile();
}

// ---------------------------------------------------------
// Function: generateReport2
void generateReport2(const std::string& changeID) {
    // Generates a report listing customers/staff who need to be informed when a particular change has been implemented
    // Prints the report to standard output
    ChangeItem changeItem;
    Requester requester;
    ChangeRequest changeRequest;
    bool changeItemFound = false;
    bool changeRequestFound = false;
    bool requesterFound = false;

    openChangeItemFile();
    if (!changeItemFile.is_open()) {
        std::cerr << "Failed to open changeItemFile.\n";
        return;
    }
    seekToBeginningOfChangeItemFile();

    // Search for the ChangeItem with the specified changeID
    while (changeItemFile.read(reinterpret_cast<char*>(&changeItem), sizeof(ChangeItem))) {
        if (std::to_string(changeItem.changeID) == changeID) {
            changeItemFound = true;
            break;
        }
    }
    closeChangeItemFile();

    if (!changeItemFound) {
        std::cerr << "ChangeItem with ChangeID " << changeID << " not found.\n";
        return;
    }

    std::cout << "Found ChangeItem: ID=" << changeItem.changeID << ", Description=" << changeItem.description << "\n";

    openChangeRequestFile();
    if (!changeRequestFile.is_open()) {
        std::cerr << "Failed to open changeRequestFile.\n";
        return;
    }
    seekToBeginningOfChangeRequestFile();

    std::vector<std::string> requesterNames;
    // Search forward by the size of ChangeRequests for a change request that has the specified change ID
    while (changeRequestFile.read(reinterpret_cast<char*>(&changeRequest), sizeof(ChangeRequest))) {
        if (changeRequest.changeID == std::stoi(changeID)) {
            changeRequestFound = true;
            requesterNames.push_back(changeRequest.requesterName);
        }
    }
    closeChangeRequestFile();

    if (!changeRequestFound) {
        std::cerr << "No change request found for ChangeItem with ChangeID " << changeID << ".\n";
        return;
    }

    openRequesterFile();
    if (!requesterFile.is_open()) {
        std::cerr << "Failed to open requesterFile.\n";
        return;
    }
    seekToBeginningOfRequesterFile();

    std::vector<Requester> relatedRequesters;
    while (requesterFile.read(reinterpret_cast<char*>(&requester), sizeof(Requester))) {
        // Loop forward by the size of requesters to check whether that requester matches the selected change ID
        for (const auto& name : requesterNames) {   // 
            if (std::strcmp(requester.reqName, name.c_str()) == 0) {
                relatedRequesters.push_back(requester);
                requesterFound = true;
            }
        }
    }
    closeRequesterFile();

    if (!requesterFound) {
        std::cerr << "No requesters found for ChangeItem with ChangeID " << changeID << ".\n";
        return;
    }

    // Generate the report
    std::cout << "Report #2: List of Customers/Staff Who Need to Be Informed When a Particular Change Has Been Implemented\n";
    // Loop forward by the size of requesters inside the relatedRequesters vector to display the names and emails of requesters
    for (const auto& req : relatedRequesters) {
        std::cout << "Name: " << req.reqName << ", Email: " << req.email << "\n";
    }
}