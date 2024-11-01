#include <iostream>
#include "stringtoprocess.h"


using namespace std;


int main() {
    string input;

    do { //loop for continous calculation

        cout << "Please input the number or variable" << endl;
        getline(cin, input);

        Texttomath mathProcessor(input);

        if (input == "show")
        {
            mathProcessor.display_variable();
        }
        else if (input == "exit") 
        {
            cout << "Good bye see you next time บ้ายบาย" << endl;
        }
        else
        {
            mathProcessor.Texttomathdisplay(0);
        }

    } while (input != "exit");
    

    cout << "program exit" << endl;
    return 0;
}
