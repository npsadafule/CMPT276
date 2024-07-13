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

// Global variable definitions
extern std::vector<Product> products;
extern std::fstream changeItemFile;

// ============================================
// Function Implementations
// ============================================

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