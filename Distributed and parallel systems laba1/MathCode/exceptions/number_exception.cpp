#include "number_exception.h"


number_exception:: number_exception() {
    type_of_error = "number_exception";
}

number_exception::number_exception(string  error_reason) {
    this->error_reason = error_reason;
    type_of_error = "number_exception";
}
