#pragma once
#include "basic_exception.h"

class number_exception :
    public basic_exception
{

public:
   
    number_exception();
    number_exception(string  error_reason);

};

