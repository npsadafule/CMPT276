// ============================================
// Module Name: main.cpp
// ============================================
// Version History:
// Rev. 1 - 2024/07/01 - Neel Sadafule
// ============================================

#include <iostream>
#include "UserInterface.h"
#include "SystemController.h"

// Main Function
// ============================================
// Function: main
int main() {
    // Description:
    // Entry point of the application. It starts the system by calling the start function and then
    // activates the user interface.
    start();
    activateUI();
    return 0;
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
void exampleFunction(
    const std::string& param1,    // in
    int param2                    // out
) {
    // Description:
    // This function serves as an example.
    // It does something useful.
}

6. Error Handling:
    - Always check the return values of functions and handle errors appropriately.
    - Use exceptions where appropriate, but not for control flow.

7. Miscellaneous:
    - Do not leave commented-out code blocks in the final submission.
    - Keep lines under 80 characters where possible.
*/
