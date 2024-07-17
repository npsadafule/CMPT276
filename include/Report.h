#ifndef REPORT_H
#define REPORT_H

#include <string>
#include <vector>
#include <fstream>
#include "Requester.h"

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

// Opens the Report file
void openReportFile();

// Closes the Report file
void closeReportFile();

// Writes a Report to the file
// Parameter: report (The Report to write)
void writeReport(const Report& report);

// Seeks to the beginning of the Report file
void seekToBeginningOfReportFile();

// Retrieves the next Report from the file
// Parameter: report (The Report object to store the retrieved data)
// Returns: bool (true if retrieval was successful, false otherwise)
bool getNextReport(Report& report);

// Generates a report based on the product name
// Parameter: productName (The name of the product)
void generateReport1(const std::string& productName);

// Generates a report based on the change ID
// Parameter: changeID (The ID of the change)
void generateReport2(const std::string& changeID);

// External declaration for the report file stream
extern std::fstream reportFile;

#endif // REPORT_H
