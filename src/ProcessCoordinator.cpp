// ============================================
// Module Name: ProcessCoordinator.cpp
// ============================================
// Version History:
// Rev. 2 - 2024/07/17 - Group 7
// ============================================

// Overall internal design issues:
// This module implements ProcessCoordinator.h, following our central control design from our Architectural Design Document. Specifically, it houses the implementation of scenario execution as cases of a particular submenu. For example, handleProductMaintenance has a case for executing Product creation and Product Release creation. Hence, it uses structures exported by each of the lower-level modules (e.g., Product). Also, do-while loops are used freqeuntly to ensure proper user input.

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

// Non-exported module scope constants for repeating a scenario
static const int YES = 1;   
static const int NO = 0;

// Files
extern std::fstream productReleaseFile;

// Variables for navigation options
int entryCount;

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

    // Format the date into the provided buffer using snprintf
    std::snprintf(dateStr, size, "%04d%02d%02d", now->tm_year + 1900, now->tm_mon + 1, now->tm_mday);
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
	std::cout << "\nAre you sure you want to add this product release (1 for Y, 0 for N)?\n" <<
	std::endl;
}

// ---------------------------------------------------------
// Function: doYouWantAnotherProdRel
void doYouWantAnotherProdRel() {
    // Prompts the user to confirm adding another product release
	std::cout << "\nDo you wish to add another release (1 for Y, 0 for N)?\n" << std::endl;
}

