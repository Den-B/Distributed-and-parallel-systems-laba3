#pragma once

#include "../math/ultimate_mathematics.h"
#include "NumberDataType.h"
#include "ObjectTypeManager.h"


using namespace std;
class DeductibleClass: public NumberDataType{
private:

	int module_value;
	int value = 0;

public:
	
	DeductibleClass(int Number, int Module_number);
	
	void setNumber(int Number);
	int getValue();
	int getModule();
	virtual bool moreThan(BasicDataType* Second_value);
	static	ObjectTypeManager* GetControlTypeObject(int module_value);
	

	// Унаследовано через NumberDataType
	virtual BasicDataType* addition(BasicDataType* SecondValue) override;
	virtual BasicDataType* multiplication(BasicDataType* SecondValue) override;
	virtual BasicDataType* getNeutralElementWithRespectToAddition() override;
	virtual BasicDataType* getNeutralElementWithRespectToMultiplication() override;
	virtual BasicDataType* clone() override;
	virtual string convertToString() override;
	virtual bool equal(BasicDataType* SecondValue) override;
	virtual vector<NumberDataType*> searchingForMultipliersForLeastCommonMultiple(NumberDataType* Second_value) override;
	virtual NumberDataType* inverseOfAddition() override;
	virtual NumberDataType* multiplicationByReverseElement(NumberDataType* Second_value) override;
	virtual NumberDataType* reduceValuesOfNumbersInArrays(vector<NumberDataType*> top_array, vector<NumberDataType*> bottom_array) override;
	virtual NumberDataType* findSquareRoot() override;
	virtual NumberDataType* absoluteValue() override;

};

