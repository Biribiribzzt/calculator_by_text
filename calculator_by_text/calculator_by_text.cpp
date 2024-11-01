#include <iostream>
#include "stringtoprocess.h"
using namespace std;


int main() {
    string input;
    while (input != "exit") {
        cout << "Please input the number or variable" << endl;
        getline(cin, input);
        Texttomath mathProcessor(input);
        if (input == "show") {
            mathProcessor.display_variable();
        }
        else {
            mathProcessor.Texttomathdisplay(0);
        }
        
    }
    cout << "program exit" << endl;
    return 0;
}
