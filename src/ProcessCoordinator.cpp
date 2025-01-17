// ============================================
// Module Name: ProcessCoordinator.cpp
// ============================================
// Version History:
// Rev. 3 - 2024/07/30 - Group 7
	// Kenneth Tan: Edited comments to match Assignment 5 requirements, implmeneted list displays for
	// each scenario, edited change ID's to generate automatically, and removed unused parameters.
// Rev. 2 - 2024/07/17 - Group 7
// Rev. 1 - 2024/07/01 - Group 7
// ============================================

// Overall internal design issues:
// This module implements ProcessCoordinator.h, following our central control design 
// from our Architectural Design Document. Specifically, it houses the implementation of s
// cenario execution as cases of a particular submenu. For example, handleProductMaintenance 
// has a case for executing Product creation and Product Release creation. Hence, it uses structures 
// exported by each of the lower-level modules (e.g., Product). Also, do-while loops are used 
// freqeuntly to ensure proper user input.

#include "ProcessCoordinator.h"
#include "Product.h"
#include "ChangeRequest.h"
#include "Report.h"
#include "Requester.h"
#include "UserInterface.h"
#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdio>  // For sprintf
#include <sstream>


// Static constants
static const int YES = 1;	// Used to confirm a decision prompt
static const int NO = 0;	// Used to reject a decision prompt
static const int CI_STRING_BUF_LEN = 6 +1;	// Used for requesting a change ID from the user

// Files
extern std::fstream productReleaseFile;

// Global variables externed
extern int globalHighestCID;

// Function Implementations
// ============================================

// General functions
// ---------------------------------------------------------
// Function: getTodaysDate
void getTodaysDate(char* dateStr, size_t size) {
	// Retrieves the current date in the format YYYYMMDD
	// Parameter: dateStr (Buffer to store the formatted date)
	// Parameter: size (Size of the buffer)

    // Get the current time
    std::time_t t = std::time(nullptr);
    std::tm* now = std::localtime(&t);

    // Format the date into the provided buffer using snprintf in YYYY-MM-DD format
    std::snprintf(dateStr, size, "%04d-%02d-%02d", now->tm_year + 1900, now->tm_mon + 1, now->tm_mday);
}

// ---------------------------------------------------------
// Function: stringToInt
bool stringToInt(const char* str, int& result) {
	// Not using "atoi" because failure output (i.e., 0) does not work with existing code
    // Check for an empty string
    if (str == nullptr || std::strlen(str) == 0) {
        return false;
    }

    // Loop by the number of characters there are in 'str' to determine
	// whether a stored character is a digit
    for (size_t i = 0; i < std::strlen(str); ++i) {
        if (!std::isdigit(str[i])) {
            return false;
        }
    }

    // Use atoi to convert the string to an integer
    result = std::atoi(str);
    return true;
}

// Display functions for Scenario 4.1
// ============================================
// ---------------------------------------------------------
// Function: confirmAddingProduct
void confirmAddingProduct() {
	// Prompts the user to confirm adding a product
	std::cout << "\nAre you sure you want to add the product (1 for Y, 0 for N)?\n";
}

// ---------------------------------------------------------
// Function: doYouWantAnotherProduct
void doYouWantAnotherProduct() {
	// Prompts the user to confirm adding another product
	std::cout << "\nDo you wish to add another product (1 for Y, 0 for N)?\n";
}

// Display functions for Scenario 4.2
// ============================================
// ---------------------------------------------------------
// Function: confirmAddingProdRel
void confirmAddingProdRel() {
	// Prompts the user to confirm adding a product release
	std::cout << "\nAre you sure you want to add this product release (1 for Y, 0 for N)?\n";
}

// ---------------------------------------------------------
// Function: doYouWantAnotherProdRel
void doYouWantAnotherProdRel() {
	// Prompts the user to confirm adding another product release
	std::cout << "\nDo you wish to add another release (1 for Y, 0 for N)?\n";
}

// Display functions for Scenario 4.3
// ============================================
// ---------------------------------------------------------
// Function: reqSearchChoice
void reqSearchChoice() {
	// Prompts the user to enter an existing requester or create a new one
	std::cout << "\nEnter '1' to enter an existing requester; enter '2' to create a new requester: " << std::endl;
}

// ---------------------------------------------------------
// Function: CIChoiceDisplay
void CIChoiceDisplay() {
	// Prompts the user to enter an existing change ID or create a new one
	std::cout << "\nEnter '1' to enter an existing change ID; enter '2' to create a new change ID: " << std::endl;
}

// ---------------------------------------------------------
// Function: CIPrompt
void CIPrompt() {
	// Prompts the user to enter a change ID
	std::cout << "\nEnter a change ID (max 6 digits, i.e., 0 to 999999):\n";
}

// ---------------------------------------------------------
// Function: confirmAddCR
void confirmAddCR() {
	// Prompts the user to confirm adding a customer request
	std::cout << "\nAre you sure you want to add a customer request?\n";
}

// ---------------------------------------------------------
// Function: repeatChangeCR
void repeatChangeCR() {
	// Prompts the user to confirm creating another change request
	std::cout << "\nDo you wish to create another Change Request? (1 for Y, 0 for N)?\n";
}

// Display functions for Scenario 4.4
// ============================================
// ---------------------------------------------------------
// Function: repeatCIQuery
void repeatCIQuery() {
	// Prompts the user to confirm querying another change item
	std::cout << "\nDo you wish to query for another Change Item (1 for Y, 0 for N)?\n";
}

// Display functions for Scenario 4.5
// ============================================
// ---------------------------------------------------------
// Function: choiceUpdateDisp
void choiceUpdateDisp() {
	// Displays the update options for a change item
	std::cout << "\nSelect what update to make to this change item:\n"
				 "1) Update Description\n"
				 "2) Update State\n"
				 "3) Update Anticipated Release ID\n"
				 "0) Exit (you will be asked to save your changes)\n";
}

// ---------------------------------------------------------
// Function: choiceSaveUpdDisp
void choiceSaveUpdDisp() {
	// Prompts the user to confirm saving the updates made to a change item
	std::cout << "\nSave the changes made to the Change Item (1 for Y, 0 for N)?" << std::endl;
}

// ---------------------------------------------------------
// Function: repeatUpdate
void repeatUpdate() {
	// Prompts the user to confirm updating another change item
	std::cout << "\nDo you wish to update another Change Item? (1 for Y, 0 for N)?\n";
}

// Display functions for Scenario 4.6
// ============================================
// ---------------------------------------------------------
// Function: repeatGen1
void repeatGen1() {
	std::cout << "\nDo you wish to generate another Report #1 (1 for Y, 0 for N)?\n";
}

// Display functions for Scenario 4.7
// ============================================
// ---------------------------------------------------------
// Function: repeatGen2
void repeatGen2() {
	std::cout << "\nDo you wish to generate another Report #2 (1 for Y, 0 for N)?\n";
}

