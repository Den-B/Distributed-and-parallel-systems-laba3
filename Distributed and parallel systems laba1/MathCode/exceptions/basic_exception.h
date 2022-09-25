#pragma once
#include <string>
#include <Windows.h>
#include <exception>
#include <vector>
using namespace std;

class basic_exception :public exception {
protected:
    string error_reason = "null";
    string type_of_error = "encoder_exception";

 
public:

    basic_exception();
    basic_exception(string error_reason);
    string what_is_the_reason_for_this_error();
    string what_type_of_error();
    string full_information_about_current_error();
    void set_reason(string reason);
    void set_type_of_error(string type);


};