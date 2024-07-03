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

// ---------------------------------------------
// Function: createProduct
// Description: Creates a new product and adds it to the global product list.
// Parameters:
// - name: The name of the product (in).
// ---------------------------------------------
void createProduct(const std::string& name);

// ---------------------------------------------
// Function: createRelease
// Description: Creates a new release for an existing product.
// Parameters:
// - productName: The name of the product (in).
// - releaseID: The ID of the release (in).
// - releaseDate: The release date (in).
// ---------------------------------------------
void createRelease(const std::string& productName, const std::string& releaseID, const std::string& releaseDate);

#endif // PRODUCT_H
