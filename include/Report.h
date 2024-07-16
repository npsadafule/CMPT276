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
void openReportFile();
void closeReportFile();
void writeReport(const Report& report);
void seekToBeginningOfReportFile();
bool getNextReport(Report& report);
void generateReport1(const std::string& productName);
void generateReport2(const std::string& changeID);

extern std::fstream reportFile;

#endif // REPORT_H
