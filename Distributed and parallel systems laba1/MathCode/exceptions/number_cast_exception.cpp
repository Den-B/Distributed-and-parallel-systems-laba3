#include "number_cast_exception.h"


number_cast_exception::number_cast_exception() {
    type_of_error = "number_cast_exception";
}

number_cast_exception::number_cast_exception(string  error_reason) {
    this->error_reason = error_reason;
    type_of_error = "number_cast_exception";
}