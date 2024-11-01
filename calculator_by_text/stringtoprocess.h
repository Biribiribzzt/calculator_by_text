#pragma once

#include<iostream>
#include<string>
#include<vector>
#include<sstream>
#include<iomanip>

#define MAX_VAR 30
#define OUT_PRECI 30

using namespace std;

class Texttomath {
public:
    //constrctor
    Texttomath(string input);
    Texttomath(string input,uint8_t quick);
    void Texttomathdisplay(uint8_t show_debug);
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
    uint8_t process;
    uint8_t internal_number;

    //variable of bool
    bool is_external_variable;
    bool is_assinging;
    bool test = false;
    bool is_error = false;

    //temp_variable
    long double temp;

    //function 
    long double assign(const string content, long double value);
    long double findnumberat(const string& content); //this function find by searching input text
    uint8_t checkcase(const string& context); //this check if any of input are text suitable for variable
    uint8_t Return_process();
    void splitString(const string& str, string& part1, string& part2, string& part3); //this function split string
};

