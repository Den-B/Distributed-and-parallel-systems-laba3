#pragma once
#include "number_exception.h"
class number_cast_exception :
    public number_exception
{

 public:
     number_cast_exception();
     number_cast_exception(string  error_reason);

};

