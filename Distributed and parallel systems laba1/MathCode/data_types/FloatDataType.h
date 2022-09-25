#pragma once
#include "NumberDataType.h"

#include <algorithm>
#include <cmath>
#include <string>
#include <typeinfo>
#include "../exceptions/incorrect_input_data_exception.h"
#include "NumberDataType.h"
#include "ObjectTypeManager.h"
#include "../exceptions/number_cast_exception.h"


using namespace std;

class FloatDataType :
  public NumberDataType
{
private:
	 long double number = 0.0;
	 int rounding_accuracy = 10000;
	 FloatDataType* round_double_data_type();

public:
	FloatDataType() = default;
	FloatDataType(double Number);
	double getValue();
	static ObjectTypeManager* GetControlTypeObject();
	static FloatDataType* round_double_data_type(double number, int rounding_accuracy);


	// Унаследовано через NumberDataType
	virtual BasicDataType* addition(BasicDataType* SecondValue) override;
	virtual BasicDataType* multiplication(BasicDataType* SecondValue) override;
	virtual BasicDataType* getNeutralElementWithRespectToAddition() override;
	virtual BasicDataType* getNeutralElementWithRespectToMultiplication() override;
	virtual BasicDataType* clone() override;
	virtual string convertToString() override;
	virtual bool moreThan(BasicDataType* SecondValue) override;
	virtual vector<NumberDataType*> searchingForMultipliersForLeastCommonMultiple(NumberDataType* Second_value) override;
	virtual NumberDataType* inverseOfAddition() override;
	virtual NumberDataType* multiplicationByReverseElement(NumberDataType* Second_value) override;
	virtual NumberDataType* reduceValuesOfNumbersInArrays(vector<NumberDataType*> top_array, vector<NumberDataType*> bottom_array) override;
	virtual NumberDataType* findSquareRoot() override;
	virtual NumberDataType* absoluteValue() override;
	virtual bool equal(BasicDataType* SecondValue) override;

	virtual ~FloatDataType();

};

