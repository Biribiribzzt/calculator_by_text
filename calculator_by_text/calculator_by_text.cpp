#include <iostream>
#include "stringtoprocess.h"
using namespace std;


int main() {
    string input;
    while (input != "exit") {
        getline(cin, input);
        Texttomath mathProcessor(input,1);
    }
    cout << "program exit" << endl;
    return 0;
}
