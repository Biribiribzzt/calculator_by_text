#pragma once

#include<iostream>
#include<string>
#include<vector>
#include<sstream>

using namespace std;

class Texttomath {
public:
    Texttomath(const string& input);
    int Return_process();
    void print_text_test();
    double calculate();

private:

    string processtext;

    vector<string> finalresult;
    vector<string> external_name;
    vector<double> external_value;

    int process;
    int internal_number;

    bool is_external_variable;
    bool is_assinging;
    bool test = true;

    double findnumberat(const string& content);
    int checkcase(const string& context);

    vector<string> splitString(const string& str, char delimiter);
};
