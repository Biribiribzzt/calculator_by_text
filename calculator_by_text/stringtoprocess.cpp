#include "stringtoprocess.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
#include <cctype>
#include <algorithm>
#include <iomanip>

using namespace std;

uint32_t Texttomath::count = 1; // Initialize static variable
string Texttomath::external_name[MAX_VAR] = {};
long double Texttomath::external_value[MAX_VAR] = {}; 

// main constrictor
Texttomath::Texttomath(string input) {
    processtext = input;
    temp = 0;
    process = 0;
    internal_number = 0;
    is_external_variable = 0;
    is_assinging = 0;
    is_intialized = 0;
    is_error = 0;

}

Texttomath::Texttomath(string input,uint8_t quick) {
    processtext = input;
    splitString(processtext, finalresult[0], finalresult[1], finalresult[2]);
    external_name[0] = "ans";
    is_error = 0;
    external_value[0] = calculate();
    if(!is_error)
    {
        cout << setprecision(OUT_PRECI) << "Answer : " << external_value[0] << endl;
        cout << "-----------------------------------" << endl;
    }

}

//constrctor2 show debug.
void Texttomath::Texttomathdisplay(uint8_t mode) {
    splitString(processtext, finalresult[0], finalresult[1], finalresult[2]);
    external_name[0] = "ans";
    external_value[0] = calculate();
    if (!is_error)
    {
        cout << setprecision(OUT_PRECI) << "Answer : " << external_value[0] << endl;
        cout << "-----------------------------------" << endl;
    }

    if(mode == 1)
    {
        for (int i = 0; i < 3; i++) {
            cout << finalresult[i] << endl;
        }
        debug();
    }
}

