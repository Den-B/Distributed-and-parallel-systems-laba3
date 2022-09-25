#include "DeductibleClass.h"

DeductibleClass::DeductibleClass(int Number, int Module_value) {
	if (Module_value <= 1)throw incorrect_input_data_exception("wrong module value");
	this->module_value = Module_value;
	this->value = Number;
}

void DeductibleClass::setNumber(int Number) {
	value = ultimate_mathematics::normalize_the_number(Number, module_value);
}

int DeductibleClass::getValue() {
	return value;
}

int DeductibleClass::getModule()
{
	return module_value;
}

bool DeductibleClass::moreThan(BasicDataType* SecondValue)
{
	try {

		DeductibleClass* buffer = dynamic_cast<DeductibleClass*>(SecondValue);
		return this->getValue() > buffer->getValue();

	}
	catch (bad_cast exception) {
		throw incorrect_input_data_exception("wrong type");
	}
}

string DeductibleClass::convertToString()
{
	return to_string(value)+"(mod "+to_string(module_value)+")";
}



BasicDataType* DeductibleClass::addition(BasicDataType* Second_value)
{
	try {
		DeductibleClass* buffer = dynamic_cast<DeductibleClass*>(Second_value);
		return new DeductibleClass(ultimate_mathematics::normalize_the_number(this->getValue() + buffer->getValue(), this->module_value), this->module_value);
	}
	catch (bad_cast exception) {
		throw  number_cast_exception("wrong type");
	}
}


BasicDataType* DeductibleClass::multiplication(BasicDataType* Second_value)
{
	try {
		DeductibleClass* buffer = dynamic_cast<DeductibleClass*>(Second_value);
		return new DeductibleClass(ultimate_mathematics::normalize_the_number(this->getValue() * buffer->getValue(), this->module_value), this->module_value);
	}
	catch (bad_cast exception) {
		throw number_cast_exception("wrong type");
	}
}

BasicDataType* DeductibleClass::getNeutralElementWithRespectToAddition()
{
	return new DeductibleClass(0,this->module_value);

}

BasicDataType* DeductibleClass::getNeutralElementWithRespectToMultiplication()
{
	return new DeductibleClass(1,this->module_value);
}

NumberDataType* DeductibleClass::multiplicationByReverseElement(NumberDataType* Second_value) {
	try {
		DeductibleClass* buffer = dynamic_cast<DeductibleClass*>(Second_value);
		DeductibleClass reverse =DeductibleClass(ultimate_mathematics::InverseBezu(buffer->getValue(), buffer->getModule()),buffer->getModule());
		return new DeductibleClass(ultimate_mathematics::normalize_the_number(dynamic_cast<DeductibleClass*>(this->multiplication(&reverse))->getValue(), this->module_value) , this->module_value);

	}
	catch (bad_cast exception) {
		throw incorrect_input_data_exception("wrong type");
	}
}


NumberDataType* DeductibleClass::inverseOfAddition() {
	return new DeductibleClass(ultimate_mathematics::normalize_the_number(-1 * this->getValue(),this->module_value),this->module_value);
}




vector<NumberDataType*> DeductibleClass::searchingForMultipliersForLeastCommonMultiple(NumberDataType* Second_value) {
	try {
		DeductibleClass* buffer = dynamic_cast<DeductibleClass*>(Second_value);
		return  { new DeductibleClass(buffer->getValue(),this->module_value),new DeductibleClass(this->getValue(),this->module_value) };
	}
	catch (bad_cast exception) {
		throw incorrect_input_data_exception("wrong type");
	}

}


NumberDataType* DeductibleClass::reduceValuesOfNumbersInArrays(vector<NumberDataType*> top_array, vector<NumberDataType*> bottom_array) {
	try {
		
		NumberDataType* top_value = dynamic_cast<NumberDataType*>(this->getNeutralElementWithRespectToMultiplication());
		for (vector<NumberDataType*>::iterator array_iter = top_array.begin(); array_iter != top_array.end(); array_iter++) {
				top_value = dynamic_cast<NumberDataType*>(top_value->multiplication(*array_iter));
		}

		NumberDataType* bottom_value = dynamic_cast<NumberDataType*>(this->getNeutralElementWithRespectToMultiplication());
		for (vector<NumberDataType*>::iterator array_iter = bottom_array.begin(); array_iter != bottom_array.end(); array_iter++) {
			bottom_value = dynamic_cast<NumberDataType*>(bottom_value->multiplication(*array_iter));
		}
		
		NumberDataType* buffer =  (top_value)->multiplicationByReverseElement(bottom_value);

		delete top_value;
		delete bottom_value;
		return new DeductibleClass(dynamic_cast<DeductibleClass*>(buffer)->getValue(),this->getModule());
	}
	catch (bad_cast exception) {
		throw incorrect_input_data_exception("wrong type");
	}
}

bool DeductibleClass::equal(BasicDataType* Second_value)
{
	try {
		DeductibleClass* buffer = dynamic_cast<DeductibleClass*>(Second_value);
		return this->getValue() == buffer->getValue();

	}
	catch (bad_cast exception) {
		throw incorrect_input_data_exception("wrong type");
	}
}

BasicDataType* DeductibleClass::clone()
{
	return new DeductibleClass(this->value,this->module_value);
}

ObjectTypeManager* DeductibleClass::GetControlTypeObject(int Module_value)
{
	return new ObjectTypeManager(new DeductibleClass(0,Module_value));
}


NumberDataType* DeductibleClass::findSquareRoot(){
	return new DeductibleClass(sqrt(this->getValue()), this->getModule());
}

NumberDataType* DeductibleClass::absoluteValue(){
	return new DeductibleClass(abs(value), this->getModule());
}
