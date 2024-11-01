#include "stringtoprocess.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
#include <cctype>
#include <algorithm>

using namespace std;

uint32_t Texttomath::count = 0; // Initialize static variable
string Texttomath::external_name[MAX_VAR] = {};
long double Texttomath::external_value[MAX_VAR] = {}; 

// main constrictor
Texttomath::Texttomath(string input) {
    processtext = input;
    splitString(processtext,finalresult[0], finalresult[1],finalresult[2]);

    for (int i = 0; i < 3; i++) {
        cout << finalresult[i] << endl;
    }

    cout << "Answer : " << calculate() << endl;

    count++;
}

//constrctor2 show debug.
Texttomath::Texttomath(string input, uint16_t show_debug) {
    processtext = input;
    splitString(processtext, finalresult[0], finalresult[1], finalresult[2]);

    for (int i = 0; i < 3; i++) {
        cout << finalresult[i] << endl;
    }
    
    cout << "Answer : " << calculate() << endl;
    debug();
    count++;
}

//checkcase of variable 
uint16_t Texttomath::checkcase(const string& context) {
    splitString(context, finalresult[0], finalresult[1], finalresult[2]);

    if (finalresult[0].empty() || finalresult[2].empty()) {
        cout << "Error: Invalid input format in checkcase." << std::endl;
        return 0; // Return error code
    }

    // Lambda to check if a string is a valid long double
    auto isLongDouble = [](const string& s) -> bool {
        try {
            stold(s);  
            return true;
        }
        catch (const std::invalid_argument& e) {
            return false; 
        }
        catch (const std::out_of_range& e) {
            return false;   
        }
    };

    bool firstIsLongDouble = isLongDouble(finalresult[0]);
    bool secondIsLongDouble = isLongDouble(finalresult[2]);

    if (firstIsLongDouble && secondIsLongDouble) {
        return 1;
    }
    else if (!firstIsLongDouble && !secondIsLongDouble) {
        return 2;
    }
    else if (!firstIsLongDouble && secondIsLongDouble) {
        return 3;
    }
    else if (firstIsLongDouble && !secondIsLongDouble) {
        return 4;
    }

    std::cout << "Error: Unhandled case in checkcase." << std::endl;
    return 5;

}

//split the string
void Texttomath::splitString(const string& str, string& part1, string& part2, string& part3) { 
    std::istringstream stream(str);
    std::getline(stream, part1, ' ');
    std::getline(stream, part2, ' ');
    std::getline(stream, part3, ' ');
}

 //find number in other array by seaching text
long double Texttomath::findnumberat(const string& content) {
    for (size_t i = 0; i < MAX_VAR; ++i) {
        if (external_name[i] == content) {
            return external_value[i];
        }
    }
    cout << "Variable " << content << " not found!" << endl;
    return 0.0;
}

//Return the operator of text
uint16_t Texttomath::Return_process() { 
    string opt = finalresult[1].empty() ? "Operator doesn't exist" : finalresult[1];
    if (opt == "+") return process = 1;
    else if (opt == "-") return process = 2;
    else if (opt == "*") return process = 3;
    else if (opt == "/") return process = 4;
    else if (opt == "^") return process = 5;
    else if (opt == "=") return process = 6;
}

//calculate the input text by check_case and return_process
long double Texttomath::calculate() { 
    int case_index = checkcase(processtext);
    long double num1 = 0;
    long double num2 = 0; 
    uint16_t process_index = Return_process();

    if (is_error) {
        cout << "Error: Calculation cannot proceed due to invalid input format." << endl;
        return 0.0;
    }

    switch (case_index) {
    case 1:
        num1 = stold(finalresult[0]);
        num2 = stold(finalresult[2]);
        break;
    case 2:
        num1 = findnumberat(finalresult[0]);
        num2 = findnumberat(finalresult[2]);
        break;
    case 3:
        if (process_index == 6) {
            external_name[count] = (finalresult[0]);
            external_value[count] = stold(finalresult[2]);
            break;
        }
        else {
            num1 = findnumberat(finalresult[0]);
            num2 = stold(finalresult[2]);
            break;
        }
    case 4:
        num1 = stold(finalresult[0]);
        num2 = findnumberat(finalresult[2]);
        break;
    default:
        cout << "Invalid calculation case!" << endl;
        return 0.0;
    }

    switch (process_index) {
    case 1: return num1 + num2; break;
    case 2: return num1 - num2; break;
    case 3: return num1 * num2; break;
    case 4: return (num2 != 0) ? num1 / num2 : (cout << "Error: Division by zero." << endl, 0.0); break;
    case 5: return pow(num1, num2); break;
    case 6: cout << "variable initialization" << endl; break;
    default:
        cout << "No valid operation found." << endl;
        return 0;
        break;
    }
}

//debug function. Show all of infomations 
void Texttomath::debug() {  
    cout << "Processed text: " << processtext << endl;
    cout << "Operation code: " << Return_process() << endl;
    cout << "Case code: " << checkcase(processtext) << endl;
    cout << "Is external variable: " << is_external_variable << endl;

    if (!is_external_variable) {
        cout << "Number1: " << stod(finalresult[0]) << ", Number2: " << stod(finalresult[2]) << endl;
    } else {
        display_variable();
    }

    cout << "Answer: " << calculate() << endl;
}

// function to show varible in arrange ways
void Texttomath::display_variable() { 
    for(uint16_t i = 0; i < MAX_VAR; i++) {
        string ptr = external_name[i];
        if (ptr != "") { cout << "[" << external_name[i] << "=" << external_value[i] << "] "; }
        else { cout << "[variable not intialize] "; }

        if (i%2 == 0) { cout << endl; }
    }
    cout << endl;
}