//checkcase of variable 
uint8_t Texttomath::checkcase(const string& context) {
    splitString(context, finalresult[0], finalresult[1], finalresult[2]);

    if (finalresult[0].empty() || finalresult[2].empty()) {
        cout << "Error: Invalid input format." << std::endl;
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

void Texttomath::splitString(const string& str, string& part1, string& part2, string& part3) {
    string trimmedStr = str;

    // Remove any spaces from the string
    trimmedStr.erase(remove(trimmedStr.begin(), trimmedStr.end(), ' '), trimmedStr.end());

    // Look for the position of the operator (+, -, *, /) in the string
    size_t operatorPos = string::npos;
    for (size_t i = 0; i < trimmedStr.size(); ++i) {
        if (trimmedStr[i] == '+' || trimmedStr[i] == '-' || trimmedStr[i] == '*' || trimmedStr[i] == '/' || trimmedStr[i] == '^' || trimmedStr[i] == '!' || trimmedStr[i] == '=' || trimmedStr[i] == '$') {
            operatorPos = i;
            break;
        }
    }

    // If an operator is found, split the string into two parts based on the operator
    if (operatorPos != string::npos) {
        // Part 1: The substring before the operator
        part1 = trimmedStr.substr(0, operatorPos);

        // Part 2: The operator itself
        part2 = string(1, trimmedStr[operatorPos]);

        // Part 3: The substring after the operator
        part3 = trimmedStr.substr(operatorPos + 1);
    }
    else {
        // If no operator is found, it's an invalid format
        part1 = part2 = part3 = "";
    }
}

 //find number in other array by seaching text
long double Texttomath::findnumberat(const string& content) {
    for (size_t i = 0; i < MAX_VAR; ++i) {
        if (external_name[i] == content) {
            return external_value[i];
        }
    }
    cout << "Variable " << content << " not found!" << endl; is_error = true;
    return 0.0;
}

//Return the operator of text
uint8_t Texttomath::Return_process() { 
    string opt = finalresult[1].empty() ? "Operator doesn't exist" : finalresult[1];
    if (opt == "+") return process = 1;
    else if (opt == "-") return process = 2;
    else if (opt == "*") return process = 3;
    else if (opt == "/") return process = 4;
    else if (opt == "^") return process = 5;
    else if (opt == "=") return process = 6;
    else if (opt == "!") return process = 7;
    else if (opt == "$") return process = 8;
    else return 404;
}

long double factorial(int n) {
    if (n < 0) return 0; // Factorial is not defined for negative numbers
    if (n == 0) return 1; // Base case: 0! = 1
    long double result = 1;
    for (int i = 1; i <= n; ++i) {
        result *= i;
    }
    return result;
}

long double squreroot(int n) {
    return sqrtl(n);
}

//calculate the input text by check_case and return_process
long double Texttomath::calculate() { 
    int case_index = checkcase(processtext);
    long double num1 = 0;
    long double num2 = 0; 
    uint8_t process_index = Return_process();

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
        if (process_index == 6) {
            num1 = assign(finalresult[0], findnumberat(finalresult[2]));
            is_external_variable = 1;
            break;
        }
        else {
            num1 = findnumberat(finalresult[0]);
            num2 = findnumberat(finalresult[2]);
            is_external_variable = 1;
            break;
        }
    case 3:
        if (process_index == 6) {
            num1 = assign(finalresult[0], stold(finalresult[2]));
            is_external_variable = 1;
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
        cout << "Couldn't recogize text and number." << endl;
        return 0.0;
    }

    switch (process_index) {
    case 1: return num1 + num2; break;
    case 2: return num1 - num2; break;
    case 3: return num1 * num2; break;
    case 4: return (num2 != 0) ? num1 / num2 : (cout << "Error: Division by zero." << endl, 0.0); break;
    case 5: return pow(num1, num2); break;
    case 6: if (is_intialized) { cout << "variable intialized" << endl; } is_error = 1; return num1; break;
    case 7: return factorial(num1); break;
    case 8: return squreroot(num1); break;
    default:
        cout << "No valid operation found." << endl;
        return 0;
        break;
    }

    return 0;
}

//debug function. Show all of infomations 
void Texttomath::debug() {  
    cout << "Processed text: " << processtext << endl;
    cout << "Operation code: " << finalresult[1] << endl;
    cout << "Case code: " << checkcase(processtext) << endl;
    cout << "Is external variable: " << is_external_variable << endl;

    if (!is_external_variable) {
        cout << "Number1: " << stold(finalresult[0]) << ", Number2: " << stod(finalresult[2]) << endl;
    } else {
        display_variable();
    }

    cout << "Answer: " << calculate() << endl;
}

// function to show varible in arrange ways
void Texttomath::display_variable() { 
    for(uint64_t i = 0; i < MAX_VAR; i++) {
        string ptr = external_name[i];
        if (ptr != "") { cout << "[" << external_name[i] << "=" << external_value[i] << "] "; }
        else { cout << "[variable not intialize] "; }

        if (i%2 == 0) { cout << endl; }
    }
    cout << endl;
}

long double Texttomath::assign(const string name,long double value) {
    bool is_repeated = false;
    for (uint64_t i = 0; i < MAX_VAR; ++i) {
        if (external_name[i] == name) {
            external_value[i] = value;
            is_repeated = true;
            break;
        }
        else {
            is_repeated = false;
        }
    }
    if (is_repeated == false) 
    {
        if(count < MAX_VAR)
        {
            external_name[count] = name;
            external_value[count] = value;
            count++;
        }
        else
        {
            cout << "variable exceed the limit" << endl;
        }
    }
    is_intialized = true;
    return value;
}

long double Texttomath::mean() {
    long double total = 0;
    long double count1 = 0;
    if(count > 1)
    {
        for (int i = 1; i < count; i++) {
            total += external_value[i];
            count1++;

        }
        return total / count1;
    }
    else {
        cout << "too few variable" << endl;
        return 0;
    }

}

long double Texttomath::total() {
    long double total = 0;
    if (count > 1)
    {
        for (int i = 1; i < count; i++) {
            total += external_value[i];
        }
        return total;
    }
    else {
        cout << "too few variable" << endl;
        return 0;
    }

}