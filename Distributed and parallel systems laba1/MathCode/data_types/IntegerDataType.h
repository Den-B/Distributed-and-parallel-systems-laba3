#pragma once

#include <string>
#include <typeinfo>
#include "../exceptions/incorrect_input_data_exception.h"
#include "NumberDataType.h"
#include "ObjectTypeManager.h"
#include "../exceptions/number_cast_exception.h"
#include "../math/ultimate_mathematics.h"

using namespace std;

class IntegerDataType :public NumberDataType {
private:
	long long int number = 0;


public:

	IntegerDataType() = default;
	IntegerDataType(int Number);
	static ObjectTypeManager* GetControlTypeObject();
	int getValue();

	// Унаследовано через NumberDataType
	virtual BasicDataType* addition(BasicDataType* SecondValue) override;
	virtual BasicDataType* multiplication(BasicDataType* SecondValue) override;
	virtual BasicDataType* getNeutralElementWithRespectToAddition() override;
	virtual BasicDataType* getNeutralElementWithRespectToMultiplication() override;
	virtual BasicDataType* clone() override;
	virtual bool equal(BasicDataType* SecondValue) override;
	virtual bool moreThan(BasicDataType* SecondValue) override;
	virtual vector<NumberDataType*> searchingForMultipliersForLeastCommonMultiple(NumberDataType* Second_value) override;
	virtual NumberDataType* inverseOfAddition() override;
	virtual NumberDataType* multiplicationByReverseElement(NumberDataType* Second_value) override;
	virtual NumberDataType* reduceValuesOfNumbersInArrays(vector<NumberDataType*> top_array, vector<NumberDataType*> bottom_array) override;
	virtual string convertToString() override;
	virtual NumberDataType* findSquareRoot() override;
	virtual NumberDataType* absoluteValue() override;


};