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
int generateReport1(int& page,const char* productName) {
	// Displays up to 20 module objects from the specified page of the module file.
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
	changeItemFile.seekp((page-1)*ITEMS_PER_PAGE*sizeof(ChangeItem),std::ios::cur);
	// std::cout << "end of getting to page" << std::endl;

	// Print the page
	int pageRecordsCount = 0;
	std::cout << std::endl;
	std::cout << "Product A Report #1" << std::endl;
	std::cout << "Page " << page << "/" << modulePages << std::endl;
	std::cout << "                                                                     Anticipated" << std::endl;
	std::cout << "  Product     Description                     Change ID  State       Release ID" << std::endl;
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
// Generates a report listing customers/staff who need to be informed when a particular change has been implemented
// Prints the report to standard output
void generateReport2(const std::string& changeID, const std::string& newReleaseID) {
    ChangeItem changeItem;
    Requester requester;
    ChangeRequest changeRequest;
    bool changeItemFound = false;
    bool changeRequestFound = false;
    bool requesterFound = false;

    // Prompt for product name
    std::string productName;
    std::cout << "Enter the product name: ";
    std::cin >> productName;

    // Validate product name
    Product product;
    if (!retrieveProductByName(productName.c_str(), product)) {
        std::cerr << "Product " << productName << " not found.\n";
        return;
    }

    // Search for the ChangeItem with the specified changeID
    seekToBeginningOfChangeItemFile();
    while (changeItemFile.read(reinterpret_cast<char*>(&changeItem), sizeof(ChangeItem))) {
        if (std::to_string(changeItem.changeID) == changeID && std::strcmp(changeItem.productName, productName.c_str()) == 0) {
            changeItemFound = true;
            break;
        }
    }
    changeItemFile.clear();
    if (!changeItemFound) {
        std::cerr << "ChangeItem with ChangeID " << changeID << " not found for product " << productName << ".\n";
        return;
    }

    // Validate release ID matches the product
    ProductRelease productRelease;
    if (!retrieveProductReleaseByKey(productName.c_str(), newReleaseID.c_str(), productRelease)) {
        std::cerr << "ReleaseID " << newReleaseID << " not found for product " << productName << ".\n";
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

    // Generate the formatted report
    std::cout << "Product " << productName << " Report #2 for Change Item " << changeID << "\n\n";
    std::cout << "Details of the Current Change Item:\n";
    std::cout << changeItem.productName << ", " << changeItem.description << ", " << changeItem.changeID
              << ", " << changeItem.state << ", " << changeItem.anticipatedReleaseID << "\n";
    std::cout << "(Product, Description, Change ID, State, Anticipated Release ID)\n\n";
    std::cout << "The following customers will be informed that their Change Request for\n";
    std::cout << "Change Item " << changeID << " of " << changeItem.productName << " was implemented. They will be able to see\n";
    std::cout << "the changes made on Release " << newReleaseID << " of ITS on 2024-07-23.\n\n";

    std::cout << "    Requestor        Email\n";
    int count = 1;
    for (const auto& req : relatedRequesters) {
        std::cout << count << ")  " << req.reqName << "     " << req.email << "\n";
        ++count;
    }
}
