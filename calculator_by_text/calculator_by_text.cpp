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
            cout << "Good bye see you next time" << endl;
            break;
        }
        else if (input == "help") 
        {
            cout << "-----------------------------------------------------------------------------\nThis program convert text input into math calculation base on user input\nExample\nx = 20\nx + 2\nOUTPUT = 22\nthere are 7 operator\n1 : + \n2 : - \n3 : * \n4 : / \n5 : ^ \n6 : ! \n7 : = \nans variable will store the answer value\nAlso this program can calculate up to 1E-160 floating point\nAllow up to 1E-64 vaiable\nsupport multi-character variable name\n-----------------------------------------------------------------------------\n";
        }
        else if (input == "mean") {
            cout << "mean of list : " << mathProcessor.mean() << endl;
            cout << "-----------------------------------" << endl;
        }
        else if (input == "total") {
            cout << "total of list : " << mathProcessor.total() << endl;
            cout << "-----------------------------------" << endl;
        }
        else
        {
            mathProcessor.Texttomathdisplay(0);
        }


    } while (input != "exit");
    

    cout << "program exit" << endl;
    return 0;
}
