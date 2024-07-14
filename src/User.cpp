#include "User.h"
#include <fstream>
#include <vector>

// Global variable definition
// extern std::vector<User> users;
extern std::fstream requesterFile;

// ============================================
// Function Implementations: Product Release
// ============================================

// ---------------------------------------------------------
// Function: openRequesterFile
void openRequesterFile() {
	// Note: trunc is ensuring that we test with an empty file: pre-condition followed
    requesterFile.open("requestersFile.dat", std::ios::in | std::ios::out | std::ios::binary | std::ios::app);

	// Check if file opening worked properly, exit if it didn't
	if (!requesterFile.is_open()) exit(1);
}

// ---------------------------------------------------------
// Function: closeProductReleaseFile
void closeRequesterFile() {
    // if (productReleaseFile.is_open()) {
    //     productReleaseFile.close();
    // }
}

// ---------------------------------------------------------
// Function: writeProductRelease
void writeRequester(const Requester& requester) {
    // if (!productReleaseFile.is_open()) return;

	// // Get the character address of the product struct, write it a byte at a time (char),
	// // writing "sizeof(Product)" amount of bytes  
	// // Note: fixed-length writing as Product is a struct and attribute type fixes the struct size
	// productReleaseFile.write(reinterpret_cast<const char*>(&productRelease), sizeof(ProductRelease));

	// // Check if we ran out of disk space; exit if we have
	// if (!productReleaseFile.good()) exit(1);
}

// ---------------------------------------------------------
// Function: seekToBeginningOfProductReleaseFile
void seekToBeginningOfRequesterFile() {
    // if (!productReleaseFile.is_open()) return;

	// // Reset internal flags
    // productReleaseFile.clear();

	// // Set the position in the input sequence to the beginning of the file
	// // Zero offest from the beginning of the file
    // productReleaseFile.seekg(0, std::ios::beg);
}

void displayRequester(const Requester& requester) {
	// std::cout << productRelease.productName <<
	// 			 ", " << productRelease.releaseID <<
	// 			 ", " << productRelease.releaseDate << std::endl;
}

void requesterFileDisplay20OrLess(const char* filename) {
	// const int MAX_READS = 20;

	// ProductRelease tmpPR;

    // std::ifstream inFile(filename, std::ios::binary);
    // if (!inFile) {
    //     std::cerr << "Failed to open file for reading!" << std::endl;
    //     return;
    // }

	// int counter = 0;
    // while (inFile.read(reinterpret_cast<char*>(&tmpPR), sizeof(ProductRelease)) &&
	// 	   counter < MAX_READS) {
	// 	displayProductRelease(tmpPR);
	// 	counter++;
    // }
}


// For retrieving a particular product with a particular key
bool retrieveRequesterByKey(const char* filename, const char* reqName, Requester& requester) {
	// ProductRelease tmpProductRelease;

	// seekToBeginningOfProductReleaseFile();

	// std::ifstream inFile(filename, std::ios::binary);
    // if (!inFile) {
    //     std::cerr << "Failed to open file for reading!" << std::endl;
    //     return false;
    // }

    // while (inFile.read(reinterpret_cast<char*>(&tmpProductRelease), sizeof(ProductRelease))) {
	// 	// If in the inFile, there exists an element that matches what we hope to retrieve
    //     if ((std::strcmp(tmpProductRelease.productName, productReleaseName) == 0) &&
	// 		(std::strcmp(tmpProductRelease.releaseID, releaseID) == 0)) {
	// 		inFile.close();
			
	// 		// Store the product into the product outside of the function
	// 		std::strcpy(productRelease.productName, tmpProductRelease.productName);
	// 		std::strcpy(productRelease.releaseID, tmpProductRelease.releaseID);
	// 		std::strcpy(productRelease.releaseDate, tmpProductRelease.releaseDate);

    //         return true; // Product found
    //     }
    // }

	// inFile.close();
    // return false; // Product not found
}

// ---------------------------------------------------------
// Function: createProductRelease
void createRequester(const char* reqName,
					 const char* phoneNumber,
					 const char* email,
					 const char* department) {	// Variables
	// // Create the product release
	// ProductRelease productRelease = {};
	
	// // Store input strings to their corresponding attributes
	// std::strcpy(productRelease.productName, productName);
	// std::strcpy(productRelease.releaseID, releaseID);
	// std::strcpy(productRelease.releaseDate, releaseDate);
	
	// // Write it to file
	// bool productReleaseExists = false;

    // ProductRelease tmpProductRelease;

	// seekToBeginningOfProductFile();

	// std::ifstream inFile("productReleases.dat", std::ios::binary);
    // if (!inFile) {
    //     std::cerr << "Failed to open product release file for reading!" << std::endl;
    //     exit(1);
    // }

    // // Read each product from the file and compare its name with the target name
	// // std::cout << "before read loop" << std::endl;
    // while (inFile.read(reinterpret_cast<char*>(&tmpProductRelease), sizeof(ProductRelease))) {
    //     if ((std::strcmp(tmpProductRelease.productName, productName) == 0) &&
	// 		(std::strcmp(tmpProductRelease.releaseID, releaseID) == 0)) {
	// 		productReleaseExists = true;
    //     }
    // }
	// inFile.close();
	
	// // If the product release doesn't exist, append it to the end of the file
    // if (!productReleaseExists) {
	// 	writeProductRelease(productRelease);
	// }	
}

