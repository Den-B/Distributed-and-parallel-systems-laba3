#pragma once
#include "BasicDataType.h"
class ObjectTypeManager
{
private:
	BasicDataType* object;
public:

	ObjectTypeManager(BasicDataType* Object);
	ObjectTypeManager(ObjectTypeManager& other);
	BasicDataType* getNeutralElementWithRespectToAddition();
	BasicDataType* getNeutralElementWithRespectToMultiplication();
	BasicDataType* getAccessToObject();
	ObjectTypeManager* clone();
	~ObjectTypeManager();

};