// Functions for Executing Scenarios
// ============================================
// ---------------------------------------------------------
// Function: handleProductMaintenance
void handleProductMaintenance(int choice) {
	// Handles the product maintenance scenarios
	// Parameter: choice (The chosen scenario for product maintenance)
    int choiceConfirmAdd;
	int choiceRepeat;
    switch (choice) {
        case 1: {
			bool repeat = false;
			// Loop while repeat equals 'true.'
			do
			{
				// Scenario 4.1: Creating a Product - duplication prevention logic not implemented
				char productName[PRODUCT_NAME_LENGTH];
				Product tmpProd;
				int notProperLen;
				int exists;

				// Product name read
				// Loop while the product name entered is not of the proper lenght or
				// already exists
				do {
					std::cout << "\nCreate a product by entering its name (max 10 char, must pre-exist): \n";
					std::cin.getline(productName, PRODUCT_NAME_LENGTH);

					// Check if input length is valid
					if (std::cin.fail()) {
						std::cin.clear(); // Clear the fail state
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
						std::cout << "Invalid input. Please enter 1 to 10 characters." << std::endl;
						notProperLen = true; // Continue the loop
						exists = false; // Reset exists flag
					} else if (strlen(productName) == 0) {
						std::cout << "Product name cannot be empty. Please enter 1 to 10 characters." << std::endl;
						notProperLen = true; // Continue the loop
						exists = false; // Reset exists flag
					} else {
						// Check if the product already exists
						exists = retrieveProductByName(productName, tmpProd);
						if (exists) {
							std::cout << "The product already exists!" << std::endl;
						}
						notProperLen = false; // Exit the loop if both conditions are false
					}
				} while (notProperLen || exists);

				// Final choices
				choiceConfirmAdd = readIntegerInput(confirmAddingProduct,NO,YES);
				if (choiceConfirmAdd == YES) {
					createProduct(productName);
					choiceRepeat = readIntegerInput(doYouWantAnotherProduct,NO,YES);
					if (choiceRepeat == YES) {
						repeat = true;
					} else {
						break;
					}
				} else {
					break;
				}
			} while (repeat);
			break;
        }
        case 2: {
			// Scenario 4.2: Creating a Release of a Product - duplication prevention logic not implemented
            char productName[PRODUCT_NAME_LENGTH], releaseID[RELEASE_ID_LENGTH], releaseDate[RELEASE_DATE_LENGTH];
            
			bool repeat = false;
			
			// Loop while repeat equals 'true.'
			do
			{
				Product tmpProd;
				ProductRelease tmpRel;
				int notProperLen;
				int notExists;
				bool ifUniqueProdRel;
				int productPage = 1;
				// Flags
				bool exitFlag = false;
				
				// Loop while the compound key of the product release being created is not unique
				do {
					// Loop while the entered product is not of the proper length or does not exist.
					// Also, loop while the entered input is for navigating the display (i.e., '<' or '>')
					do {
						productFileDisplay20OrLess(productPage);
						std::cout << "Enter the product for the product release (max 10 char, must pre-exist): \n";
						std::cin.getline(productName, PRODUCT_NAME_LENGTH);

						// Check if input length is valid
						if (std::strcmp(productName,"Exit") == 0) {
							exitFlag = true;
							break;
						} else if (std::strcmp(productName,"<") == 0) {
							productPage--;
						} else if (std::strcmp(productName,">") == 0) {
							productPage++;
						} else if (std::cin.fail()) {
							std::cin.clear(); // Clear the fail state
							std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
							std::cout << "Invalid input. Please enter 1 to 10 characters." << std::endl;
							notProperLen = true; // Continue the loop
							notExists = false; // Reset notExists flag
						} else if (strlen(productName) == 0) {
							std::cout << "Product field cannot be empty. Please enter 1 to 10 characters." << std::endl;
							notProperLen = true; // Continue the loop
							notExists = false; // Reset notExists flag
						} else {
							// Check if the product exists
							notExists = !retrieveProductByName(productName, tmpProd);
							if (notExists) {
								std::cout << "The product must exist!" << std::endl;
							}
							notProperLen = false; // Exit the loop if both conditions are false
						}
					} while (notProperLen || notExists || (std::strcmp(productName,"<") == 0) || (std::strcmp(productName,">") == 0));
					if (exitFlag) break;

					// Get a product release ID
					// Loop while the entered release ID is not the proper length
					do {
						std::cout << "\nEnter the Release ID (max 8 char following your organization's format): \n";
						std::cin.getline(releaseID, RELEASE_ID_LENGTH);

						// Check if input length is valid
						if (std::cin.fail()) {
							std::cin.clear(); // Clear the fail state
							std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
							std::cout << "Invalid input. Please enter 1 to 8 characters." << std::endl;
							notProperLen = true;
						} else {
							// Check if input is empty (0 characters)
							notProperLen = strlen(releaseID) == 0;
							if (notProperLen) {
								std::cout << "Input cannot be empty. Please enter 1 to 8 characters." << std::endl;
							}
						}
					} while (notProperLen);

					// Check for uniquenes by product release ID
					ifUniqueProdRel = retrieveProductReleaseByKey(productName, releaseID, tmpRel);
					if (ifUniqueProdRel)
					{
						std::cout << "You must enter a product release that has a unique compound primary key " 
						"(i.e., unique combination of product name and release ID).\n";
					}
				} while (ifUniqueProdRel);
				if (exitFlag) break;			

				// Get a release date
				// Loop while the entered release dat is not the proper length
				do {
					std::cout << "\nEnter the release date (YYYY-MM-DD): \n";
					std::cin.getline(releaseDate, RELEASE_DATE_LENGTH);

					notProperLen = std::cin.fail() || (strlen(releaseDate) != (RELEASE_DATE_LENGTH-1));

					if (notProperLen) {
						std::cin.clear(); // Clear the fail state
						std::cout << "The release date must be 10 characters!" << std::endl;
					}
				} while (notProperLen);

				// Final choices
				choiceConfirmAdd = readIntegerInput(confirmAddingProdRel,NO,YES);
				if (choiceConfirmAdd == YES) {
					createProductRelease(productName,releaseID,releaseDate);
					choiceRepeat = readIntegerInput(doYouWantAnotherProdRel,NO,YES);
					if (choiceRepeat == YES) {
						repeat = true;
					} else {
						break;
					}
				} else {
					break;
				}			
			} while (repeat);
			break;
        }
        default: 
            std::cout << "Invalid choice. Please try again.\n";
    }
}

