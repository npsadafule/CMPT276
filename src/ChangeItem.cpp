// ============================================
// Module Name: ChangeItem.cpp
// ============================================
// Version History:
// Rev. 1 - 2024/07/01 - Group 7
// ============================================

#include "ChangeItem.h"
#include "Product.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>

// Global variable definitions
extern std::vector<Product> products;
extern std::fstream changeItemFile;

// ============================================
// Function Implementations
// ============================================

const char* intToCString(int number) {
    static std::string str; // static to ensure memory is not deallocated after function exits
    str = std::to_string(number);
    return str.c_str();
}

void openChangeItemFile() {
	// Note: trunc is ensuring that we test with an empty file: pre-condition followed
    changeItemFile.open("changeItems.dat", std::ios::in | std::ios::out | std::ios::binary | std::ios::app);
    
	// Check if file opening worked properly, exit if it didn't
	if (!changeItemFile.is_open()) exit(1);
}


// ---------------------------------------------------------
// Function: closeProductFile
void closeChangeItemFile() {
    // if (productFile.is_open()) {
    //     productFile.close();
    // }
}

// ---------------------------------------------------------
// Function: writeProduct
void writeChangeItem(const ChangeItem& ChangeItem) {
    // if (!productFile.is_open()) return;

	// // Get the character address of the product struct, write it a byte at a time (char),
	// // writing "sizeof(Product)" amount of bytes  
	// // Note: fixed-length writing as Product is a struct and attribute type fixes the struct size
    // productFile.write(reinterpret_cast<const char*>(&product), sizeof(Product));

	// // Check if we ran out of disk space; exit if we have
	// if (!productFile.good()) exit(1);
}

// ---------------------------------------------------------
// Function: seekToBeginningOfProductFile
void seekToBeginningOfChangeItemFile() {
    // if (!productFile.is_open()) return;

	// // Reset internal flags
    // productFile.clear();

	// // Set the position in the input sequence to the beginning of the file
	// // Zero offest from the beginning of the file
    // productFile.seekg(0, std::ios::beg);
}

// ---------------------------------------------------------
// Function: getNextProduct
bool getNextChangeItem(const ChangeItem& ChangeItem) {
    // if (!productFile.is_open()) return false;
    // productFile.read(reinterpret_cast<char*>(&product), sizeof(Product));
    // return !productFile.fail();
}

// For bringing up lists of products for reports
void readChangeItemFile(const char* filename,
						int changeID,
						const char* productName,
						const char* description,
						const char* anticipatedReleaseID,
						const char* state) {
    // std::ifstream inFile(filename, std::ios::binary);
    // if (!inFile) {
    //     std::cerr << "Failed to open file for reading!" << std::endl;
    //     return;
    // }

    // while (inFile.read(reinterpret_cast<char*>(&product), sizeof(Product))) {
    //     std::cout << "Product Name: " << product.name << std::endl;
    // }
}

// For retrieving a particular product with a particular name
bool retrieveChangeItemByKey(const char* filename, int changeID) {

	// seekToBeginningOfProductFile();

	// std::ifstream inFile(filename, std::ios::binary);
    // if (!inFile) {
    //     std::cerr << "Failed to open file for reading!" << std::endl;
    //     return false;
    // }

    // // Read each product from the file and compare its name with the target name
    // while (inFile.read(reinterpret_cast<char*>(&tmpProduct), sizeof(Product))) {
    //     if (std::strcmp(tmpProduct.name, productName) == 0) {
    //         inFile.close();
			
	// 		// Store the product into the product outside of the function
	// 		std::strcpy(product.name, tmpProduct.name);

    //         return true; // Product found
    //     }
    // }

    // inFile.close();
    // return false; // Product not found
}

// ---------------------------------------------------------
// Function: createProduct

// NOTE: DOESNT APPEND, CHECK DUPLICATE
void createChangeItem(int changeID,
					  const char* productName,
					  const char* description,
					  const char* anticipatedReleaseID,
					  const char* state) { 
	// // Create the product
    // Product product = {};
	
	// // Store the string into product's name attribute
	// std::strcpy(product.name, namePtr);

	// //std::cout << "createProduct: the product we received was named " << product.name << std::endl;

	// // Check if the product is on the file
	// bool productExists = false;

	// Product tmpProduct;

	// seekToBeginningOfProductFile();
	
	// std::ifstream inFile("products.dat", std::ios::binary);
    // if (!inFile) {
    //     std::cerr << "Failed to open file for reading!" << std::endl;
    //     exit(1);
    // }

	// while (inFile.read(reinterpret_cast<char*>(&tmpProduct), sizeof(Product))) {
    //     if (std::strcmp(tmpProduct.name, namePtr) == 0) {
	// 		productExists = true;
    //     }
    // }
	// inFile.close();

	// // If the product doesn't exist, append it to the end of the file
    // if (!productExists) {
	// 	writeProduct(product);
	// }	
}

// ---------------------------------------------------------
// Function: queryChangeItem
// void queryChangeItem(
// const std::string& productName, // in
// const std::string& changeID // in
// ) {
// // Description:
// // Queries and displays the details of a change item for a specified
// // product. If the product
// // or the change item does not exist, it displays an error message.
// auto it = std::find_if(products.begin(), products.end(), [&](const
// 	Product& p) { return p.name == productName; });
// if (it == products.end()) {
// 	std::cerr << "Product does not exist. Please try again.\n";
// 	return;
// }

// auto itemIt = it->changeItems.find(changeID);
// if (itemIt == it->changeItems.end()) {
// 	std::cerr << "Change Item does not exist. Please try again.\n";
// 	return;
// }


// const ChangeItem& item = itemIt->second;
// std::cout << "Product: " << productName << "\nDescription: " << item.
// 	description << "\nChange ID: " << item.changeID << "\nState: " <<
// 	item.state << "\nAnticipated Release ID: " << item.
// 	anticipatedReleaseID << "\n";
// }

// ---------------------------------------------------------
// Function: updateChangeItem
// void updateChangeItem(
// 	const std::string& productName, // in
// 	const std::string& changeID, // in
// 	const std::string& newState // in
// ) {
// 	// Description:
// 	// Updates the state of a change item for a specified product. If the
// 	// product or the change
// 	// item does not exist, it displays an error message.
// 	auto it = std::find_if(products.begin(), products.end(), [&](const
// 	Product& p) { return p.name == productName; });
// 	if (it == products.end()) {
// 	std::cerr << "Product does not exist. Please try again.\n";
// 	return;
// 	}

// 	auto itemIt = it->changeItems.find(changeID);
// 	if (itemIt == it->changeItems.end()) {
// 	std::cerr << "Change Item does not exist. Please try again.\n";
// 	return;
// 	}

// 	ChangeItem& item = itemIt->second;
// 	item.state = newState;
// 	std::cout << "Change Item updated successfully.\n";
// }