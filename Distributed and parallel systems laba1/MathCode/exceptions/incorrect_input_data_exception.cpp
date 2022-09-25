#include "incorrect_input_data_exception.h"


incorrect_input_data_exception::incorrect_input_data_exception() {
    type_of_error = "incorrect_input_data_exception";
}

incorrect_input_data_exception::incorrect_input_data_exception(string  error_reason) {
    this->error_reason = error_reason;
    type_of_error = "incorrect_input_data_exception";
}