// ---------------------------------------------------------
// Function: handleChangeRequestMaintenance
void handleChangeRequestMaintenance(int choice) {
	// Handles the change request maintenance scenarios
	// Parameter: choice (The chosen scenario for change request maintenance)
	static const int ENTER_REQ = 1;
	static const int CREATE_REQ = 2;

	static const int ENTER_CI = 1;
	static const int CREATE_CI = 2;

    switch (choice) {
        case 1: {
			// Scenario 4.3: Create Change Request
			
			// Variables
			// Scenario-wide
			bool repeat = false;
			int choiceConfirmAdd;
			int choiceRepeat;
			
			// User input storage
			// New requester (requester used for change request)
			char requester[REQ_NAME_LENGTH], phoneNum[PHONE_NUMBER_LENGTH], email[EMAIL_LENGTH], department[DEPARTMENT_LENGTH];
			// New change item (change ID used for change request)
			int changeID;	
			char productName[PRODUCT_NAME_LENGTH], description[CHANGE_DESC_LENGTH], anticipatedReleaseID[RELEASE_ID_LENGTH], state[STATE_LENGTH] = "Reported";
			// New change request
			char date[REP_DATE_LENGTH], reportedRelease[RELEASE_ID_LENGTH], priority[PRIORITY_LENGTH];

			// Requester selection
			int reqChoice;
			Requester tmpRequester;
			// Enter requester 
			int requesterPage = 1;  // (always start display on requesterPage 1)
			int ERnotExists;
			int ERnotProperLen;
			// Create requester
			int CRnotProperLen;
			int CRexists;

			// Product selction
			Product tmpProd;
			int PnotExists;
			int PnotProperLen;
			int productPage = 1;

			// ChangeItem selection
			ChangeItem tmpCI;
			ProductRelease tmpPR;
			bool isNumber = false;
			int CIPage = 1;
			char CIStringBuf[CI_STRING_BUF_LEN];
			int CIChoice;
			int CInotExists;
			int CInotProperLen;
			int releaseIDExists;
			int CIOfProductExists;
			int ARPage = 1;

			// Release ID selection
			int RIDExists;
			int RIDnotProperLen;
			int RRPage = 1;

			// Priority selection
			int PriorityNotProperLen;

			// Change request duplicate check
			ChangeRequest tmpCR;

			// Flags
			bool exitFlag = false;
			bool duplicateFlag = false;

		
			// For repeat choice
			// Loop while repeat equals 'true.'
			do {
				// Loop while the entered compound primary key of the change request is a duplicate
				do {
					// Get a requester name
					reqChoice = readIntegerInput(reqSearchChoice,1,2);
					if (reqChoice == ENTER_REQ) {
						// Loop while the entered requester is not the proper length or does not exist
						// Also, loop if the entered input is for navigation (i.e., '<' or '>')
						do {
							requesterFileDisplay20OrLess(requesterPage);
							std::cout << "Select a requester by entering their name (max 30 char, must pre-exist): \n"; // Change the input options
							std::cin.getline(requester, REQ_NAME_LENGTH);

							// Check for navigation input
							if (std::strcmp(requester,"Exit") == 0) {
								exitFlag = true;
								break;
							} else if (std::strcmp(requester,"<") == 0) {
								requesterPage--;
							} else if (std::strcmp(requester,">") == 0) {
								requesterPage++;
							} else if (std::cin.fail()) {
								// Check if input length is valid
								std::cin.clear(); // Clear the fail state
								std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
								std::cout << "Invalid input. Please enter 1 to 30 characters." << std::endl;
								ERnotProperLen = true; // Continue the loop
								ERnotExists = false; // Reset ERnotExists flag
							} else if (strlen(requester) == 0) {
								// Check if input length is valid
								std::cout << "Requester name cannot be empty. Please enter 1 to 30 characters." << std::endl;
								ERnotProperLen = true; // Continue the loop
								ERnotExists = false; // Reset ERnotExists flag
							} else {
								// Check if the requester exists
								ERnotExists = !retrieveRequesterByKey(requester, tmpRequester);
								if (ERnotExists) {
									std::cout << "The Requester must exist!" << std::endl;
								}
								ERnotProperLen = false; // Exit the loop if both conditions are false
							}
						} while (ERnotProperLen || ERnotExists || (std::strcmp(requester,"<") == 0) || (std::strcmp(requester,">") == 0));
						if (exitFlag) break;
					} else if (reqChoice == CREATE_REQ) {
						// Get requester name
						// Loop while the entered requester name is not the proper length or already exists
						do {
							std::cout << "\nEnter the requester name (max 30 char, must not exist): \n";
							std::cin.getline(requester, REQ_NAME_LENGTH);

							// Check if input length is valid
							if (std::cin.fail()) {
								std::cin.clear(); // Clear the fail state
								std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
								std::cout << "Invalid input. Please enter 1 to 30 characters." << std::endl;
								CRnotProperLen = true; // Continue the loop
								CRexists = false; // Reset CRexists flag
							} else if (strlen(requester) == 0) {
								std::cout << "Requester name cannot be empty. Please enter 1 to 30 characters." << std::endl;
								CRnotProperLen = true; // Continue the loop
								CRexists = false; // Reset CRexists flag
							} else {
								// Check if the requester already exists
								CRexists = retrieveRequesterByKey(requester, tmpRequester);
								if (CRexists) {
									std::cout << "The requester already exists!" << std::endl;
								}
								CRnotProperLen = false; // Exit the loop if both conditions are false
							}
						} while (CRnotProperLen || CRexists);

						// Get phone number
						// Loop while the entered phone number is not of the proper length
						do {
							std::cout << "\nEnter your phone number (11 digits in the format DDDDDDDDDDD): \n";
							std::cin.getline(phoneNum, PHONE_NUMBER_LENGTH);

							// Check if input length is valid
							if (std::cin.fail()) {
								std::cin.clear(); // Clear the fail state
								std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
								std::cout << "Invalid input. Please enter 11 digits." << std::endl;
								CRnotProperLen = true; // Continue the loop
							} else if (strlen(phoneNum) < (PHONE_NUMBER_LENGTH-1)) {	// Since phone number length accounts for \0
								std::cout << "Phone number cannot be less than 11 digits. Please enter 11 digits." << std::endl;
								CRnotProperLen = true; // Continue the loop
							} else {
								CRnotProperLen = false;
							}
						} while (CRnotProperLen);

						// Get email
						// Loop while the entered email is not of the proper length
						do {
							std::cout << "\nEnter the email of the customer (max 24 char in the format "
										"username@email_provider.domain_type):\n";
							std::cin.getline(email, EMAIL_LENGTH);

							// Check if input length is valid
							if (std::cin.fail()) {
								std::cin.clear(); // Clear the fail state
								std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
								std::cout << "Invalid input. Please enter 1 to 24 characters." << std::endl;
								CRnotProperLen = true; // Continue the loop
							} else if (strlen(email) == 0) {
								std::cout << "Email cannot be empty. Please enter 1 to 24 characters." << std::endl;
								CRnotProperLen = true; // Continue the loop
							} else {
								CRnotProperLen = false;
							}
						} while (CRnotProperLen);

						// Get department
						// Loop while the entered department is improper in length
						do {
							std::cout << "\nIf you are an employee, enter your department (max 12 char).\n"
										 "If this is not applicable to you, enter 'N/A':\n";
							std::cin.getline(department, DEPARTMENT_LENGTH);

							// Check if input length is valid
							if (std::cin.fail()) {
								std::cin.clear(); // Clear the fail state
								std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
								std::cout << "Invalid input. Please enter 1 to 12 characters." << std::endl;
								CRnotProperLen = true; // Continue the loop
							} else if (strlen(department) == 0) {
								std::cout << "Department cannot be empty. Please enter 1 to 12 characters." << std::endl;
								CRnotProperLen = true; // Continue the loop
							} else {
								CRnotProperLen = false;
							}
						} while (CRnotProperLen);		

						// Create new requester
						createRequester(requester,phoneNum,email,department);
						std::cout << "Requester successfully created" << std::endl;
					}

					// Select a product
					// Loop while the entered product is not of the proper length or does not exist.
					// Also, loop if the entered input is for navigation (i.e., '<' or '>')
					do {
						productFileDisplay20OrLess(productPage);
						std::cout << "Select a product by entering its name (max 10 char, must pre-exist): \n";
						std::cin.getline(productName, PRODUCT_NAME_LENGTH);

						// Check if input length is valid
						if (std::strcmp(productName,"Exit") == 0) {
							exitFlag = true;
							break;
						} else if (std::strcmp(productName,"<") == 0) {
							productPage--;
						} else if (std::strcmp(productName,">") == 0) {
							productPage++;
						} else if (std::cin.fail()) {
							std::cin.clear(); // Clear the fail state
							std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
							std::cout << "Invalid input. Please enter 1 to 10 characters." << std::endl;
							PnotProperLen = true; // Continue the loop
							PnotExists = false; // Reset PnotExists flag
						} else if (strlen(productName) == 0) {
							std::cout << "Product name cannot be empty. Please enter 1 to 10 characters." << std::endl;
							PnotProperLen = true; // Continue the loop
							PnotExists = false; // Reset PnotExists flag
						} else {
							// Check if the product exists
							PnotExists = !retrieveProductByName(productName, tmpProd);
							if (PnotExists) {
								std::cout << "The product must exist!" << std::endl;
							}
							PnotProperLen = false; // Exit the loop if both conditions are false
						}
					} while (PnotProperLen || PnotExists || (std::strcmp(productName,"<") == 0) || (std::strcmp(productName,">") == 0));
					if (exitFlag) break;

					// Change item
					CIChoice = readIntegerInput(CIChoiceDisplay,ENTER_CI,CREATE_CI);

					if (CIChoice == ENTER_CI) // Enter existing change ID
					{
						// Loop while the change ID is not of the proper length, does not exist, is not a number, 
						// or an existing change ID is not for the previously-selected product
						// Also, loop if the entered input is for navigation (i.e., '<' or '>')
						do {
							changeItemFileDisplay20OrLess(CIPage,productName);
							std::cout << "Enter an existing change ID (change item) of the product you chose [0-999999]: \n";
							std::cin.getline(CIStringBuf, CI_STRING_BUF_LEN);

							// Check if input length is valid
							if (std::strcmp(CIStringBuf,"Exit") == 0) {
								exitFlag = true;
								break;
							} else if (std::strcmp(CIStringBuf,"<") == 0) {
								CIPage--;
							} else if (std::strcmp(CIStringBuf,">") == 0) {
								CIPage++;
							} else if (std::cin.fail()) {
								std::cin.clear(); // Clear the fail state
								std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
								std::cout << "Invalid input. Please enter 1 to 6 digits." << std::endl;
								CInotProperLen = true; // Continue the loop
								CInotExists = false; // Reset CInotExists flag
							} else if (strlen(CIStringBuf) == 0) {
								std::cout << "Change ID cannot be empty. Please enter 1 to 6 digits." << std::endl;
								CInotProperLen = true; // Continue the loop
								CInotExists = false; // Reset CInotExists flag
							} else {
								// Check if the change item exists

								isNumber = stringToInt(CIStringBuf,changeID);
								CInotExists = !retrieveChangeItemByKey(changeID,tmpCI);
								if (!isNumber) {
									// Check if the string is a number
									std::cout << "The change ID must be a number!" << std::endl;
								} else if (CInotExists) {
									std::cout << "The change ID must exist!" << std::endl;
								} else {
									// Check if change items exists for the specified product
									CInotExists = false;
									CIOfProductExists = retrieveChangeItemByKeyAndProduct(changeID,tmpCI,productName);
									if (!CIOfProductExists)
									{
										std::cout << "The change item must have your selected change ID 'and' product name.\n";
									}
								}
								CInotProperLen = false; // Exit the loop if both conditions are false
							}
							// If the change item is for the chosen product and is a number between 0-999999
						} while (CInotProperLen || CInotExists || (!CIOfProductExists) || 
								(std::strcmp(CIStringBuf,"<") == 0) || (std::strcmp(CIStringBuf,">") == 0) || 
								(!isNumber));
						if (exitFlag) break;
					} else if (CIChoice == CREATE_CI) { // Create change ID
						// Store new change ID
						changeID = globalHighestCID + 1;

						// Enter description for change item
						// Loop while the description is not of the proper length
						do {
							std::cout << "\nEnter the description for the change item (max 30 char): \n";
							std::cin.getline(description, CHANGE_DESC_LENGTH);

							// Check if input length is valid
							if (std::cin.fail()) {
								std::cin.clear(); // Clear the fail state
								std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
								std::cout << "Invalid input. Please enter 1 to 30 characters." << std::endl;
								CInotProperLen = true; // Continue the loop
							} else if (strlen(description) == 0) {
								std::cout << "Description cannot be empty. Please enter 1 to 30 characters." << std::endl;
								CInotProperLen = true; // Continue the loop
							} else {
								CInotProperLen = false;
							}
						} while (CInotProperLen);

						// Enter an anticipated release ID
						// Loop while the entered anticipated release ID is improper in length or does not exist in a product release
						// Also, loop if the entered input is for navigation (i.e., '<' or '>')
						do {
							productReleaseFileDisplay20OrLess(ARPage,productName);
							std::cout << "Enter the anticipated release ID for your change item (max 8 char):\n";
							std::cin.getline(anticipatedReleaseID, RELEASE_ID_LENGTH);

							// Check if input length is valid
							if (strcmp(anticipatedReleaseID,"Exit") == 0) {
								exitFlag = true;
								break;
							} else if (std::strcmp(anticipatedReleaseID,"<") == 0) {
								ARPage--;
							} else if (std::strcmp(anticipatedReleaseID,">") == 0) {
								ARPage++;
							} else if (std::cin.fail()) {
								std::cin.clear(); // Clear the fail state
								std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
								std::cout << "Invalid input. Please enter 1 to 8 characters." << std::endl;
								CInotProperLen = true; // Continue the loop
							} else if (strlen(anticipatedReleaseID) == 0) {
								std::cout << "Release ID cannot be empty. Please enter 1 to 8 characters." << std::endl;
								CInotProperLen = true; // Continue the loop

							} else {
								CInotProperLen = false;
								// After verifying the input length, check if this release ID exists
								releaseIDExists = retrieveProductReleaseByKey(productName,anticipatedReleaseID,tmpPR);
								if (!releaseIDExists)
								{
									std::cout << "You must enter a release ID, of the chosen product, that exists (i.e., is used in a product release)\n";
								}
							}
						} while (CInotProperLen || (!releaseIDExists) || 
								 (std::strcmp(anticipatedReleaseID,"<") == 0) || (std::strcmp(anticipatedReleaseID,">") == 0));
						if (exitFlag) break;

						// (The state of a change item when created is always "Reported")	

						// Create the new change ID
						createChangeItem(changeID,productName,description,anticipatedReleaseID,state);
						std::cout << "Change item successfully created" << std::endl;
					}
					if (exitFlag) break;

					// Check if the change request being made is a duplicate
					if (retrieveChangeRequestByKey(requester,changeID,tmpCR)) {
						std::cout << "The change request you create cannot already exist "
									 "(i.e., match with an existing change reqeust's requester name and change ID)!" << std::endl << std::endl;
						duplicateFlag = true;
					} else {
						duplicateFlag = false;
					}
				} while (duplicateFlag);
				if (exitFlag) break;

				// Ask for a release ID
				// Loop while the release ID is improper in length or does not exist
				// Also, loop if the entered input is for navigation (i.e., '<' or '>')
				do {
					productReleaseFileDisplay20OrLess(RRPage,productName);
					std::cout << "Enter the reported release ID for the change request (max 8 char): \n";
					std::cin.getline(reportedRelease, RELEASE_ID_LENGTH);

					// Check if input length is valid
					if (strcmp(reportedRelease,"Exit") == 0) {
						exitFlag = true;
						break;
					} else if (std::strcmp(reportedRelease,"<") == 0) {
						RRPage--;
					} else if (std::strcmp(reportedRelease,">") == 0) {
						RRPage++;
					} else if (std::cin.fail()) {
						std::cin.clear(); // Clear the fail state
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
						std::cout << "Invalid input. Please enter 1 to 8 characters." << std::endl;
						RIDnotProperLen = true; // Continue the loop
					} else if (strlen(reportedRelease) == 0) {
						std::cout << "Reported release ID cannot be empty. Please enter 1 to 8 characters." << std::endl;
						RIDnotProperLen = true; // Continue the loop

					} else {
						RIDnotProperLen = false;
						// After verifying the input length, check if this release ID exists
						RIDExists = retrieveProductReleaseByKey(productName,reportedRelease,tmpPR);
						if (!RIDExists)
						{
							std::cout << "You must enter a release ID, of the chosen product, that exists (i.e., is used in a product release)\n";
						}
					}
				} while (RIDnotProperLen || (!RIDExists) || 
							(std::strcmp(reportedRelease,"<") == 0) || (std::strcmp(reportedRelease,">") == 0));
				if (exitFlag) break;
			
				// Ask for a Priority
				// Loop while the entered priority is not of the proper length
				do {
					std::cout << "\nEnter the change request's priority (1 to 5, with 5 being the highest; max 1 digit):\n";
					std::cin.getline(priority, PRIORITY_LENGTH);

					// Check if input length is valid
					if (std::cin.fail()) {
						std::cin.clear(); // Clear the fail priority
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
						std::cout << "Invalid input. Please enter exactly 1 digit." << std::endl;
						PriorityNotProperLen = true; // Continue the loop
					} else if (strlen(priority) == 0) {
						std::cout << "Priority cannot be empty. Please enter exactly 1 digit." << std::endl;
						PriorityNotProperLen = true; // Continue the loop
					} else {
						PriorityNotProperLen = false;
					}
				} while (PriorityNotProperLen);

				// Final choices
				choiceConfirmAdd = readIntegerInput(confirmAddCR,NO,YES);
				if (choiceConfirmAdd == YES) {
					getTodaysDate(date, sizeof(date));
					createChangeRequest(requester,changeID,reportedRelease,date,priority);
					std::cout << "Your change request’s change ID is " << changeID << "." << std::endl;
					std::cout << "The change request was successfully created." << std::endl;
					choiceRepeat = readIntegerInput(repeatChangeCR,NO,YES);
					if (choiceRepeat == YES) {
						repeat = true;
					} else {
						break;
					}
				} else {
					break;
				}	
			} while (repeat);
			break;
        }
        default: 
            std::cout << "Invalid choice. Please try again.\n";
    }
}

