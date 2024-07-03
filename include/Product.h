// ============================================
// Module Name: Product.h
// ============================================
// Version History:
// Rev. 1 - 2024/07/01 - Neel Sadafule
// ============================================

#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <map>

// ============================================
// Data structures
// ============================================
struct ChangeItem {
    std::string description;
    std::string changeID;
    std::string state;
    std::string anticipatedReleaseID;
};

struct Product {
    std::string name;
    std::map<std::string, ChangeItem> changeItems;
    std::map<std::string, std::string> releases; // Added releases map
};

// ============================================
// Function Declarations
// ============================================

// ---------------------------------------------------------
// Function: createProduct
void createProduct(
    const std::string& name    // in
);

// ---------------------------------------------------------
// Function: createRelease
void createRelease(
    const std::string& productName,    // in
    const std::string& releaseID,      // in
    const std::string& releaseDate     // in
);

#endif // PRODUCT_H
