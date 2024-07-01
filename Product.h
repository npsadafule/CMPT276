#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <map>

// ============================================
// Module Name: Product.h
// ============================================

// Version History:
// Rev. 1 - 2024/07/01 - Neel Sadafule

// ============================================
// Data structures
// ---------------------------------------------

struct ChangeItem {
    std::string description;        // Description of the change item
    std::string changeID;           // Unique identifier for the change item
    std::string state;              // Current state of the change item
    std::string anticipatedReleaseID; // Anticipated release ID for the change item
};

struct Product {
    std::string name;                       // Name of the product
    std::map<std::string, ChangeItem> changeItems; // Map of change items associated with the product
};

// Function Declarations
// ============================================

/**
 * @brief Creates a new product.
 * 
 * @param name Name of the product to be created.
 */
void createProduct(const std::string& name);

/**
 * @brief Creates a new release for an existing product.
 */
void createRelease();

#endif // PRODUCT_H
