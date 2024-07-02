#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>

// Constants for fixed length strings
const int PRODUCT_NAME_LENGTH = 30;
const int CHANGE_DESCRIPTION_LENGTH = 150;
const int CHANGE_ID_LENGTH = 6;
const int STATE_LENGTH = 15;
const int RELEASE_ID_LENGTH = 8;
const int USER_NAME_LENGTH = 30;
const int PHONE_NUMBER_LENGTH = 15;
const int EMAIL_LENGTH = 30;
const int ROLE_LENGTH = 10;
const int DEPARTMENT_LENGTH = 30;

struct ChangeItem {
    char description[CHANGE_DESCRIPTION_LENGTH];
    char changeID[CHANGE_ID_LENGTH];
    char state[STATE_LENGTH];
    char anticipatedReleaseID[RELEASE_ID_LENGTH];
};

struct Product {
    char name[PRODUCT_NAME_LENGTH];
    int numChangeItems;
    std::vector<ChangeItem> changeItems;
};

struct User {
    char name[USER_NAME_LENGTH];
    char phoneNumber[PHONE_NUMBER_LENGTH];
    char email[EMAIL_LENGTH];
    char role[ROLE_LENGTH];
    char department[DEPARTMENT_LENGTH];
};

void writeString(std::ofstream &out, const char *str, int length) {
    out.write(str, length);
}

void writeProduct(std::ofstream &out, const Product &product) {
    writeString(out, product.name, PRODUCT_NAME_LENGTH);
    out.write(reinterpret_cast<const char*>(&product.numChangeItems), sizeof(product.numChangeItems));
    for (const auto &changeItem : product.changeItems) {
        writeString(out, changeItem.description, CHANGE_DESCRIPTION_LENGTH);
        writeString(out, changeItem.changeID, CHANGE_ID_LENGTH);
        writeString(out, changeItem.state, STATE_LENGTH);
        writeString(out, changeItem.anticipatedReleaseID, RELEASE_ID_LENGTH);
    }
}

void writeUser(std::ofstream &out, const User &user) {
    writeString(out, user.name, USER_NAME_LENGTH);
    writeString(out, user.phoneNumber, PHONE_NUMBER_LENGTH);
    writeString(out, user.email, EMAIL_LENGTH);
    writeString(out, user.role, ROLE_LENGTH);
    if (std::strcmp(user.role, "Employee") == 0) {
        writeString(out, user.department, DEPARTMENT_LENGTH);
    }
}

int main() {
    std::ofstream outFile("dummy_data.bin", std::ios::binary);

    // Dummy Products
    std::vector<Product> products = {
        {"Product1", 2, {{"Change1 Description", "12345", "Reported", "Rel1"}, {"Change2 Description", "65432", "InProgress", "Rel2"}}},
        {"Product2", 1, {{"Change3 Description", "11111", "Done", "Rel3"}}}
    };

    // Dummy Users
    std::vector<User> users = {
        {"John Doe", "(123)456-7890", "john.doe@example.com", "Customer", ""},
        {"Jane Smith", "(098)765-4321", "jane.smith@example.com", "Employee", "Development"}
    };

    // Write number of products
    int numProducts = products.size();
    outFile.write(reinterpret_cast<const char*>(&numProducts), sizeof(numProducts));

    // Write products
    for (const auto &product : products) {
        writeProduct(outFile, product);
    }

    // Write number of users
    int numUsers = users.size();
    outFile.write(reinterpret_cast<const char*>(&numUsers), sizeof(numUsers));

    // Write users
    for (const auto &user : users) {
        writeUser(outFile, user);
    }

    outFile.close();
    std::cout << "Dummy data written to dummy_data.bin\n";
    return 0;
}