// ---------------------------------------------------------
// Function: handleChangeItemMaintenance
void handleChangeItemMaintenance(int choice) {
	// Handles the change item maintenance scenarios
	// Parameter: choice (The chosen scenario for change item maintenance)
    switch (choice) {
        case 1: {
			// Scenario 4.4: Querying Change Items

			// Variables
			// General
			bool repeat;
			int choiceRepeat;
			// Storage
            char productName[PRODUCT_NAME_LENGTH];
			int changeID;
			// Get an existing product
			Product tmpProd;
			int productPage = 1;
			int PnotProperLen;
			int PnotExists;
			// Get a change item based on product
			ChangeItem tmpCI;
			int CIPage = 1;
			char CIStringBuf[CI_STRING_BUF_LEN];
			bool isNumber;
			int CInotExists;
			int CInotProperLen;
			int CIOfProductExists;
			// Flags
			bool exitFlag = false;

			// For repeating the scenario
			// Loop while the user wants to repeat the scenario (i.e., 'repeat' evaluates to true)
			do {
				// Loop while the entered product name is improper in length or does not exist
				// Also, loop if the entered input is for navigation (i.e., '<' or '>')
				do {
					productFileDisplay20OrLess(productPage);
					std::cout << "Select the product your change item is for by entering its name (max 10 char, must " 
								 "pre-exist):\n";
					std::cin.getline(productName, PRODUCT_NAME_LENGTH);

					// Check if input length is valid
					if (strcmp(productName,"Exit") == 0) {
						exitFlag = true;
						break;
					} else if (std::strcmp(productName,"<") == 0) {
						productPage--;
					} else if (std::strcmp(productName,">") == 0) {
						productPage++;
					} else if (std::cin.fail()) {
						std::cin.clear(); // Clear the fail state
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
						std::cout << "Invalid input. Please enter 1 to 10 characters." << std::endl;
						PnotProperLen = true; // Continue the loop
						PnotExists = false; // Reset PnotExists flag
					} else if (strlen(productName) == 0) {
						std::cout << "Product name cannot be empty. Please enter 1 to 10 characters." << std::endl;
						PnotProperLen = true; // Continue the loop
						PnotExists = false; // Reset PnotExists flag
					} else {
						// Check if the product exists
						PnotExists = !retrieveProductByName(productName, tmpProd);
						if (PnotExists) {
							std::cout << "The product must exist!" << std::endl;
						}
						PnotProperLen = false; // Exit the loop if both conditions are false
					}
				} while (PnotProperLen || PnotExists || (std::strcmp(productName,"<") == 0) || (std::strcmp(productName,">") == 0));
				if (exitFlag) break;

				// Get the change ID based on product choice
				// Loop while the entered change ID is improper in length, does not exist, or has a change item that does not
				// store the previously-selected product as an attribute
				// Also, loop if the entered input is for navigation (i.e., '<' or '>')
				do {
					changeItemFileDisplay20OrLess(CIPage,productName);
					std::cout << "Enter an existing change ID (change item) of the product you chose [0-999999]: \n";
					std::cin.getline(CIStringBuf, CI_STRING_BUF_LEN);

					// Check if input length is valid
					if (strcmp(CIStringBuf,"Exit") == 0) {
						exitFlag = true;
						break;
					} else if (std::strcmp(CIStringBuf,"<") == 0) {
						CIPage--;
					} else if (std::strcmp(CIStringBuf,">") == 0) {
						CIPage++;
					} else if (std::cin.fail()) {
						std::cin.clear(); // Clear the fail state
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
						std::cout << "Invalid input. Please enter 1 to 6 digits." << std::endl;
						CInotProperLen = true; // Continue the loop
						CInotExists = false; // Reset CInotExists flag
					} else if (strlen(CIStringBuf) == 0) {
						std::cout << "Change ID cannot be empty. Please enter 1 to 6 digits." << std::endl;
						CInotProperLen = true; // Continue the loop
						CInotExists = false; // Reset CInotExists flag
					} else {
						// Check if the change item exists

						isNumber = stringToInt(CIStringBuf,changeID);
						CInotExists = !retrieveChangeItemByKey(changeID,tmpCI);
						if (!isNumber) {
							// Check if the string is a number
							std::cout << "The change ID must be a number!" << std::endl;
						} else if (CInotExists) {
							std::cout << "The change ID must exist!" << std::endl;
						} else {
							// Check if change items exists for the specified product
							CInotExists = false;
							CIOfProductExists = retrieveChangeItemByKeyAndProduct(changeID,tmpCI,productName);
							if (!CIOfProductExists)
							{
								std::cout << "The change item must have your selected change ID 'and' product name.\n";
							}
						}
						CInotProperLen = false; // Exit the loop if both conditions are false
					}
					// If the change item is for the chosen product and is a number between 0-999999
				} while (CInotProperLen || CInotExists || (!CIOfProductExists) || 
							(std::strcmp(CIStringBuf,"<") == 0) || (std::strcmp(CIStringBuf,">") == 0) || 
							(!isNumber));
				if (exitFlag) break;

				// Print the information of the product's change item
				std::cout << std::endl;
				std::cout << std::setw(25) << std::left << "Product:" << tmpCI.productName << std::endl;
				std::cout << std::setw(25) << std::left << "Description:" << tmpCI.description << std::endl;
				std::cout << std::setw(25) << std::left << "Change ID:" << std::to_string(changeID) << std::endl;
				std::cout << std::setw(25) << std::left << "State:" << tmpCI.state << std::endl;
				std::cout << std::setw(25) << std::left << "Anticipated Release ID:" << tmpCI.anticipatedReleaseID << std::endl;

				// Final choices
				choiceRepeat = readIntegerInput(repeatCIQuery,NO,YES);
				if (choiceRepeat == YES) {
					repeat = true;
				} else {
					repeat = false;
				}
			} while (repeat);

            break;
        }
        case 2: {
			// Scenario 4.5: Update/Assess Change Item

			// Variables
			// General
			bool repeat;
			int choiceRepeat;
			// Storage
            char productName[PRODUCT_NAME_LENGTH];
			int changeID;
			// Get an existing product
			Product tmpProd;
			int productPage = 1;
			int PnotProperLen;
			int PnotExists;
			// Get a change item based on product
			ChangeItem tmpCI;
			char CIStringBuf[CI_STRING_BUF_LEN];
			int CIPage = 1;
			bool isNumber;
			int CInotExists;
			int CIOfProductExists;
			// Deciding what update to make
			int choiceUpdate;
			// Description update
			char description[CHANGE_DESC_LENGTH];
			int CInotProperLen;
			// State update
			char state[STATE_LENGTH];
			// Anticipated release ID update
			ProductRelease tmpPR;
			char anticipatedReleaseID[RELEASE_ID_LENGTH];
			int releaseIDExists;
			int RRPage = 1;
			int RIDnotProperLen;
			// Save updates choice
			int choiceSaveUpdates;
			int origChangeID;
			// Flags
			bool exitFlag = false;

			// Loop while the user wants to repeat the scenario (i.e., 'repeat' evaluates to true)
			do {
				// Loop while the entered product is improper in length or does not exist
				// Also, loop if the entered input is for navigation (i.e., '<' or '>')
				do {
					productFileDisplay20OrLess(productPage);
					std::cout << "Select the product your change item is for by entering its name (max 10 char, must " 
								 "pre-exist):\n";
					std::cin.getline(productName, PRODUCT_NAME_LENGTH);

					// Check if input length is valid
					if (strcmp(productName,"Exit") == 0) {
						exitFlag = true;
						break;
					} else if (std::strcmp(productName,"<") == 0) {
						productPage--;
					} else if (std::strcmp(productName,">") == 0) {
						productPage++;
					} else if (std::cin.fail()) {
						std::cin.clear(); // Clear the fail state
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
						std::cout << "Invalid input. Please enter 1 to 10 characters." << std::endl;
						PnotProperLen = true; // Continue the loop
						PnotExists = false; // Reset PnotExists flag
					} else if (strlen(productName) == 0) {
						std::cout << "Product name cannot be empty. Please enter 1 to 10 characters." << std::endl;
						PnotProperLen = true; // Continue the loop
						PnotExists = false; // Reset PnotExists flag
					} else {
						// Check if the product exists
						PnotExists = !retrieveProductByName(productName, tmpProd);
						if (PnotExists) {
							std::cout << "The product must exist!" << std::endl;
						}
						PnotProperLen = false; // Exit the loop if both conditions are false
					}
				} while (PnotProperLen || PnotExists || (std::strcmp(productName,"<") == 0) || (std::strcmp(productName,">") == 0));
				if (exitFlag) break;

				// Get the change ID based on product choice
				// Loop while the change ID is not of the proper length, does not exist, is not a number, 
				// or an existing change ID is not for the previously-selected product
				// Also, loop if the entered input is for navigation (i.e., '<' or '>')
				do {
					changeItemFileDisplay20OrLess(CIPage,productName);
					std::cout << "Enter an existing change ID (change item) of the product you chose [0-999999]: \n";
					std::cin.getline(CIStringBuf, CI_STRING_BUF_LEN);

					// Check if input length is valid
					if (strcmp(CIStringBuf,"Exit") == 0) {
						exitFlag = true;
						break;
					} else if (std::strcmp(CIStringBuf,"<") == 0) {
						CIPage--;
					} else if (std::strcmp(CIStringBuf,">") == 0) {
						CIPage++;
					} else if (std::cin.fail()) {
						std::cin.clear(); // Clear the fail state
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
						std::cout << "Invalid input. Please enter 1 to 6 digits." << std::endl;
						CInotProperLen = true; // Continue the loop
						CInotExists = false; // Reset CInotExists flag
					} else if (strlen(CIStringBuf) == 0) {
						std::cout << "Change ID cannot be empty. Please enter 1 to 6 digits." << std::endl;
						CInotProperLen = true; // Continue the loop
						CInotExists = false; // Reset CInotExists flag
					} else {
						// Check if the change item exists

						isNumber = stringToInt(CIStringBuf,changeID);
						CInotExists = !retrieveChangeItemByKey(changeID,tmpCI);
						if (!isNumber) {
							// Check if the string is a number
							std::cout << "The change ID must be a number!" << std::endl;
						} else if (CInotExists) {
							std::cout << "The change ID must exist!" << std::endl;
						} else {
							// Check if change items exists for the specified product
							CInotExists = false;
							CIOfProductExists = retrieveChangeItemByKeyAndProduct(changeID,tmpCI,productName);
							if (!CIOfProductExists)
							{
								std::cout << "The change item must have your selected change ID 'and' product name.\n";
							}
						}
						CInotProperLen = false; // Exit the loop if both conditions are false
					}
					// If the change item is for the chosen product and is a number between 0-999999
				} while (CInotProperLen || CInotExists || (!CIOfProductExists) || 
							(std::strcmp(CIStringBuf,"<") == 0) || (std::strcmp(CIStringBuf,">") == 0) || 
							(!isNumber));
				if (exitFlag) break;

				// Store the original change ID (for overwriting)
				origChangeID = tmpCI.changeID;

				// Select what update to make
				// Loop while the user has not decided to exit from making updates to their selected change item
				// (i.e., entered '0')
				do {
					choiceUpdate = readIntegerInput(choiceUpdateDisp,0,3);
					switch (choiceUpdate) {
						case 1: { // Description
							// Enter description for change item
							// Loop while the description is improper in length
							do {
								std::cout << "\nCurrent description: " << tmpCI.description;
								std::cout << "\nEnter the new description for the change item (max 30 char): \n";
								std::cin.getline(description, CHANGE_DESC_LENGTH);

								// Check if input length is valid
								if (std::cin.fail()) {
									std::cin.clear(); // Clear the fail state
									std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
									std::cout << "Invalid input. Please enter 1 to 30 characters." << std::endl;
									CInotProperLen = true; // Continue the loop
								} else if (strlen(description) == 0) {
									std::cout << "Description cannot be empty. Please enter 1 to 30 characters." << std::endl;
									CInotProperLen = true; // Continue the loop
								} else {
									CInotProperLen = false;
								}
							} while (CInotProperLen);

							// Store for updating
							std::strcpy(tmpCI.description,description);
							break;
						}
						case 2: { // State
							// Loop while the entered state is improper in length
							do {
								std::cout << "\nCurrent state: " << tmpCI.state << std::endl;
								std::cout << "Options for state include: 'Reported', 'Assessed', 'InProgress', 'Done', and 'Cancelled'." << std::endl;
								std::cout << "Enter the new state of the change item (max 10 char):\n";
								std::cin.getline(state, STATE_LENGTH);

								// Check if input length is valid
								if (std::cin.fail()) {
									std::cin.clear(); // Clear the fail state
									std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
									std::cout << "Invalid input. Please enter 1 to 10 characters." << std::endl;
									CInotProperLen = true; // Continue the loop
								} else if (strlen(state) == 0) {
									std::cout << "Email cannot be empty. Please enter 1 to 10 characters." << std::endl;
									CInotProperLen = true; // Continue the loop
								} else {
									CInotProperLen = false;
								}
							} while (CInotProperLen);

							// Store for updating
							std::strcpy(tmpCI.state,state);
							break;
						}
						case 3: { // Anticipated release ID
							// Ask for a release ID
							// Loop while the entered anticipated release ID is improper in length or the release ID does not exist
							// Also, loop if the entered input is for navigation (i.e., '<' or '>')
							do {
								productReleaseFileDisplay20OrLess(RRPage,productName);
								std::cout << "Current anticipated release ID: " << tmpCI.anticipatedReleaseID;
								std::cout << "\nEnter the new anticipated release ID for the change item (max 8 char, from the list): \n";
								std::cin.getline(anticipatedReleaseID, RELEASE_ID_LENGTH);

								// Check if input length is valid
								if (strcmp(anticipatedReleaseID,"Exit") == 0) {
									exitFlag = true;
									break;
								} else if (std::strcmp(anticipatedReleaseID,"<") == 0) {
									RRPage--;
								} else if (std::strcmp(anticipatedReleaseID,">") == 0) {
									RRPage++;
								} else if (std::cin.fail()) {
									std::cin.clear(); // Clear the fail state
									std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
									std::cout << "Invalid input. Please enter 1 to 8 characters." << std::endl;
									RIDnotProperLen = true; // Continue the loop
								} else if (strlen(anticipatedReleaseID) == 0) {
									std::cout << "Anticipated release ID cannot be empty. Please enter 1 to 8 characters." << std::endl;
									RIDnotProperLen = true; // Continue the loop

								} else {
									RIDnotProperLen = false;
									// After verifying the input length, check if this release ID exists
									releaseIDExists = retrieveProductReleaseByKey(productName,anticipatedReleaseID,tmpPR);
									if (!releaseIDExists)
									{
										std::cout << "You must enter a release ID, of the chosen product, that exists (i.e., is used in a product release)\n";
									}
								}
							} while (RIDnotProperLen || (!releaseIDExists) || 
										(std::strcmp(anticipatedReleaseID,"<") == 0) || (std::strcmp(anticipatedReleaseID,">") == 0));
							if (exitFlag) break;

							// Store for updating
							std::strcpy(tmpCI.anticipatedReleaseID,anticipatedReleaseID);
							break;
						}
					}
					if (exitFlag) break;
				} while (choiceUpdate != 0);
				if (exitFlag) break;

				// Ask user if they are sure they want to update
				choiceSaveUpdates = readIntegerInput(choiceSaveUpdDisp,NO,YES);
				if (choiceSaveUpdates == YES) {
					// Store the desired updates
					updateChangeItem(origChangeID,tmpCI);
				} else {
					break;
				}

				// Final choices
				choiceRepeat = readIntegerInput(repeatUpdate,NO,YES);
				if (choiceRepeat == YES) {
					repeat = true;
				} else {
					repeat = false;
				}
			} while (repeat);

            break;
        }
        default: 
            std::cout << "Invalid choice. Please try again.\n";
    }
}

