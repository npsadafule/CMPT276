#ifndef REPORT_H
#define REPORT_H

#include <string>
#include <vector>
#include "User.h"

// ============================================
// Data structures
// ============================================
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

#endif // REPORT_H
