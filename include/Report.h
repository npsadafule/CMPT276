// ============================================
// Module Name: Report.h
// ============================================
// Version History:
// Rev. 2 - 2024/07/17 - Group 7
// ============================================

#ifndef REPORT_H
#define REPORT_H

#include <string>
#include <vector>
#include <fstream>
#include "Requester.h"

// Global variables
// External declaration for the report file stream
extern std::fstream reportFile;

// ============================================
// Data structures
// ============================================
struct User {
    std::string name;
    std::string email;
};

struct Report {
    std::string changeID;
    std::vector<User> users;
};

// ============================================
// Function Declarations
// ============================================

// ---------------------------------------------------------
// Opens the Report file
void openReportFile();

// ---------------------------------------------------------
// Closes the Report file
void closeReportFile();

// ---------------------------------------------------------
// Writes a Report to the file
void writeReport(
    // Parameter: report (The Report to write)
    const Report& report    // in
);

// ---------------------------------------------------------
// Seeks to the beginning of the Report file
void seekToBeginningOfReportFile();

// ---------------------------------------------------------
bool getNextReport(
    // Retrieves the next Report from the file
    // Parameter: report (The Report object to store the retrieved data)
    // Returns: bool (true if retrieval was successful, false otherwise)
    Report& report    // out
);

// ---------------------------------------------------------
// Generates a report based on the product name
int generateReport1(
    // Parameter: productName (The name of the product)
    int& page,	// in/out
	const char* productName    // in
);

// ---------------------------------------------------------
// Generates a report based on the change ID
void generateReport2(
    // Parameter: changeID (The ID of the change)
    const int changeID,		// in
	const char* newReleaseID,	// in
	const char* productName		// in
);

#endif // REPORT_H