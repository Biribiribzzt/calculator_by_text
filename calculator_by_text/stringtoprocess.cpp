#include "stringtoprocess.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath> 
#include <cctype> 
#include <algorithm>

using namespace std;

// Constructor
Texttomath::Texttomath(const string& input) {
    processtext = input;
    finalresult = splitString(processtext, ' ');

    for (int i = 0; i < finalresult.size(); i++) {
        cout << finalresult[i] << endl;
    }
    cout << finalresult.size() << endl;

    // Ensure finalresult has at least 3 elements before accessing indices
    if (finalresult.size() < 3) {
        cout << "Error: Input does not have enough components." << endl;
        return;
    }
    
}

int Texttomath::checkcase(const string& context) {
    vector<string> tokens = splitString(context, ' ');

    // Ensure tokens has enough elements to check cases
    if (tokens.size() < 3) {
        cout << "Error: Insufficient elements in context." << endl;
        return -1; // Return an error code or handle it as needed
    }

    // Function to check if a string represents a number
    auto isNumber = [](const string& s) -> bool {
        // Check if every character is a digit (simplified; you may want to handle decimals or negatives)
        return !s.empty() && all_of(s.begin(), s.end(), ::isdigit);
        };

    // Determine the case based on operand types
    bool firstIsNumber = isNumber(tokens[0]);
    bool secondIsNumber = isNumber(tokens[2]);

    if (firstIsNumber && secondIsNumber) {
        return 1; // Case 1: Number and Number
    }
    else if (!firstIsNumber && !secondIsNumber) {
        return 2; // Case 2: Variable and Variable
    }
    else if (!firstIsNumber && secondIsNumber) {
        return 3; // Case 3: Variable and Number
    }
    else if (firstIsNumber && !secondIsNumber) {
        return 4; // Case 4: Number and Variable
    }

    // Default return for unexpected input
    cout << "Error: Unhandled case." << endl;
    return -1;
}

// Function to split string by user-defined delimiter
vector<string> Texttomath::splitString(const string& str, char delimiter) {
    vector<string> result;
    string token;
    istringstream tokenStream(str);

    while (getline(tokenStream, token, delimiter)) {
        result.push_back(token);
    }

    return result;
}


// Finds a number associated with a variable name
double Texttomath::findnumberat(const string& content) {
    for (size_t i = 0; i < external_name.size(); ++i) {
        if (external_name[i] == content) {
            return external_value[i];
        }
    }
    cout << "Variable " << content << " not found!" << endl;
    return 0.0; // Default value if variable is not found
}

// Determines the operation based on the operator string
int Texttomath::Return_process() {
    string opt = finalresult.size() > 1 ? finalresult[1] : "Operator doesn't exist";
    if (opt == "+") {
        process = 1;
    }
    else if (opt == "-") {
        process = 2;
    }
    else if (opt == "*") {
        process = 3;
    }
    else if (opt == "/") {
        process = 4;
    }
    else if (opt == "^") {
        process = 5;
    }
    else if (opt == "=") {
        is_assinging = true;
        process = 6;
    }
    else {
        process = 404; // Not found
    }
    return process;
}

// Perform calculations based on case index
double Texttomath::calculate() {
    int case_index = checkcase(processtext);
    double num1 = 0;
    double num2 = 0;
    int process_index = Return_process();

    switch (case_index) {
    case 1: // Number and Number
        if (finalresult.size() == 3) { // Ensure indices are accessible
            num1 = stod(finalresult[0]);
            num2 = stod(finalresult[2]);
        }
        else {
            cout << "Error: Insufficient elements for calculation." << endl;
            return 0.0;
        }
        break;
    case 2: // Variable and Variable
        num1 = findnumberat(finalresult[0]);
        num2 = findnumberat(finalresult[2]);
        break;
    case 3: // Variable and Number
        num1 = findnumberat(finalresult[0]);
        num2 = stod(finalresult[2]);
        break;
    case 4: // Number and Variable
        num1 = stod(finalresult[0]);
        num2 = findnumberat(finalresult[2]);
        break;
    case 5: // Assignment
        if (process_index == 6) {
            external_name.push_back(finalresult[0]);
            external_value.push_back(stod(finalresult[2]));
            cout << "Finished assigning variable." << endl;
            return 0.0; // No operation result for assignment
        }
        break;
    default:
        cout << "Invalid calculation case!" << endl;
        return 0.0;
    }

    switch (process_index) {
    case 1:
        return num1 + num2;
    case 2:
        return num1 - num2;
    case 3:
        return num1 * num2;
    case 4:
        if (num2 != 0) {
            return num1 / num2;
        }
        else {
            cout << "Error: Division by zero." << endl;
            return 0.0;
        }
    case 5:
        return pow(num1, num2); // Correct exponentiation
    case 404:
        cout << "Error: process not found" << endl;
        return 0.0;
    default:
        cout << "No valid operation found." << endl;
        return 0.0;
    }
}

// Prints test message with processed results
void Texttomath::print_text_test() {
    cout << "Processed text: " << processtext << endl;
    cout << "Operation code: " << process << endl;
    cout << "Is external variable: " << is_external_variable << endl;

    if (!is_external_variable) {
        cout << "Number1: " << stod(finalresult[0]) << ", Number2: " << stod(finalresult[2]) << endl;
    }
    else {
        for (int i = 0; i < external_name.size(); i++) {
            cout << external_name[i] << " = " << external_value[i] << endl;
        }
    }

    cout << "answer : " << calculate() << endl;
}
