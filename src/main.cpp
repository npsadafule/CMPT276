// ============================================
// Module Name: main.cpp
// ============================================
// Version History:
// Rev. 2 - 2024/07/17 - Group 7
	//	Kenneth Tan: Edited comments to match Assignment 5 requirements.
// Rev. 1 - 2024/07/01 - Group 7
// ============================================

// Overall internal design issues:
// Initiates the ITS system by calling "start," which opens necesary files. Then, a call is made 
// to "activateUI," which starts the user interface. The main function call terminates once
// the user quits ITS (i.e., ends the call to "activateUI").

#include <iostream>
#include "UserInterface.h"
#include "SystemController.h"

// ============================================
// Main Function
// ============================================

// ---------------------------------------------------------
// Function: main
int main() {
    // Description:
    // Entry point of the program. Starts the system and activates the user interface.
    // Returns: int (Exit status, 0 indicates successful execution)
    start();         // Initialize system components
    activateUI();    // Start user interface
    return 0;        // Exit program successfully
}

/*
Coding Conventions:

1. Module and File Organization:
    - Each .cpp file starts with a comment stating the file's name and a revision history.
    - Use bold dividers for major sections: // ============================================

2. Function and Parameter Commenting:
    - Each function must have a comment describing its purpose, parameters, and any exceptions it might throw.
    - Use a thin horizontal dividing line before function prototypes in header files.
    - Place specific comments regarding a whole function after the signature but before the first statement.
        - If there is only one line for a comment detailing the general operation of the function, it is placed above the prototype.
        - If a comment is two or more lines, it will either be completely stored inside the function curly braces or have one brief description line before the prototype

3. Naming Conventions:
    - Class names: CamelCase with the first letter capitalized.
    - Function names: camelCase with the first letter lowercase.
    - Constants: UPPER_CASE.
    - Variables: camelCase.

4. Indentation and Spacing:
    - Use 3 spaces for indentation.
    - Opening braces `{` go on the same line as the function name or control statement.
    - Place a space after commas and around operators.

5. Version History:
    - The revision history should be in chronological order, with the latest changes at the top.

Example Function Comment:

// ---------------------------------------------------------
// Function: exampleFunction
// This function serves as an example.
// Parameter: param1 (Description of param1)
// Parameter: param2 (Description of param2)
void exampleFunction(const std::string& param1, int param2) {
    // It does something useful.
}

6. Error Handling:
    - Always check the return values of functions and handle errors appropriately.
    - Use exceptions where appropriate, but not for control flow.

7. Miscellaneous:
    - Do not leave commented-out code blocks in the final submission.
    - Keep lines under 80 characters where possible.
*/