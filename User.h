#ifndef USER_H
#define USER_H

#include <string>

// ============================================
// Module Name: User.h
// ============================================

// Version History:
// Rev. 1 - 2024/07/01 - Neel Sadafule

// ============================================
// Data structures
// ---------------------------------------------

struct User {
    std::string name;           // Name of the user
    std::string phoneNumber;    // Phone number of the user
    std::string email;          // Email address of the user
    std::string role;           // Role of the user ("Customer" or "Employee")
    std::string department;     // Department of the user (if role is "Employee")
};

#endif // USER_H
