#pragma once
using namespace std;
#include <fstream>
#include "../exceptions/basic_exception.h"

class BasicLog {
    string log_file_name;
    string program_name;
public:

    BasicLog(string program_name,string file_name);
    void writeInFile(string message);
    void standartPrologue();
    void standartEpilogue();
    void printExceptionLog(basic_exception exception);
};