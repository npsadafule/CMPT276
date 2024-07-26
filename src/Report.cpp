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
// Opens the report file for reading and writing in binary mode
// Prints an error message to standard error if the file fails to open
void openReportFile() {
    reportFile.open("reports.dat", std::ios::in | std::ios::out | std::ios::binary);
    if (!reportFile.is_open()) {
        std::cerr << "Failed to open reports.dat file.\n";
    }
}

// ---------------------------------------------------------
// Function: closeReportFile
// Closes the report file if it is open
void closeReportFile() {
    if (reportFile.is_open()) {
        reportFile.close();
    }
}

// ---------------------------------------------------------
// Function: writeReport
// Writes a Report object to the report file
// Returns immediately if the file is not open
void writeReport(const Report& report) {
    if (!reportFile.is_open()) return;
    reportFile.write(reinterpret_cast<const char*>(&report), sizeof(Report));
}

// ---------------------------------------------------------
// Function: seekToBeginningOfReportFile
// Seeks to the beginning of the report file
// Returns immediately if the file is not open
void seekToBeginningOfReportFile() {
    if (!reportFile.is_open()) return;
    reportFile.clear();
    reportFile.seekg(0, std::ios::beg);
}

// ---------------------------------------------------------
// Function: getNextReport
// Reads the next Report object from the report file
// Returns true if the read operation is successful, false otherwise
// Returns false immediately if the file is not open
bool getNextReport(Report& report) {
    if (!reportFile.is_open()) return false;
    return reportFile.read(reinterpret_cast<char*>(&report), sizeof(Report)).good();
}

// ---------------------------------------------------------
// Function: generateReport1
// Generates a report listing all change items for a specific product that are not done and not cancelled
// Prints the report to standard output
void generateReport1(const std::string& productName) {
    ChangeItem changeItem;
    seekToBeginningOfChangeItemFile();
    
    std::cout << "Report #1: List of All Change Items for " << productName << " that are Not Done and Not Cancelled\n";
    bool found = false;
    while (changeItemFile.read(reinterpret_cast<char*>(&changeItem), sizeof(ChangeItem))) {
        if ((std::strcmp(changeItem.productName, productName.c_str()) == 0) &&
            (std::strcmp(changeItem.state, "Done") != 0) && 
            (std::strcmp(changeItem.state, "Cancelled") != 0)) {
            std::cout << "Change ID: " << changeItem.changeID 
					  << ", Product name: " << changeItem.productName
                      << ", Description: " << changeItem.description 
                      << ", State: " << changeItem.state 
                      << ", Anticipated Release ID: " << changeItem.anticipatedReleaseID << "\n";
            found = true;
        }
    }
	changeItemFile.clear();
    if (!found) {
        std::cerr << "No matching change items found for product: " << productName << ".\n";
    }
}

// ---------------------------------------------------------
// Function: generateReport2
// Generates a report listing customers/staff who need to be informed when a particular change has been implemented
// Prints the report to standard output
void generateReport2(const std::string& changeID, const std::string& newReleaseID) {
    ChangeItem changeItem;
    Requester requester;
    ChangeRequest changeRequest;
    bool changeItemFound = false;
    bool changeRequestFound = false;
    bool requesterFound = false;

    // Search for the ChangeItem with the specified changeID
    seekToBeginningOfChangeItemFile();
    while (changeItemFile.read(reinterpret_cast<char*>(&changeItem), sizeof(ChangeItem))) {
        if (std::to_string(changeItem.changeID) == changeID) {
            changeItemFound = true;
            break;
        }
    }
    changeItemFile.clear();
    if (!changeItemFound) {
        std::cerr << "ChangeItem with ChangeID " << changeID << " not found.\n";
        return;
    }

    // Update the anticipated release ID of the change item
    std::strcpy(changeItem.anticipatedReleaseID, newReleaseID.c_str());
    if (!updateChangeItem(changeItem.changeID, changeItem)) {
        std::cerr << "Failed to update ChangeItem with ChangeID " << changeID << ".\n";
        return;
    }

	// Find the matching change request
    seekToBeginningOfChangeRequestFile();
    std::vector<std::string> requesterNames;
    while (changeRequestFile.read(reinterpret_cast<char*>(&changeRequest), sizeof(ChangeRequest))) {
        if (changeRequest.changeID == std::stoi(changeID)) {
            changeRequestFound = true;
            requesterNames.push_back(changeRequest.requesterName);
        }
    }
    changeRequestFile.clear();
    if (!changeRequestFound) {
        std::cerr << "No change request found for ChangeItem with ChangeID " << changeID << ".\n";
        return;
    }

    seekToBeginningOfRequesterFile();
    std::vector<Requester> relatedRequesters;
	// For each requester stored
    while (requesterFile.read(reinterpret_cast<char*>(&requester), sizeof(Requester))) {
        // For each 'requester name' attached to the selected change item
		for (const auto& name : requesterNames) {
			// Store the 'requester'
            if (std::strcmp(requester.reqName, name.c_str()) == 0) {
                relatedRequesters.push_back(requester);
                requesterFound = true;
            }
        }
    }
    requesterFile.clear();
    if (!requesterFound) {
        std::cerr << "No requesters found for ChangeItem with ChangeID " << changeID << ".\n";
        return;
    }

    // Generate the report
    std::cout << "Report #2: List of Customers/Staff Who Need to Be Informed When a Particular Change Has Been Implemented\n";
    // Print each relevant requester's name and email
	for (const auto& req : relatedRequesters) {
        std::cout << "Name: " << req.reqName << ", Email: " << req.email << "\n";
    }
}
