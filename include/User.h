#ifndef USER_H
#define USER_H

#include <string>

// ============================================
// Data structures
// ============================================
struct User {
    std::string name;
    std::string phoneNumber;
    std::string email;
    std::string role; // "Customer" or "Employee"
    std::string department;
};

#endif // USER_H
