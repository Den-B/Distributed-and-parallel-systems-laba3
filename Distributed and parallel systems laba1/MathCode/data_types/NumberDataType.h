#pragma once
#include "BasicDataType.h"
#include <vector>

class NumberDataType :
    public BasicDataType
{

public:

    virtual vector<NumberDataType*> searchingForMultipliersForLeastCommonMultiple(NumberDataType* Second_value) = 0;
    virtual NumberDataType* inverseOfAddition() = 0;
    virtual NumberDataType* multiplicationByReverseElement(NumberDataType* Second_value) = 0;
    virtual NumberDataType* reduceValuesOfNumbersInArrays(vector<NumberDataType*>top_array, vector<NumberDataType*> bottom_array) = 0;
    virtual NumberDataType* findSquareRoot() = 0;
    virtual NumberDataType* absoluteValue() = 0;
};

