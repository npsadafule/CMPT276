// ============================================
// Module Name: Report.cpp
// ============================================
// Version History:
// Rev. 3 - 2024/07/30 - Group 7
	// Kenneth Tan: Edited comments to match Assignment 5 requirements and removed unused parameters.
	// Kenneth Tan and Neel Sadafule: Implemented Report Generation #1 and #2.
// Rev. 2 - 2024/07/17 - Group 7
// Rev. 1 - 2024/07/01 - Group 7
// ============================================

// Overall internal design issues:
// This module implements report generation #1 and #2. Generation is done through the use of structs 
// of lower-level modules. It uses linear search to find records within various
// files based on a criteria of attributes (e.g., primary key (single or compound)).

#include "Report.h"
#include "Product.h"
#include "Requester.h"
#include "ChangeRequest.h"
#include "ChangeItem.h"
#include <iostream>
#include <fstream>
#include <iomanip>

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
int generateReport1(int& page,const char* productName) {
	// Generates a report listing all change items for a specific product that are not done and not cancelled
	// Prints the report to standard output
    // Returns the number of modules displayed or -1 if the file cannot be opened.
    // Parameter: page (The page number to display)
    // Parameter: filename (The name of the module file)
	
	// Constants
	static const int ITEMS_PER_PAGE = 20;	// static

	// Variables
	int modulePages;
	ChangeItem tmpModule;

	// Find the total number of items on file
	seekToBeginningOfChangeItemFile();
	int counter = 0;
	// Loop by the size of ChangeItem to retrieve all change items from file
	while (changeItemFile.read(reinterpret_cast<char*>(&tmpModule), sizeof(ChangeItem))) {
		if (strcmp(tmpModule.productName,productName) == 0) {
			counter++;
		}
	}
	changeItemFile.clear();
	// std::cout << "total entries " << std::to_string(counter) << std::endl;

	// Calculate the total number of pages
	modulePages = (counter + ITEMS_PER_PAGE-1) / ITEMS_PER_PAGE;
	// std::cout << "total pages " << std::to_string(modulePages) << std::endl;

	// Handle no items case
	if (modulePages == 0) {
		modulePages = 1;
	}

	// Determine if the provided page is valid
	if ((page < 1) || (page > modulePages)) {
		if (page < 1) {
			page++;
			std::cout << "No previous pages exist!" << std::endl;
		} else {
			page--;
			std::cout << "No next pages exist!" << std::endl;
		}
	} 

	// Display the selected page
	// Loop forward by the number of pages on the file so that the next read is the
	// desired page
	seekToBeginningOfChangeItemFile();
	// Skip 20 * "number of pages to flip" records that have the given product
	if ((page-1) != 0) {
		int pageRecordsCount0 = 0;
		// Loop by the size of ChangeItem to move the changeItemFile get pointer past the first 
		// (page-1)*(ITEMS_PER_PAGE) change items with a productName attribute of 'productName'
		while (changeItemFile.read(reinterpret_cast<char*>(&tmpModule), sizeof(ChangeItem)) && 
			(pageRecordsCount0 < (page-1)*(ITEMS_PER_PAGE))) {
			if (strcmp(tmpModule.productName,productName) == 0) {
				pageRecordsCount0++;
				if (pageRecordsCount0 == (page-1)*ITEMS_PER_PAGE) break;
			}
		}
		changeItemFile.clear();
	}
	// std::cout << "end of getting to page" << std::endl;

	// Print the page
	int pageRecordsCount = 0;
	std::cout << std::endl;
	std::cout << "Product A Report #1" << std::endl;
	std::cout << "Page " << page << "/" << modulePages << std::endl;
	std::cout << "                                                                     Anticipated" << std::endl;
	std::cout << "  Product     Description                     Change ID  State       Release ID" << std::endl;
	// Loop by the size of ChangeItem to read each ChangeItem from file until ITEMS_PER_PAGE or less number of 
	// change items are displayed with the productName 'productName' and have a state that is not 'Done' or 'Cancelled'
	while (changeItemFile.read(reinterpret_cast<char*>(&tmpModule), sizeof(ChangeItem)) && 
		  (pageRecordsCount < ITEMS_PER_PAGE)) {
		if ((strcmp(tmpModule.productName,productName) == 0) &&
			!(strcmp(tmpModule.state,"Done") == 0) &&
			!(strcmp(tmpModule.state,"Cancelled") == 0)) {
			std::cout << "- ";
			displayChangeItem(tmpModule);
			pageRecordsCount++;
		}
	}
	changeItemFile.clear();
	std::cout << "Enter ‘Exit’ to stop viewing the generated Report #1." << std::endl;
	std::cout << "If previous/next pages exist, enter ‘<’ for the previous page and ‘>’ for the next page." << std::endl;

	
	return pageRecordsCount;
}

