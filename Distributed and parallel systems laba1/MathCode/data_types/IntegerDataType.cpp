#include "IntegerDataType.h"


std::string IntegerDataType::convertToString() {
	return std::to_string(number);
}

BasicDataType* IntegerDataType::addition(BasicDataType* Second_value)
{
	try {
		IntegerDataType* buffer = dynamic_cast<IntegerDataType*>(Second_value);
		return new IntegerDataType(buffer->getValue() + this->number);
	}
	catch (bad_cast exception) {
		throw  number_cast_exception("wrong type");
	}
}


BasicDataType* IntegerDataType::multiplication(BasicDataType* Second_value)
{
	try {
		IntegerDataType* buffer = dynamic_cast<IntegerDataType*>(Second_value);
		return new IntegerDataType(buffer->getValue()  * this->number);
		
	}
	catch (bad_cast exception) {
		throw number_cast_exception("wrong type");
	}
}


BasicDataType* IntegerDataType::getNeutralElementWithRespectToAddition()
{
	return new IntegerDataType(0);

}

BasicDataType* IntegerDataType::getNeutralElementWithRespectToMultiplication()
{	
	return new IntegerDataType(1);
}

NumberDataType* IntegerDataType::multiplicationByReverseElement(NumberDataType* Second_value){
	try {
		IntegerDataType* buffer = dynamic_cast<IntegerDataType*>(Second_value);
		if (this->getValue() % buffer->getValue() != 0) throw number_exception("it's impossible to divide one number by another");
		return new IntegerDataType(this->getValue()/buffer->getValue());

	}
	catch (bad_cast exception) {
		throw incorrect_input_data_exception("wrong type");
	}
}


NumberDataType* IntegerDataType::inverseOfAddition(){
	return new IntegerDataType(-1*this->getValue());
}


vector<NumberDataType*> IntegerDataType::searchingForMultipliersForLeastCommonMultiple(NumberDataType* Second_value){
	try {
		IntegerDataType* buffer = dynamic_cast<IntegerDataType*>(Second_value);
		int nod = ultimate_mathematics::NodEuclidean(this->getValue(),buffer->getValue());
		return  { new IntegerDataType(buffer->getValue() / nod), new IntegerDataType(this->getValue() / nod) };

	}
	catch (bad_cast exception) {
		throw incorrect_input_data_exception("wrong type");
	}
	
}


NumberDataType* IntegerDataType::reduceValuesOfNumbersInArrays(vector<NumberDataType*> top_array, vector<NumberDataType*> bottom_array){
	try {
		
		bool sign = false; // +
		vector<int>top_integer_array,bottom_integer_array;
		for (vector<NumberDataType*>::iterator array_iter = top_array.begin(); array_iter != top_array.end(); array_iter++) {
			vector<int> factorization_array = ultimate_mathematics::factorization(abs(dynamic_cast<IntegerDataType*>(*array_iter)->getValue()));
			if (dynamic_cast<IntegerDataType*>(*array_iter)->getValue() < 0) sign = !sign;
			for (vector<int>::iterator array_of_dividers_iter = factorization_array.begin(); array_of_dividers_iter != factorization_array.end(); array_of_dividers_iter++) {
				top_integer_array.push_back(*array_of_dividers_iter);
			}
		}

		for (vector<NumberDataType*>::iterator array_iter = bottom_array.begin(); array_iter != bottom_array.end(); array_iter++) {
			vector<int> factorization_array = ultimate_mathematics::factorization(abs(dynamic_cast<IntegerDataType*>(*array_iter)->getValue()));
			if (dynamic_cast<IntegerDataType*>(*array_iter)->getValue() < 0) sign = !sign;
			for (vector<int>::iterator array_of_dividers_iter = factorization_array.begin(); array_of_dividers_iter != factorization_array.end(); array_of_dividers_iter++) {
				bottom_integer_array.push_back(*array_of_dividers_iter);
			}
		}


		for (int i = 0,index_of_offset = 0;i < top_integer_array.size(); i++) {
			bool is_end = false;
			for (vector<int>::iterator first_array_iter = (top_integer_array.begin()+ index_of_offset),second_array = bottom_integer_array.begin(); is_end == false && second_array != bottom_integer_array.end(); second_array++, index_of_offset++) {
				if (*first_array_iter == *second_array) {
					top_integer_array.erase(first_array_iter);
					bottom_integer_array.erase(second_array);
					break;
				}
				else {
					index_of_offset--;
				}

			}
		}

		int top_value =1,bottom_value = 1;
		for (vector<int>::iterator array_iter = top_integer_array.begin(); array_iter != top_integer_array.end(); array_iter++) {
			top_value *= *array_iter;
		}
		for (vector<int>::iterator array_iter =bottom_integer_array.begin(); array_iter != bottom_integer_array.end(); array_iter++) {
			bottom_value *= *array_iter;
		}
		int result = top_value / bottom_value;
		if (sign) return new IntegerDataType((-1)*result);
		else return new IntegerDataType( result);

	}
	catch (bad_cast exception) {
		throw incorrect_input_data_exception("wrong type");
	}
}

bool IntegerDataType::equal(BasicDataType* Second_value)
{
	try{
		IntegerDataType* buffer = dynamic_cast<IntegerDataType*>(Second_value);
		return this->getValue() == buffer->getValue();

	}
	catch (bad_cast exception) {
		throw incorrect_input_data_exception("wrong type");
	}
}

bool IntegerDataType::moreThan(BasicDataType* SecondValue)
{

	try {

		IntegerDataType* buffer = dynamic_cast<IntegerDataType*>(SecondValue);
		return this->getValue() > buffer->getValue();

	}
	catch (bad_cast exception) {
		throw incorrect_input_data_exception("wrong type");
	}
	
}


BasicDataType* IntegerDataType::clone()
{
	return new IntegerDataType(this->number);
}


ObjectTypeManager* IntegerDataType::GetControlTypeObject()
{
	return new ObjectTypeManager(new IntegerDataType());
}


NumberDataType* IntegerDataType::findSquareRoot(){
	return new IntegerDataType(sqrt(this->getValue()));
}

NumberDataType* IntegerDataType::absoluteValue()
{
	return new IntegerDataType(abs(number));
}



IntegerDataType::IntegerDataType(int Number) {
	number = Number;

}

int IntegerDataType::getValue() {
	return number;
}