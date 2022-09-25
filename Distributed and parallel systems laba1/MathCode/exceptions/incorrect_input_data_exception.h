#pragma once
#include "basic_exception.h"
class incorrect_input_data_exception :
    public basic_exception
{
public:
    incorrect_input_data_exception();
    incorrect_input_data_exception(string  error_reason);
};