// ---------------------------------------------------------
// Function: generateReport2
void generateReport2(const int changeID, const char* newReleaseID, const char* productName) {
	// Generates a report listing customers/staff who need to be informed when a particular change has been implemented
	// Prints the report to standard output
    ChangeItem changeItem;
    Requester requester;
    ChangeRequest changeRequest;
    bool changeRequestFound = false;
    bool requesterFound = false;

	// Retrieve the relevant product release
    ProductRelease productRelease;
    retrieveProductReleaseByKey(productName, newReleaseID, productRelease);

    // Update the anticipated release ID of the change item
	retrieveChangeItemByKey(changeID,changeItem);
	// Update the anticipated release ID of the change item in its RAM object
	std::strcpy(changeItem.anticipatedReleaseID,newReleaseID);
	// Make the update
	updateChangeItem(changeID, changeItem);

    // Find the change requests for the chosen change item
    seekToBeginningOfChangeRequestFile();
    std::vector<std::string> requesterNames;
	// Loop by the size of a ChangeRequest to read all change requests from file
    while (changeRequestFile.read(reinterpret_cast<char*>(&changeRequest), sizeof(ChangeRequest))) {
        if (changeRequest.changeID == changeID) {
            changeRequestFound = true;
            requesterNames.push_back(changeRequest.requesterName);
        }
    }
    changeRequestFile.clear();
    if (!changeRequestFound) {
        std::cerr << "No change request found for ChangeItem with ChangeID " << changeID << ".\n";
        return;
    }

	// Find the requesters attached to each change request
    seekToBeginningOfRequesterFile();
    std::vector<Requester> relatedRequesters;
    // For each requester stored
	// Loop by the size of Requesters to read all requesters from file
    while (requesterFile.read(reinterpret_cast<char*>(&requester), sizeof(Requester))) {
        // Loop for each 'requester name' from a change request of the selected change item
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

    // Generate the formatted report
	std::cout << std::endl;
    std::cout << productName << " Report #2 for Change Item " << changeID << "\n\n";
    std::cout << "Details of the selected Change Item post-update:\n";
    std::cout << changeItem.productName << ", " << changeItem.description << ", " << changeItem.changeID
              << ", " << changeItem.state << ", " << changeItem.anticipatedReleaseID << "\n";
    std::cout << "(Product, Description, Change ID, State, Anticipated Release ID)\n\n";
    std::cout << "The following customers will be informed that their Change Request for\n";
    std::cout << "Change Item " << changeID << " of " << changeItem.productName << " was implemented. They will be able to see\n";
    std::cout << "the changes made on Release " << newReleaseID << " of ITS on " << productRelease.releaseDate << ".\n\n";

    std::cout << "  Requester                       Email\n";
	// Loop for each of the requesters related to change requests of the chosen change item
    for (const auto& req : relatedRequesters) {
        std::cout << std::left << "- " << std::setw(30) << req.reqName << "  " << std::setw(24) << req.email << "\n";
    }
}
