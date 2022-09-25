#pragma once
#include <iostream>
#include <vector>
#include "BasicLog.h"
#include "../exceptions/incorrect_input_data_exception.h"
#include "../exceptions/basic_exception.h"



using namespace std;

class BasicConsoleInterface {
protected:

    BasicLog* log;
    string program_name;
    string file_name;

    int readNumber();

public:

    BasicConsoleInterface(string program_name, string recorder_file);
    void lineIntent();
    string getFileName();
    string getProgramName();
    int inputNumber(string what_is_number);
    vector<int> inputNumberArray(string what_is_number, int count_of_numbers);
    string inputString();
    void printResultString(string message);
    void printString(string message);
    void printStringLn(string message);
    void standartPrologue();
    void standartEpilogue();
    BasicLog* getLog();
    void writeExceptionLogInFile(basic_exception exception);
    ~BasicConsoleInterface();

};