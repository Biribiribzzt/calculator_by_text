#pragma once

#include<iostream>
#include<string>
#include<vector>
#include<sstream>

#define MAX_VAR 30

using namespace std;

class Texttomath {
public:
    //constrctor
    Texttomath(string input);
    Texttomath(string input, uint16_t show_debug);
    //count of class create
    static uint32_t count;

    //function to call
    void display_variable(); //display all of variable
    void debug();
    long double calculate();
private:
    //input text
    string processtext;

    //array 
    const int max = MAX_VAR;
    string finalresult[3];           
    static string external_name[MAX_VAR];
    static long double external_value[MAX_VAR];

    //variable of int
    uint16_t process;
    uint16_t internal_number;

    //variable of bool
    bool is_external_variable;
    bool is_assinging;
    bool test = false;
    bool is_error = false;

    //function 
    long double findnumberat(const string& content); //this function find by searching input text
    uint16_t checkcase(const string& context); //this check if any of input are text suitable for variable
    uint16_t Return_process();
    void splitString(const string& str, string& part1, string& part2, string& part3); //this function split string
};

