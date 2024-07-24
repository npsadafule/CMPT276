// ============================================
// Module Name: SystemController.cpp
// ============================================
// Version History:
// Rev. 2 - 2024/07/17 - Group 7
// ============================================

// Overall internal design issues:
// This module implements SystemController.h, following our central control design from our Architectural Design Document. Specifically, it houses the implementation of the start-up function, along with each module's file initialization function. Currently, shutdown functions are stored in their respective lower-level modules, but they will be stored here in our fifth release.

#include "SystemController.h"
#include "Product.h"
#include "ChangeRequest.h"
#include "Report.h"
#include "Requester.h"
#include "ChangeItem.h"
#include <iostream>
#include <fstream>

// Global file streams
std::fstream requesterFile;
std::fstream productFile;
std::fstream productReleaseFile;
std::fstream changeRequestFile;
std::fstream changeItemFile;
std::fstream highestCIDFile;


// ============================================
// Function Implementations
// ============================================
// ---------------------------------------------------------
// Function: initRequester
void initRequester() {
    // Initializes the requester file stream for reading and writing requesters.
    // Ensures the requesterFile stream is opened in binary append mode.
    requesterFile.open("requestersFile.dat", std::ios::in | std::ios::out | std::ios::binary | std::ios::app);
    if (!requesterFile.is_open()) {
        std::cerr << "Failed to open requestersFile.dat file.\n";
        exit(1);
    }
}

// ---------------------------------------------------------
// Function: initProduct
void initProduct() {
    // Initializes the product and product release file streams for reading and writing products.
    // Ensures both productFile and productReleaseFile streams are opened in binary append mode.
    productFile.open("products.dat", std::ios::in | std::ios::out | std::ios::binary | std::ios::app);
    if (!productFile.is_open()) {
        std::cerr << "Failed to open products.dat file.\n";
        exit(1);
    }

    productReleaseFile.open("productReleases.dat", std::ios::in | std::ios::out | std::ios::binary | std::ios::app);
    if (!productReleaseFile.is_open()) {
        std::cerr << "Failed to open productReleases.dat file.\n";
        exit(1);
    }
}

// ---------------------------------------------------------
// Function: initChangeRequest
void initChangeRequest() {
    // Initializes the change request file stream for reading and writing change requests.
    // Ensures the changeRequestFile stream is opened in binary append mode.
    changeRequestFile.open("changeRequests.dat", std::ios::in | std::ios::out | std::ios::binary | std::ios::app);
    if (!changeRequestFile.is_open()) {
        std::cerr << "Failed to open changeRequests.dat file.\n";
        exit(1);
    }
}

// ---------------------------------------------------------
// Function: initChangeItem
void initChangeItem() {
    changeItemFile.open("changeItems.dat", std::ios::in | std::ios::out | std::ios::binary);

    // If the file does not exist, create it
    if (!changeItemFile.is_open()) {
        // Open the file in write mode to create it
        changeItemFile.open("changeItems.dat", std::ios::out | std::ios::binary);
        if (!changeItemFile.is_open()) {
            std::cerr << "Failed to create changeItems.dat file.\n";
            exit(1);
        }
        changeItemFile.close(); // Close the file after creating it

        // Reopen the file in read/write mode
        changeItemFile.open("changeItems.dat", std::ios::in | std::ios::out | std::ios::binary);
        if (!changeItemFile.is_open()) {
            std::cerr << "Failed to reopen changeItems.dat file.\n";
            exit(1);
        }
    }
}

// ---------------------------------------------------------
// Function: initReportGen
void initReportGen() {
    // Initializes the report generation functionality.
    // This function is currently to be determined (TBD) and has no implementation.
    // May or may not be needed for Assignment 5
}

// ---------------------------------------------------------
// Function: initHighestCID
void initHighestCID() {
    // Open the file in append mode and binary mode
    highestCIDFile.open("highestCID.dat", std::ios::app | std::ios::binary);
    if (!highestCIDFile.is_open()) {
        std::cerr << "Failed to open or create highestCID.dat file.\n";
        exit(1);
    }
    
    // Close and reopen the file in read/write mode
    highestCIDFile.close();
    highestCIDFile.open("highestCID.dat", std::ios::in | std::ios::out | std::ios::binary);
    if (!highestCIDFile.is_open()) {
        std::cerr << "Failed to reopen highestCID.dat file.\n";
        exit(1);
    }
}

// ---------------------------------------------------------
// Function: start
void start() {
    // Starts the system, initializing all necessary components.
    // Calls functions to initialize requester, product, change request, change item,
    // report generation, and highest change ID functionalities.
    initRequester();
    initProduct();
    initChangeRequest();
    initChangeItem();
    initReportGen();
    initHighestCID();
    storeHighestCID();
}

// ---------------------------------------------------------
// Function: shutdown
void shutdown() {
    // Shuts down the system, closing all open file streams.
    // Calls functions to close requester, product, change request, change item,
    // and report file streams.
    closeRequesterFile();
    closeProductFile(); // Function call to close product file (not defined here)
    closeChangeRequestFile(); // Function call to close change request file (not defined here)
    closeChangeItemFile(); // Function call to close change item file (not defined here)
    closeReportFile(); // Function call to close report file (not defined here)
    closeHighestCID(); // Function call to close highest change ID file (not defined here)
}

// End of file