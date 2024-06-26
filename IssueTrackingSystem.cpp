#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

// Data structures
struct ChangeItem {
    std::string description;
    std::string changeID;
    std::string state;
    std::string anticipatedReleaseID;
};

struct Product {
    std::string name;
    std::map<std::string, ChangeItem> changeItems;
};

struct User {
    std::string name;
    std::string phoneNumber;
    std::string email;
    std::string role; // "Customer" or "Employee"
    std::string department;
};

std::vector<Product> products;
std::vector<User> users;
std::map<std::string, std::string> changeRequests;

void displayMainMenu();
void handleProductMaintenance();
void handleChangeRequestMaintenance();
void handleChangeItemMaintenance();
void handleReportGeneration();
void createProduct();
void createRelease();
void createChangeRequest();
void queryChangeItem();
void updateChangeItem();
void generateReport1();
void generateReport2();
void displayHelp();

int main() {
    displayMainMenu();
    return 0;
}

void displayMainMenu() {
    int choice;
    do {
        std::cout << "\n====== Main Menu ======\n";
        std::cout << "1) Product Maintenance\n";
        std::cout << "2) Change Request Maintenance\n";
        std::cout << "3) Change Item Maintenance\n";
        std::cout << "4) Report Generation\n";
        std::cout << "0) Exit\n";
        std::cout << "Enter the number you want [0-4]: ";
        std::cin >> choice;

        switch (choice) {
            case 1: handleProductMaintenance(); break;
            case 2: handleChangeRequestMaintenance(); break;
            case 3: handleChangeItemMaintenance(); break;
            case 4: handleReportGeneration(); break;
            case 0: std::cout << "Thank you for using the Issue Tracking System.\n"; break;
            default: std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);
}

void handleProductMaintenance() {
    int choice;
    do {
        std::cout << "\n====== Product Maintenance ======\n";
        std::cout << "1) Create a Product\n";
        std::cout << "2) Create a Release of a Product\n";
        std::cout << "0) Return to Main Menu\n";
        std::cout << "Choose an option [0-2] and press ENTER: ";
        std::cin >> choice;

        switch (choice) {
            case 1: createProduct(); break;
            case 2: createRelease(); break;
            case 0: break;
            default: std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);
}

void handleChangeRequestMaintenance() {
    int choice;
    do {
        std::cout << "\n====== Change Request Maintenance ======\n";
        std::cout << "1) Add a new change request\n";
        std::cout << "0) Go back to Main Menu\n";
        std::cout << "Choose an option [0-1] and press ENTER: ";
        std::cin >> choice;

        switch (choice) {
            case 1: createChangeRequest(); break;
            case 0: break;
            default: std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);
}

void handleChangeItemMaintenance() {
    int choice;
    do {
        std::cout << "\n====== Change Item Maintenance ======\n";
        std::cout << "1) Query Change Item to Screen\n";
        std::cout << "2) Update/Assess Change Item\n";
        std::cout << "0) Return to Main Menu\n";
        std::cout << "Choose an option [0-2] and press ENTER: ";
        std::cin >> choice;

        switch (choice) {
            case 1: queryChangeItem(); break;
            case 2: updateChangeItem(); break;
            case 0: break;
            default: std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);
}

void handleReportGeneration() {
    int choice;
    do {
        std::cout << "\n====== Report Generation ======\n";
        std::cout << "1) Generate Report #1\n";
        std::cout << "2) Generate Report #2\n";
        std::cout << "0) Return to Main Menu\n";
        std::cout << "Choose an option [0-2] and press ENTER: ";
        std::cin >> choice;

        switch (choice) {
            case 1: generateReport1(); break;
            case 2: generateReport2(); break;
            case 0: break;
            default: std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);
}

void createProduct() {
    Product newProduct;
    std::cout << "Enter the Product Name (max 30 char): ";
    std::cin.ignore();
    std::getline(std::cin, newProduct.name);

    // Check for uniqueness
    for (const auto& product : products) {
        if (product.name == newProduct.name) {
            std::cout << "Product name already exists. Please try again.\n";
            return;
        }
    }

    products.push_back(newProduct);
    std::cout << "Product " << newProduct.name << " added successfully.\n";
}

void createRelease() {
    std::string productName;
    std::cout << "Enter the Product Name (max 30 char, must pre-exist): ";
    std::cin.ignore();
    std::getline(std::cin, productName);

    // Check if product exists
    auto it = std::find_if(products.begin(), products.end(), [&](const Product& p) { return p.name == productName; });
    if (it == products.end()) {
        std::cout << "Product does not exist. Please try again.\n";
        return;
    }

    std::string releaseID, releaseDate;
    std::cout << "Enter the Release ID (max 30 char following your organizations format): ";
    std::getline(std::cin, releaseID);
    std::cout << "Enter the Release Date (YYYY-MM-DD): ";
    std::getline(std::cin, releaseDate);

    std::cout << "Release " << releaseID << " for Product " << productName << " added successfully.\n";
}

void createChangeRequest() {
    std::string profileName;
    std::cout << "Select your profile (enter name or 'new' to create a new profile): ";
    std::cin.ignore();
    std::getline(std::cin, profileName);

    if (profileName == "new") {
        User newUser;
        std::cout << "Enter the Customer Name (max 30 char): ";
        std::getline(std::cin, newUser.name);
        std::cout << "Enter the phone number of the customer (max 30 char in the format (DDD)DDD-DDDD): ";
        std::getline(std::cin, newUser.phoneNumber);
        std::cout << "Enter the email of the customer (max 30 char in the format username@email_provider.domain_type): ";
        std::getline(std::cin, newUser.email);
        std::cout << "Are you a Customer or an Employee? (C/E): ";
        std::getline(std::cin, newUser.role);
        if (newUser.role == "E") {
            std::cout << "Enter the name of the employee’s department (max 30 char): ";
            std::getline(std::cin, newUser.department);
        }
        users.push_back(newUser);
        profileName = newUser.name;
    }

    std::string productName;
    std::cout << "Select a product (must pre-exist): ";
    std::getline(std::cin, productName);

    auto it = std::find_if(products.begin(), products.end(), [&](const Product& p) { return p.name == productName; });
    if (it == products.end()) {
        std::cout << "Product does not exist. Please try again.\n";
        return;
    }

    std::string changeID, description, anticipatedReleaseID;
    std::cout << "Enter the Change ID (6 digit number): ";
    std::getline(std::cin, changeID);
    std::cout << "Enter the description for the product (max 150 char): ";
    std::getline(std::cin, description);
    std::cout << "Enter the Anticipated Release ID for the product (max 8 char): ";
    std::getline(std::cin, anticipatedReleaseID);

    ChangeItem newItem = { description, changeID, "Reported", anticipatedReleaseID };
    it->changeItems[changeID] = newItem;
    std::cout << "Change Request ID is " << changeID << ". The Change Request was successfully added.\n";
}

void queryChangeItem() {
    std::string productName;
    std::cout << "Select a product (must pre-exist): ";
    std::cin.ignore();
    std::getline(std::cin, productName);

    auto it = std::find_if(products.begin(), products.end(), [&](const Product& p) { return p.name == productName; });
    if (it == products.end()) {
        std::cout << "Product does not exist. Please try again.\n";
        return;
    }

    std::cout << "Select a Change Item of " << productName << "\n";
    for (const auto& [id, item] : it->changeItems) {
        std::cout << "ID: " << id << ", Description: " << item.description << ", State: " << item.state << ", Anticipated Release ID: " << item.anticipatedReleaseID << "\n";
    }

    std::string changeID;
    std::cout << "Enter the Change ID: ";
    std::getline(std::cin, changeID);

    auto itemIt = it->changeItems.find(changeID);
    if (itemIt == it->changeItems.end()) {
        std::cout << "Change Item does not exist. Please try again.\n";
        return;
    }

    const ChangeItem& item = itemIt->second;
    std::cout << "Product: " << productName << "\nDescription: " << item.description << "\nChange ID: " << item.changeID << "\nState: " << item.state << "\nAnticipated Release ID: " << item.anticipatedReleaseID << "\n";
}

void updateChangeItem() {
    std::string productName;
    std::cout << "Select a product (must pre-exist): ";
    std::cin.ignore();
    std::getline(std::cin, productName);

    auto it = std::find_if(products.begin(), products.end(), [&](const Product& p) { return p.name == productName; });
    if (it == products.end()) {
        std::cout << "Product does not exist. Please try again.\n";
        return;
    }

    std::cout << "Select a Change Item of " << productName << "\n";
    for (const auto& [id, item] : it->changeItems) {
        std::cout << "ID: " << id << ", Description: " << item.description << ", State: " << item.state << ", Anticipated Release ID: " << item.anticipatedReleaseID << "\n";
    }

    std::string changeID;
    std::cout << "Enter the Change ID: ";
    std::getline(std::cin, changeID);

    auto itemIt = it->changeItems.find(changeID);
    if (itemIt == it->changeItems.end()) {
        std::cout << "Change Item does not exist. Please try again.\n";
        return;
    }

    ChangeItem& item = itemIt->second;
    int updateChoice;
    do {
        std::cout << "Select what update to make to Change Item " << changeID << " of " << productName << ":\n";
        std::cout << "1) Update Description\n";
        std::cout << "2) Update State\n";
        std::cout << "3) Update Anticipated Release ID\n";
        std::cout << "0) Exit\n";
        std::cout << "Choose an option [0-3] and press ENTER: ";
        std::cin >> updateChoice;
        std::cin.ignore();

        switch (updateChoice) {
            case 1:
                std::cout << "Current description: " << item.description << "\nEnter a new description (max 150 char): ";
                std::getline(std::cin, item.description);
                break;
            case 2:
                std::cout << "Current State: " << item.state << "\nSelect the new state:\n";
                std::cout << "1) Reported\n2) Assessed\n3) InProgress\n4) Done\n5) Cancelled\n";
                int stateChoice;
                std::cin >> stateChoice;
                std::cin.ignore();
                switch (stateChoice) {
                    case 1: item.state = "Reported"; break;
                    case 2: item.state = "Assessed"; break;
                    case 3: item.state = "InProgress"; break;
                    case 4: item.state = "Done"; break;
                    case 5: item.state = "Cancelled"; break;
                    default: std::cout << "Invalid choice. No change made.\n";
                }
                break;
            case 3:
                std::cout << "Current Anticipated Release ID: " << item.anticipatedReleaseID << "\nEnter a new Anticipated Release ID (max 8 char): ";
                std::getline(std::cin, item.anticipatedReleaseID);
                break;
            case 0: break;
            default: std::cout << "Invalid choice. Please try again.\n";
        }
    } while (updateChoice != 0);

    std::cout << "Change Item updated successfully.\n";
}

void generateReport1() {
    std::string productName;
    std::cout << "Enter the product name to generate Report #1: ";
    std::cin.ignore();
    std::getline(std::cin, productName);

    auto it = std::find_if(products.begin(), products.end(), [&](const Product& p) { return p.name == productName; });
    if (it == products.end()) {
        std::cout << "Product does not exist. Please try again.\n";
        return;
    }

    std::cout << "Report #1: List of All Change Items for " << productName << " that are Not Done and Not Cancelled\n";
    for (const auto& [id, item] : it->changeItems) {
        if (item.state != "Done" && item.state != "Cancelled") {
            std::cout << "ID: " << id << ", Description: " << item.description << ", State: " << item.state << ", Anticipated Release ID: " << item.anticipatedReleaseID << "\n";
        }
    }
}

void generateReport2() {
    std::string changeID;
    std::cout << "Enter the Change ID to generate Report #2: ";
    std::cin.ignore();
    std::getline(std::cin, changeID);

    std::cout << "Report #2: List of Customers/Staff Who Need to Be Informed When a Particular Change Has Been Implemented\n";
    for (const auto& user : users) {
        std::cout << "Name: " << user.name << ", Email: " << user.email << "\n";
    }
}

void displayHelp() {
    std::cout << "Help: This system is designed to manage and track issues, such as bugs and feature requests, within a software development environment.\n";
    std::cout << "At any point, type 'Help' to receive guidance on the available options and how to use them.\n";
}