// ---------------------------------------------------------
// Function: handleReportGeneration
void handleReportGeneration(int choice) {
	// Handles the report generation scenarios
	// Parameter: choice (The chosen scenario for report generation)
    switch (choice) {
        case 1: {
			// Scenario 4.6: Report #1: List of All Change Items for a 
			// Particular Product that are Not Done and Not Cancelled
						// Scenario 4.4: Querying Change Items

			// Variables
			// General
			bool repeat = false;
			int choiceRepeat;
			// Storage
            char productName[PRODUCT_NAME_LENGTH];
			// Get an existing product
			Product tmpProd;
			int productPage = 1;
			int PnotProperLen;
			int PnotExists;
			// Get a change item based on product
			const int INPUT_BUF_LEN = 4 +1;
			int CIPage = 1;
			char inputBuf[INPUT_BUF_LEN];
			// Flags
			bool exitFlag = false;

			// For repeating the scenario
			// Loop while the uesr wants to repeat the scenario (i.e., 'repeat' evaluates to 'true')
			do {
				exitFlag = false;
				// Get the product
				// Loop while the entered product is improper in length or does not exist
				// Also, loop if the entered input is for navigation (i.e., '<' or '>')
				do {
					productFileDisplay20OrLess(productPage);
					std::cout << "Select the product your change item is for by entering its name (max 10 char, must " 
								 "pre-exist):\n";
					std::cin.getline(productName, PRODUCT_NAME_LENGTH);

					// Check if input length is valid
					if (strcmp(productName,"Exit") == 0) {
						exitFlag = true;
						break;
					} else if (std::strcmp(productName,"<") == 0) {
						productPage--;
					} else if (std::strcmp(productName,">") == 0) {
						productPage++;
					} else if (std::cin.fail()) {
						std::cin.clear(); // Clear the fail state
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
						std::cout << "Invalid input. Please enter 1 to 10 characters." << std::endl;
						PnotProperLen = true; // Continue the loop
						PnotExists = false; // Reset PnotExists flag
					} else if (strlen(productName) == 0) {
						std::cout << "Product name cannot be empty. Please enter 1 to 10 characters." << std::endl;
						PnotProperLen = true; // Continue the loop
						PnotExists = false; // Reset PnotExists flag
					} else {
						// Check if the product exists
						PnotExists = !retrieveProductByName(productName, tmpProd);
						if (PnotExists) {
							std::cout << "The product must exist!" << std::endl;
						}
						PnotProperLen = false; // Exit the loop if both conditions are false
					}
				} while (PnotProperLen || PnotExists || (std::strcmp(productName,"<") == 0) || (std::strcmp(productName,">") == 0));
				if (exitFlag) break;
			
				// Print the report
				// Get the change ID based on product choice
				// Loop until the user decides to stop viewing their generated report (i.e., enters 'Exit' as input)
				do {
					generateReport1(CIPage,productName);
					std::cin.getline(inputBuf, INPUT_BUF_LEN);

					// Check if input length is valid
					if (strcmp(inputBuf,"Exit") == 0) {
						exitFlag = true;
						break;
					} else if (std::strcmp(inputBuf,"<") == 0) {
						CIPage--;
					} else if (std::strcmp(inputBuf,">") == 0) {
						CIPage++;
					} else if (std::cin.fail()) {
						std::cin.clear(); // Clear the fail state
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
						std::cout << "Invalid input. Please enter 1 to 4 charactters." << std::endl;
					} else if (strlen(inputBuf) == 0) {
						std::cout << "Input cannot be empty. Please enter 1 to 4 characters." << std::endl;
					} else {
						std::cout << "Please enter input from the given options." << std::endl;
					}
				} while (!exitFlag);

				// Ask if they want to generate another report
				choiceRepeat = readIntegerInput(repeatGen1,NO,YES);
				if (choiceRepeat == YES) {
					repeat = true;
				} else {
					repeat = false;
				}
			} while (repeat);
			break;
       	}
        case 2: {
		// Scenario 4.7: Report #2: List of Customers/Staff Who Need to Be Informed When
		// a Particular Change Has Been Implemented, and in What ProductRelease ID
            // Variables
			// General
			bool repeat;
			int choiceRepeat;
			// Storage
            char productName[PRODUCT_NAME_LENGTH];
			int changeID;
			// Get an existing product
			Product tmpProd;
			int productPage = 1;
			int PnotProperLen;
			int PnotExists;
			// Get a change item based on product
			ChangeItem tmpCI;
			int CIPage = 1;
			char CIStringBuf[CI_STRING_BUF_LEN];
			bool isNumber;
			int CInotExists;
			int CInotProperLen;
			int CIOfProductExists;
			// Anticipated release ID update
			ProductRelease tmpPR;
			char anticipatedReleaseID[RELEASE_ID_LENGTH];
			int releaseIDExists;
			int RRPage = 1;
			int RIDnotProperLen;
			// Flags
			bool exitFlag = false;
			
			// For repeating the scenario
			// Loop while the uesr wants to repeat the scenario (i.e., 'repeat' evaluates to 'true')
			do {
				// Loop while the entered product name is improper in length or does not exist
				// Also, loop if the entered input is for navigation (i.e., '<' or '>')
				do {
					productFileDisplay20OrLess(productPage);
					std::cout << "Select a product by entering its name (max 10 char, must pre-exist):\n";
					std::cin.getline(productName, PRODUCT_NAME_LENGTH);

					// Check if input length is valid
					if (strcmp(productName,"Exit") == 0) {
						exitFlag = true;
						break;
					} else if (std::strcmp(productName,"<") == 0) {
						productPage--;
					} else if (std::strcmp(productName,">") == 0) {
						productPage++;
					} else if (std::cin.fail()) {
						std::cin.clear(); // Clear the fail state
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
						std::cout << "Invalid input. Please enter 1 to 10 characters." << std::endl;
						PnotProperLen = true; // Continue the loop
						PnotExists = false; // Reset PnotExists flag
					} else if (strlen(productName) == 0) {
						std::cout << "Product name cannot be empty. Please enter 1 to 10 characters." << std::endl;
						PnotProperLen = true; // Continue the loop
						PnotExists = false; // Reset PnotExists flag
					} else {
						// Check if the product exists
						PnotExists = !retrieveProductByName(productName, tmpProd);
						if (PnotExists) {
							std::cout << "The product must exist!" << std::endl;
						}
						PnotProperLen = false; // Exit the loop if both conditions are false
					}
				} while (PnotProperLen || PnotExists || (std::strcmp(productName,"<") == 0) || (std::strcmp(productName,">") == 0));
				if (exitFlag) break;

				// Get the change ID based on product choice
				// Loop while the change ID is not of the proper length, does not exist, is not a number, 
				// or an existing change ID is not for the previously-selected product
				// Also, loop if the entered input is for navigation (i.e., '<' or '>')
				do {
					changeItemFileDisplay20OrLess(CIPage,productName);
					std::cout << "Enter an existing change ID (change item) of the product you chose [0-999999]: \n";
					std::cin.getline(CIStringBuf, CI_STRING_BUF_LEN);

					// Check if input length is valid
					if (strcmp(CIStringBuf,"Exit") == 0) {
						exitFlag = true;
						break;
					} else if (std::strcmp(CIStringBuf,"<") == 0) {
						CIPage--;
					} else if (std::strcmp(CIStringBuf,">") == 0) {
						CIPage++;
					} else if (std::cin.fail()) {
						std::cin.clear(); // Clear the fail state
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
						std::cout << "Invalid input. Please enter 1 to 6 digits." << std::endl;
						CInotProperLen = true; // Continue the loop
						CInotExists = false; // Reset CInotExists flag
					} else if (strlen(CIStringBuf) == 0) {
						std::cout << "Change ID cannot be empty. Please enter 1 to 6 digits." << std::endl;
						CInotProperLen = true; // Continue the loop
						CInotExists = false; // Reset CInotExists flag
					} else {
						// Check if the change item exists

						isNumber = stringToInt(CIStringBuf,changeID);
						CInotExists = !retrieveChangeItemByKey(changeID,tmpCI);
						if (!isNumber) {
							// Check if the string is a number
							std::cout << "The change ID must be a number!" << std::endl;
						} else if (CInotExists) {
							std::cout << "The change ID must exist!" << std::endl;
						} else {
							// Check if change items exists for the specified product
							CInotExists = false;
							CIOfProductExists = retrieveChangeItemByKeyAndProduct(changeID,tmpCI,productName);
							if (!CIOfProductExists)
							{
								std::cout << "The change item must have your selected change ID 'and' product name.\n";
							}
						}
						CInotProperLen = false; // Exit the loop if both conditions are false
					}
					// If the change item is for the chosen product and is a number between 0-999999
				} while (CInotProperLen || CInotExists || (!CIOfProductExists) || 
							(std::strcmp(CIStringBuf,"<") == 0) || (std::strcmp(CIStringBuf,">") == 0) || 
							(!isNumber));
				if (exitFlag) break;


				// Ask for a release ID
				// Loop while the entered anticipated release ID is improper in length or does not exist in a product release
				// Also, loop if the entered input is for navigation (i.e., '<' or '>')
				do {
					productReleaseFileDisplay20OrLess(RRPage,productName);
					std::cout << "Enter the new anticipated release ID for the change item (max 8 char, from the list): \n";
					std::cin.getline(anticipatedReleaseID, RELEASE_ID_LENGTH);

					// Check if input length is valid
					if (strcmp(anticipatedReleaseID,"Exit") == 0) {
						exitFlag = true;
						break;
					} else if (std::strcmp(anticipatedReleaseID,"<") == 0) {
						RRPage--;
					} else if (std::strcmp(anticipatedReleaseID,">") == 0) {
						RRPage++;
					} else if (std::cin.fail()) {
						std::cin.clear(); // Clear the fail state
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
						std::cout << "Invalid input. Please enter 1 to 8 characters." << std::endl;
						RIDnotProperLen = true; // Continue the loop
					} else if (strlen(anticipatedReleaseID) == 0) {
						std::cout << "Anticipated release ID cannot be empty. Please enter 1 to 8 characters." << std::endl;
						RIDnotProperLen = true; // Continue the loop

					} else {
						RIDnotProperLen = false;
						// After verifying the input length, check if this release ID exists
						releaseIDExists = retrieveProductReleaseByKey(productName,anticipatedReleaseID,tmpPR);
						if (!releaseIDExists)
						{
							std::cout << "You must enter a release ID, of the chosen product, that exists (i.e., is used in a product release)\n";
						}
					}
				} while (RIDnotProperLen || (!releaseIDExists) || 
							(std::strcmp(anticipatedReleaseID,"<") == 0) || (std::strcmp(anticipatedReleaseID,">") == 0));
				if (exitFlag) break;

				// Generate the report
				generateReport2(changeID, anticipatedReleaseID, productName);

				// Final choices
				choiceRepeat = readIntegerInput(repeatGen2,NO,YES);
				if (choiceRepeat == YES) {
					repeat = true;
				} else {
					repeat = false;
				}
			} while (repeat);

            break;
        }
        default: 
            std::cout << "Invalid choice. Please try again.\n";
    }
}