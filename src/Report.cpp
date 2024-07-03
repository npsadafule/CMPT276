#include "Report.h"
#include "Product.h"
#include "User.h"
#include <iostream>
#include <fstream>

// File handling functions
std::fstream reportFile;

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
    Product product;
    openProductFile();
    seekToBeginningOfProductFile();
    while (getNextProduct(product)) {
        if (product.name == productName) {
            std::cout << "Report #1: List of All Change Items for " << productName << " that are Not Done and Not Cancelled\n";
            for (const auto& [id, item] : product.changeItems) {
                if (item.state != "Done" && item.state != "Cancelled") {
                    std::cout << "ID: " << id << ", Description: " << item.description << ", State: " << item.state << ", Anticipated Release ID: " << item.anticipatedReleaseID << "\n";
                }
            }
            closeProductFile();
            return;
        }
    }
    std::cerr << "Product does not exist. Please try again.\n";
    closeProductFile();
}

// ---------------------------------------------------------
// Function: generateReport2
void generateReport2(const std::string& changeID) {
    openReportFile();
    seekToBeginningOfReportFile();
    Report report;
    while (getNextReport(report)) {
        if (report.changeID == changeID) {
            std::cout << "Report #2: List of Customers/Staff Who Need to Be Informed When a Particular Change Has Been Implemented\n";
            for (const auto& user : report.users) {
                std::cout << "Name: " << user.name << ", Email: " << user.email << "\n";
            }
            closeReportFile();
            return;
        }
    }
    std::cerr << "Change Request not found. Please try again.\n";
    closeReportFile();
}
