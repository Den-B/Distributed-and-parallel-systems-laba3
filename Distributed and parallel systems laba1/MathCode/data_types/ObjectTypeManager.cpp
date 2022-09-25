#include "ObjectTypeManager.h"

ObjectTypeManager::ObjectTypeManager(BasicDataType* Object) {
	object = Object;
}

ObjectTypeManager::ObjectTypeManager(ObjectTypeManager& other)
{
	this->object = other.object->clone();
}
                                  
BasicDataType* ObjectTypeManager::getNeutralElementWithRespectToAddition() {
	return object->getNeutralElementWithRespectToAddition();
}
BasicDataType* ObjectTypeManager::getNeutralElementWithRespectToMultiplication() {
	return object->getNeutralElementWithRespectToMultiplication();
}

BasicDataType* ObjectTypeManager::getAccessToObject()
{
	return object;
}

ObjectTypeManager* ObjectTypeManager::clone()
{
	return new ObjectTypeManager(this->object->clone());
}

ObjectTypeManager::~ObjectTypeManager() {
	delete object;
}
