#include "basic_exception.h"
using namespace std;



basic_exception::basic_exception() {
    
}

basic_exception::basic_exception(string error_reason) {
    this->error_reason = error_reason;
}


string basic_exception::what_is_the_reason_for_this_error() {
    return error_reason;
}

string basic_exception::what_type_of_error() {
    return type_of_error;
}


string basic_exception::full_information_about_current_error() {

    string buffer_string;
    buffer_string = "Current reason: " + error_reason;
    buffer_string += +".\nType of error: " + type_of_error + ".";
    return buffer_string;

}


void basic_exception::set_reason(string reason){
    this->error_reason = reason;
}

void basic_exception::set_type_of_error(string type){
    this->type_of_error = type;
}



