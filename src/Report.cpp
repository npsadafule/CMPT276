#include "Report.h"
#include "Product.h"
#include "Requester.h"
#include "ChangeRequest.h"
#include "ChangeItem.h"
#include <iostream>
#include <fstream>

// File handling functions
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
    reportFile.open("reports.dat", std::ios::in | std::ios::out | std::ios::binary);
    if (!reportFile.is_open()) {
        std::cerr << "Failed to open reports.dat file.\n";
    }
}

// ---------------------------------------------------------
// Function: closeReportFile
void closeReportFile() {
    if (reportFile.is_open()) {
        reportFile.close();
    }
}

// ---------------------------------------------------------
// Function: writeReport
void writeReport(const Report& report) {
    if (!reportFile.is_open()) return;
    reportFile.write(reinterpret_cast<const char*>(&report), sizeof(Report));
}

// ---------------------------------------------------------
// Function: seekToBeginningOfReportFile
void seekToBeginningOfReportFile() {
    if (!reportFile.is_open()) return;
    reportFile.clear();
    reportFile.seekg(0, std::ios::beg);
}

// ---------------------------------------------------------
// Function: getNextReport
bool getNextReport(Report& report) {
    if (!reportFile.is_open()) return false;
    return reportFile.read(reinterpret_cast<char*>(&report), sizeof(Report)).good();
}

// ---------------------------------------------------------
// Function: generateReport1
void generateReport1(const std::string& productName) {
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
        for (const auto& name : requesterNames) {
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
    for (const auto& req : relatedRequesters) {
        std::cout << "Name: " << req.reqName << ", Email: " << req.email << "\n";
    }
}