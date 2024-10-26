#include <iostream>
#include "stringtoprocess.h"
using namespace std;


int main() {
    string input = "10ZZ + 5"; // Example input
    Texttomath mathProcessor(input);

    mathProcessor.print_text_test(); // Outputs processed results and answer
    return 0;
}
