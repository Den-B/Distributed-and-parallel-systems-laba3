#pragma once
#include <string>
using namespace std;

class BasicDataType {

	public:

	virtual BasicDataType* addition(BasicDataType* SecondValue) = 0;
	virtual BasicDataType* multiplication(BasicDataType* SecondValue) = 0;
	virtual BasicDataType* getNeutralElementWithRespectToAddition() = 0;
	virtual BasicDataType* getNeutralElementWithRespectToMultiplication() = 0;
	virtual BasicDataType* clone() = 0;
	virtual string convertToString() = 0;
	virtual bool equal(BasicDataType* SecondValue) = 0;
	virtual bool moreThan(BasicDataType* SecondValue) = 0;
	virtual ~BasicDataType() = default; 

};