// Display functions for Scenario 4.3
// ============================================
// ---------------------------------------------------------
// Function: requesterOptions
void requesterOptions() {
    // Displays the options for navigating requesters
	std::cout << "=== Enter '" << std::to_string(entryCount+1) << "' for previous 20 items, '" <<
				 std::to_string(entryCount+2) << "' for next 20 items ===" << std::endl <<
				 "=== 0 (zero) for exiting the list ===" << std::endl;
}

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
	std::cout << "\nSelect what update to make to this change item of Product A:\n"
				 "1) Update Description\n"
				 "2) Update State\n"
				 "3) Update Anticipated Release ID\n"
				 "0) Save updates made to the chosen Change Item\n";
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
			do 
			{
                    // Keep repeating the "create Product" scenario so long as the user inputs 'YES'
				// Scenario 4.1: Creating a Product - duplication prevention logic not implemented
				char productName[PRODUCT_NAME_LENGTH];
				Product tmpProd;
				int notProperLen;
				int exists;

				// Product name read
				do {
                    // Keep looping based on whether user input is not of the proper length or encounters a key uniquness issue. If both of these conditions are false, we have valid input.
					std::cout << "\nEnter the Product Name (max 30 char, must not exist): \n";
					std::cin.getline(productName, PRODUCT_NAME_LENGTH);

					// Check if input length is valid
					if (std::cin.fail()) {
						std::cin.clear(); // Clear the fail state
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
						std::cout << "\nInvalid input. Please enter 1 to 30 characters." << std::endl;
						notProperLen = true; // Continue the loop
						exists = false; // Reset exists flag
					} else if (strlen(productName) == 0) {
						std::cout << "\nProduct name cannot be empty. Please enter 1 to 30 characters." << std::endl;
						notProperLen = true; // Continue the loop
						exists = false; // Reset exists flag
					} else {
						// Check if the product already exists
						exists = retrieveProductByName("products.dat", productName, tmpProd);
						if (exists) {
							std::cout << "\nThe product already exists!" << std::endl;
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
			do   // Keep repeating the "create Product Release" scenario so long as the user inputs 'YES'
			{
				Product tmpProd;
				ProductRelease tmpRel;
				int notProperLen;
				int notExists;
				bool ifUniqueProdRel;
				
				do {    
                            // Keep looping so long as we run into a key uniqueness issue for product releases (i.e., entering an existing name and release ID).
					do {
                             // Keep looping based on whether user input is not of the proper length or encounters a referential integrity issue. If both of these conditions are false, we have valid input.
						std::cout << "\nEnter the Product Name (max 30 char, must pre-exist): \n";
						std::cin.getline(productName, PRODUCT_NAME_LENGTH);

						// Check if input length is valid
						if (std::cin.fail()) {
							std::cin.clear(); // Clear the fail state
							std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
							std::cout << "\nInvalid input. Please enter 1 to 30 characters." << std::endl;
							notProperLen = true; // Continue the loop
							notExists = false; // Reset notExists flag
						} else if (strlen(productName) == 0) {
							std::cout << "\nProduct name cannot be empty. Please enter 1 to 30 characters." << std::endl;
							notProperLen = true; // Continue the loop
							notExists = false; // Reset notExists flag
						} else {
							// Check if the product exists
							notExists = !retrieveProductByName("products.dat", productName, tmpProd);
							if (notExists) {
								std::cout << "\nThe product must exist!" << std::endl;
							}
							notProperLen = false; // Exit the loop if both conditions are false
						}
					} while (notProperLen || notExists);

					// Get a product release ID
					do {   
                        // Keep looping for input from the user for a product release ID that is of the proper length
						std::cout << "\nEnter the Release ID (max 8 char following your organization's format): \n";
						std::cin.getline(releaseID, RELEASE_ID_LENGTH);

						// Check if input length is valid
						if (std::cin.fail()) {
							std::cin.clear(); // Clear the fail state
							std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
							std::cout << "\nInvalid input. Please enter 1 to 8 characters." << std::endl;
							notProperLen = true;
						} else {
							// Check if input is empty (0 characters)
							notProperLen = strlen(releaseID) == 0;
							if (notProperLen) {
								std::cout << "\nInput cannot be empty. Please enter 1 to 8 characters." << std::endl;
							}
						}
					} while (notProperLen);

					// Check for uniquenes by product release ID
					ifUniqueProdRel = retrieveProductReleaseByKey("productReleases.dat", productName, releaseID, tmpRel);
					if (ifUniqueProdRel)
					{
						std::cout << "You must enter a product release that has a unique compound primary key " 
						"(i.e., unique combination of product name and release ID).\n";
					}
				} while (ifUniqueProdRel);				

				// Get a release date
				do {
                    // Loop forward until a release date of the proper length is entered
					std::cout << "\nEnter the release date (YYYYMMDD)): \n \n";
					std::cin.getline(releaseDate, RELEASE_DATE_LENGTH);

					notProperLen = std::cin.fail() || strlen(releaseDate) != 8;

					if (notProperLen) {
						std::cin.clear(); // Clear the fail state
						std::cout << "\nThe release date must be 8 characters!" << std::endl;
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
    // std::vector<User> users; // Declare the 'users' variable
	static const int ENTER_REQ = 1;
	static const int CREATE_REQ = 2;

	static const int ENTER_CI = 1;
	static const int CREATE_CI = 2;

	std::cout << std::endl;

    switch (choice) {
        case 1: {
			// Scenario 4.3: Create Change Request
			
			// Variables
			// Scenario-wide
			bool repeat = false;
			int choiceConfirmAdd;
			int choiceRepeat;
			
			// User input storage
			char requester[REQ_NAME_LENGTH], phoneNum[PHONE_NUMBER_LENGTH], email[EMAIL_LENGTH], department[DEPARTMENT_LENGTH];
			char productName[PRODUCT_NAME_LENGTH], description[CHANGE_DESC_LENGTH], anticipatedReleaseID[RELEASE_ID_LENGTH];
			char state[STATE_LENGTH] = "Reported";
			char date[REP_DATE_LENGTH];
			int changeID;		
			char reportedRelease[RELEASE_ID_LENGTH] = "TBD";	

			// Requester selection
			int reqChoice;
			Requester tmpRequester;
			// Enter requester 
			int ERnotExists;
			int ERnotProperLen;
			// Create requester
			int CRnotProperLen;
			int CRexists;

			// Product selction
			Product tmpProd;
			int PnotExists;
			int PnotProperLen;

			// ChangeItem selection
			ChangeItem tmpCI;
			int CIChoice;
			int CInotExists;
			int CInotProperLen;
			int releaseIDExists;

		
			// For repeat choice
			do {
                    // Keep looping if the user chooses that they want to create another change request
				// Get a requester name
				reqChoice = readIntegerInput(reqSearchChoice,1,2);
				if (reqChoice == ENTER_REQ) {
					do {
                            // Keep looping for a requester name until it has the proper length and the requester is unique
						std::cout << "\nEnter the Requester name (max 30 char, must pre-exist): \n";
						std::cin.getline(requester, REQ_NAME_LENGTH);

						// Check if input length is valid
						if (std::cin.fail()) {
							std::cin.clear(); // Clear the fail state
							std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
							std::cout << "\nInvalid input. Please enter 1 to 30 characters." << std::endl;
							ERnotProperLen = true; // Continue the loop
							ERnotExists = false; // Reset ERnotExists flag
						} else if (strlen(requester) == 0) {
							std::cout << "\nRequester name cannot be empty. Please enter 1 to 30 characters." << std::endl;
							ERnotProperLen = true; // Continue the loop
							ERnotExists = false; // Reset ERnotExists flag
						} else {
							// Check if the product exists
							ERnotExists = !retrieveRequesterByKey("requestersFile.dat", requester, tmpRequester);
							if (ERnotExists) {
								std::cout << "\nThe Requester must exist!" << std::endl;
							}
							ERnotProperLen = false; // Exit the loop if both conditions are false
						}
					} while (ERnotProperLen || ERnotExists);
				} else if (reqChoice == CREATE_REQ) {
					// Keep looping for a requester name until it has the proper length and the requester does not have a key uniqueness issue
					do {
						std::cout << "\nEnter the Requester name (max 30 char, must not exist): \n";
						std::cin.getline(requester, REQ_NAME_LENGTH);

						// Check if input length is valid
						if (std::cin.fail()) {
							std::cin.clear(); // Clear the fail state
							std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
							std::cout << "\nInvalid input. Please enter 1 to 30 characters." << std::endl;
							CRnotProperLen = true; // Continue the loop
							CRexists = false; // Reset CRexists flag
						} else if (strlen(requester) == 0) {
							std::cout << "\nRequester name cannot be empty. Please enter 1 to 30 characters." << std::endl;
							CRnotProperLen = true; // Continue the loop
							CRexists = false; // Reset CRexists flag
						} else {
							// Check if the requester already exists
							CRexists = retrieveRequesterByKey("requestersFile.dat", requester, tmpRequester);
							if (CRexists) {
								std::cout << "\nThe requester already exists!" << std::endl;
							}
							CRnotProperLen = false; // Exit the loop if both conditions are false
						}
					} while (CRnotProperLen || CRexists);

					// Get phone number
                    // Keep looping as long as the entered phone number is not of the proper length
					do {
						std::cout << "\nEnter your phone number (10 digits in the format DDDDDDDDDD): \n";
						std::cin.getline(phoneNum, PHONE_NUMBER_LENGTH);

						// Check if input length is valid
						if (std::cin.fail()) {
							std::cin.clear(); // Clear the fail state
							std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
							std::cout << "\nInvalid input. Please enter 10 characters." << std::endl;
							CRnotProperLen = true; // Continue the loop
						} else if (strlen(phoneNum) < 10) {
							std::cout << "\nPhone number cannot be less than 10 digits. Please enter 10 digits." << std::endl;
							CRnotProperLen = true; // Continue the loop
						} else {
							CRnotProperLen = false;
						}
					} while (CRnotProperLen);

					// Get email
                    // Keep looping as long as the email entered is not the proper length
					do {
						std::cout << "\nEnter the email of the customer (max 24 char in the format "
									"username@email_provider.domain_type):\n";
						std::cin.getline(email, PHONE_NUMBER_LENGTH);

						// Check if input length is valid
						if (std::cin.fail()) {
							std::cin.clear(); // Clear the fail state
							std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
							std::cout << "\nInvalid input. Please enter 1 to 24 characters." << std::endl;
							CRnotProperLen = true; // Continue the loop
						} else if (strlen(email) == 0) {
							std::cout << "\nEmail cannot be empty. Please enter 1 to 24 characters." << std::endl;
							CRnotProperLen = true; // Continue the loop
						} else {
							CRnotProperLen = false;
						}
					} while (CRnotProperLen);

					// Get department
                    // Keep looping as long as the department entered is not the proper length
					do {
						std::cout << "\nIf you are an employee, enter your department (max 12 char). If this is not "
									"applicable to you, enter 'N/A':\n";
						std::cin.getline(department, DEPARTMENT_LENGTH);

						// Check if input length is valid
						if (std::cin.fail()) {
							std::cin.clear(); // Clear the fail state
							std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
							std::cout << "\nInvalid input. Please enter 1 to 12 characters." << std::endl;
							CRnotProperLen = true; // Continue the loop
						} else if (strlen(department) == 0) {
							std::cout << "\nDepartment cannot be empty. Please enter 1 to 12 characters." << std::endl;
							CRnotProperLen = true; // Continue the loop
						} else {
							CRnotProperLen = false;
						}
					} while (CRnotProperLen);		

					// Create new requester
					createRequester(requester,phoneNum,email,department);
				}

				// Select a product
                    // Keep looping so long as the product name entered is not the proper length and runs into a referential integrity issue
				do {
					std::cout << "\nEnter the Product Name (max 30 char, must pre-exist): \n";
					std::cin.getline(productName, PRODUCT_NAME_LENGTH);

					// Check if input length is valid
					if (std::cin.fail()) {
						std::cin.clear(); // Clear the fail state
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
						std::cout << "\nInvalid input. Please enter 1 to 30 characters." << std::endl;
						PnotProperLen = true; // Continue the loop
						PnotExists = false; // Reset PnotExists flag
					} else if (strlen(productName) == 0) {
						std::cout << "\nProduct name cannot be empty. Please enter 1 to 30 characters." << std::endl;
						PnotProperLen = true; // Continue the loop
						PnotExists = false; // Reset PnotExists flag
					} else {
						// Check if the product exists
						PnotExists = !retrieveProductByName("products.dat", productName, tmpProd);
						if (PnotExists) {
							std::cout << "\nThe product must exist!" << std::endl;
						}
						PnotProperLen = false; // Exit the loop if both conditions are false
					}
				} while (PnotProperLen || PnotExists);

				// Change item
				CIChoice = readIntegerInput(CIChoiceDisplay,ENTER_CI,CREATE_CI);

				if (CIChoice == ENTER_CI) // Enter existing change ID
				{
                    // Keep loooping so long as the change ID entered does not exist
					do {
						changeID = readIntegerInput(CIPrompt,0,999999);

						CInotExists = !retrieveChangeItemByKey("changeItems.dat",changeID,tmpCI);
						if (CInotExists) {
							std::cout << "\nThe change item must exist!\n";
						}
					} while (CInotExists);
				} else if (CIChoice == CREATE_CI) { // Create change ID
					// Enter new change ID
                    // Keep looping so long as the change ID entered runs into a key uniqueness issue
					do {
						changeID = readIntegerInput(CIPrompt,0,999999);

						CInotExists = retrieveChangeItemByKey("changeItems.dat",changeID,tmpCI);
						if (CInotExists) {
							std::cout << "\nThe change item must not exist!\n";
						}
					} while (CInotExists);

					// Enter description for change item
                    // Keep looping so long as the entered description has an improper length
					do {
						std::cout << "\nEnter the description for the change item (max 150 char): \n";
						std::cin.getline(description, CHANGE_DESC_LENGTH);

						// Check if input length is valid
						if (std::cin.fail()) {
							std::cin.clear(); // Clear the fail state
							std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
							std::cout << "\nInvalid input. Please enter 1 to 150 characters." << std::endl;
							CInotProperLen = true; // Continue the loop
						} else if (strlen(description) == 0) {
							std::cout << "\nDescription cannot be empty. Please enter 1 to 150 characters." << std::endl;
							CInotProperLen = true; // Continue the loop
						} else {
							CInotProperLen = false;
						}
					} while (CInotProperLen);

					// Enter an anticipated release ID
                    // Keep looping as long a the entered release ID does not have the proper length or the release ID encounters a referential integrity issue
					do {
						std::cout << "\nEnter the anticipated release ID for the change item (max 8 char): \n";
						std::cin.getline(anticipatedReleaseID, RELEASE_ID_LENGTH);

						// Check if input length is valid
						if (std::cin.fail()) {
							std::cin.clear(); // Clear the fail state
							std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
							std::cout << "\nInvalid input. Please enter 1 to 8 characters." << std::endl;
							CInotProperLen = true; // Continue the loop
						} else if (strlen(anticipatedReleaseID) == 0) {
							std::cout << "\nRelease ID cannot be empty. Please enter 1 to 8 characters." << std::endl;
							CInotProperLen = true; // Continue the loop

						} else {
							CInotProperLen = false;
							// After verifying the input length, check if this release ID exists
							releaseIDExists = determineReleaseIDExistence(anticipatedReleaseID);
							if (!releaseIDExists)
							{
								std::cout << "You must enter a release ID that exists (i.e., is used in a product release)\n";
							}
						}
					} while (CInotProperLen || (!releaseIDExists));

					// Create the new change ID
					createChangeItem(changeID,productName,description,anticipatedReleaseID,state);
				}

				// Final choices
				choiceConfirmAdd = readIntegerInput(confirmAddCR,NO,YES);
				if (choiceConfirmAdd == YES) {
					getTodaysDate(date, sizeof(date));
					createChangeRequest(requester,changeID,reportedRelease,date,"Low");
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
			int notProperLen;
			int notExists;
			// Get a change item based on product
			ChangeItem tmpCI;
			int CInotExists;
			int CIOfProductExists;

			// For repeating the scenario
                // Keep looping so long as the user enters 'YES' to querying for another change item
			do {
                    // Keep looping so long as the entered product name is not the proper length or does not exist
				do {
					std::cout << "\nSelect a product name (max 30 char, must pre-exist): \n";
					std::cin.getline(productName, PRODUCT_NAME_LENGTH);

					// Check if input length is valid
					if (std::cin.fail()) {
						std::cin.clear(); // Clear the fail state
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
						std::cout << "\nInvalid input. Please enter 1 to 30 characters." << std::endl;
						notProperLen = true; // Continue the loop
						notExists = false; // Reset notExists flag
					} else if (strlen(productName) == 0) {
						std::cout << "\nProduct name cannot be empty. Please enter 1 to 30 characters." << std::endl;
						notProperLen = true; // Continue the loop
						notExists = false; // Reset notExists flag
					} else {
						// Check if the product exists
						notExists = !retrieveProductByName("products.dat", productName, tmpProd);
						if (notExists) {
							std::cout << "\nThe product must exist!" << std::endl;
						}
						notProperLen = false; // Exit the loop if both conditions are false
					}
				} while (notProperLen || notExists);
			
				// Get the change ID based on product choice
                    // Keep looping so long as the entered change ID encounters a referential integrity issue or there are no change items with the change ID and product name specified
				do {
					changeID = readIntegerInput(CIPrompt,0,999999);

					CInotExists = !retrieveChangeItemByKey("changeItems.dat",changeID,tmpCI);
					if (CInotExists) {
						std::cout << "\nThe change item must exist!\n";
					}
					else {
						CInotExists = false;
						CIOfProductExists = retrieveChangeItemByKeyAndProduct("changeItems.dat",changeID,tmpCI,productName);
						if (!CIOfProductExists)
						{
							std::cout << "The change item must have your selected change ID 'and' product name.\n";
						}
					}
				} while (CInotExists || (!CIOfProductExists));


				// Print the information of the product's change item
				std::cout << std::endl;
				std::cout << std::setw(25) << std::left << "Product:" << tmpCI.productName << std::endl;
				std::cout << std::setw(25) << std::left << "Description:" << tmpCI.description << std::endl;
				std::cout << std::setw(25) << std::left << "Change ID:" << std::to_string(changeID) << std::endl;
				std::cout << std::setw(25) << std::left << "State:" << tmpCI.state << std::endl;
				std::cout << std::setw(25) << std::left << "Anticipated Release ID:" << tmpCI.productName << std::endl;

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
			int notProperLen;
			int notExists;
			// Get a change item based on product
			ChangeItem tmpCI;
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
			char anticipatedReleaseID[RELEASE_ID_LENGTH];
			int releaseIDExists;
			// Save updates choice
			int choiceSaveUpdates;
			int origChangeID;

			// For repeating the scenario
                // Keep looping so long as the user says 'YES' to updating another change item
			do {
                    // Keep looping so long as the entered product name is not the proper length or does not exist
				do {
					std::cout << "\nSelect a product name (max 30 char, must pre-exist): \n";
					std::cin.getline(productName, PRODUCT_NAME_LENGTH);

					// Check if input length is valid
					if (std::cin.fail()) {
						std::cin.clear(); // Clear the fail state
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
						std::cout << "\nInvalid input. Please enter 1 to 30 characters." << std::endl;
						notProperLen = true; // Continue the loop
						notExists = false; // Reset notExists flag
					} else if (strlen(productName) == 0) {
						std::cout << "\nProduct name cannot be empty. Please enter 1 to 30 characters." << std::endl;
						notProperLen = true; // Continue the loop
						notExists = false; // Reset notExists flag
					} else {
						// Check if the product exists
						notExists = !retrieveProductByName("products.dat", productName, tmpProd);
						if (notExists) {
							std::cout << "\nThe product must exist!" << std::endl;
						}
						notProperLen = false; // Exit the loop if both conditions are false
					}
				} while (notProperLen || notExists);
			
				// Get the change ID based on product choice
                    // Keep looping so long as the entered change ID encounters a referential integrity issue or there are no change items with the change ID and product name specified
				do {
					changeID = readIntegerInput(CIPrompt,0,999999);

					CInotExists = !retrieveChangeItemByKey("changeItems.dat",changeID,tmpCI);
					if (CInotExists) {
						std::cout << "\nThe change item must exist!\n";
					}
					else {
						CInotExists = false;
						CIOfProductExists = retrieveChangeItemByKeyAndProduct("changeItems.dat",changeID,tmpCI,productName);
						if (!CIOfProductExists)
						{
							std::cout << "The change item must have your selected change ID 'and' product name.\n";
						}
					}
				} while (CInotExists || (!CIOfProductExists));

				// Store the original change ID (for overwriting)
				origChangeID = tmpCI.changeID;

				// Select what update to make
				do {
					choiceUpdate = readIntegerInput(choiceUpdateDisp,0,3);
					switch (choiceUpdate) {
						case 1: { // Description
							std::cout << "\nCurrent description: " << tmpCI.description << std::endl;
							// Enter description for change item
							do {
								std::cout << "Enter the new description for the change item (max 150 char): \n";
								std::cin.getline(description, CHANGE_DESC_LENGTH);

								// Check if input length is valid
								if (std::cin.fail()) {
									std::cin.clear(); // Clear the fail state
									std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
									std::cout << "\nInvalid input. Please enter 1 to 150 characters." << std::endl;
									CInotProperLen = true; // Continue the loop
								} else if (strlen(description) == 0) {
									std::cout << "\nDescription cannot be empty. Please enter 1 to 150 characters." << std::endl;
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
							std::cout << "\nCurrent state: " << tmpCI.state << std::endl;
							do {
								std::cout << "Enter the new state of the change item (max 10 char):\n";
								std::cin.getline(state, STATE_LENGTH);

								// Check if input length is valid
								if (std::cin.fail()) {
									std::cin.clear(); // Clear the fail state
									std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
									std::cout << "\nInvalid input. Please enter 1 to 10 characters." << std::endl;
									CInotProperLen = true; // Continue the loop
								} else if (strlen(state) == 0) {
									std::cout << "\nEmail cannot be empty. Please enter 1 to 10 characters." << std::endl;
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
							std::cout << "\nCurrent anticipated release ID: " << tmpCI.anticipatedReleaseID << std::endl;
							// Enter an anticipated release ID
							do {
								std::cout << "Enter the new anticipated release ID for the change item (max 8 char): \n";
								std::cin.getline(anticipatedReleaseID, RELEASE_ID_LENGTH);

								// Check if input length is valid
								if (std::cin.fail()) {
									std::cin.clear(); // Clear the fail state
									std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
									std::cout << "\nInvalid input. Please enter 1 to 8 characters." << std::endl;
									CInotProperLen = true; // Continue the loop
								} else if (strlen(anticipatedReleaseID) == 0) {
									std::cout << "\nDescription cannot be empty. Please enter 1 to 8 characters." << std::endl;
									CInotProperLen = true; // Continue the loop

								} else {
									CInotProperLen = false;
									// After verifying the input length, check if this release ID exists
									releaseIDExists = determineReleaseIDExistence(anticipatedReleaseID);
									if (!releaseIDExists)
									{
										std::cout << "You must enter a release ID that exists (i.e., is used in a product release)\n";
									}
								}
							} while (CInotProperLen || (!releaseIDExists));

							// Store for updating
							std::strcpy(tmpCI.anticipatedReleaseID,anticipatedReleaseID);
							break;
						}
					}
				} while (choiceUpdate != 0);

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
            std::string productName;
            std::cout << "Enter the product name to generate Report #1: ";
            std::getline(std::cin, productName);
            generateReport1(productName);
            break;
        }
        case 2: {
		// Scenario 4.7: Report #2: List of Customers/Staff Who Need to Be Informed When
		// a Particular Change Has Been Implemented, and in What ProductRelease ID
            std::string changeID;
            std::cout << "Enter the Change ID to generate Report #2: ";
            std::getline(std::cin, changeID);
            generateReport2(changeID);
            break;
        }
        default: 
            std::cout << "Invalid choice. Please try again.\n";
    }
}

// ---------------------------------------------------------
// Function: displayHelp
// Displays help information for using the system
void displayHelp() {
    std::cout << "Help: This system is designed to manage and track issues, such as bugs and feature requests, within a software development environment.\n";
    std::cout << "At any point, type 'Help' to receive guidance on the available options and how to use them.\n";
}