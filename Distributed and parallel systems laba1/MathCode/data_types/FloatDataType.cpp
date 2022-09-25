#include "FloatDataType.h"

string FloatDataType::convertToString() {
	return std::to_string(number);
}

BasicDataType* FloatDataType::addition(BasicDataType* Second_value)
{
	try {
		FloatDataType* buffer = dynamic_cast<FloatDataType*>(Second_value);
		return round_double_data_type(this->number + buffer->getValue(), this->rounding_accuracy);
	}
	catch (bad_cast exception) {
		throw  number_cast_exception("wrong type");
	}
}


BasicDataType* FloatDataType::multiplication(BasicDataType* Second_value)
{
	try {
		FloatDataType* buffer = dynamic_cast<FloatDataType*>(Second_value);
		return round_double_data_type(this->getValue() * buffer->number, this->rounding_accuracy);

	}
	catch (bad_cast exception) {
		throw number_cast_exception("wrong type");
	}
}

BasicDataType* FloatDataType::getNeutralElementWithRespectToAddition()
{
	return new FloatDataType(0.0);

}

BasicDataType* FloatDataType::getNeutralElementWithRespectToMultiplication()
{
	return new FloatDataType(1.0);
}

NumberDataType* FloatDataType::multiplicationByReverseElement(NumberDataType* Second_value) {
	try {
		FloatDataType* buffer = dynamic_cast<FloatDataType*>(Second_value);
		return round_double_data_type(this->getValue() / buffer->getValue(),this->rounding_accuracy);

	}
	catch (bad_cast exception) {
		throw incorrect_input_data_exception("wrong type");
	}
}

NumberDataType* FloatDataType::inverseOfAddition() {
	return new FloatDataType(-1.0 * this->getValue());
}

vector<NumberDataType*> FloatDataType::searchingForMultipliersForLeastCommonMultiple(NumberDataType* Second_value) {
	try {
		FloatDataType* buffer = dynamic_cast<FloatDataType*>(Second_value);
		return { buffer->round_double_data_type(),this->round_double_data_type() };

	}
	catch (bad_cast exception) {
		throw incorrect_input_data_exception("wrong type");
	}

}


NumberDataType* FloatDataType::reduceValuesOfNumbersInArrays(vector<NumberDataType*> top_array, vector<NumberDataType*> bottom_array) {
	try {

		for (int i = 0; i < top_array.size() && (top_array.size() <= bottom_array.size() || i < bottom_array.size()); i++) {
			top_array[i] = top_array[i]->multiplicationByReverseElement(bottom_array[i]);
		}

		FloatDataType* top_number = dynamic_cast<FloatDataType*>(this->getNeutralElementWithRespectToMultiplication());
		for (vector<NumberDataType*>::iterator number_iter = top_array.begin(); number_iter != top_array.end(); number_iter++) {
			top_number = dynamic_cast<FloatDataType*>((top_number)->multiplication(*number_iter));
		}
		if (top_array.size() > bottom_array.size()) return top_number;
		for (int i = 0; i < top_array.size(); i++) {
			bottom_array.erase(bottom_array.begin());
		}


		FloatDataType* bottom_number = dynamic_cast<FloatDataType*>(this->getNeutralElementWithRespectToMultiplication());
		for (vector<NumberDataType*>::iterator number_iter = bottom_array.begin(); number_iter != bottom_array.end(); number_iter++) {
			bottom_number = dynamic_cast<FloatDataType*>(bottom_number->multiplication(*number_iter));
		}
		return round_double_data_type(top_number->getValue() / bottom_number->getValue(), this->rounding_accuracy);
	}
	catch (bad_cast exception) {
		throw incorrect_input_data_exception("wrong type");
	}
}

bool FloatDataType::equal(BasicDataType* Second_value)
{
	try {
		FloatDataType* buffer = dynamic_cast<FloatDataType*>(Second_value);
		return fabs(this->getValue() - buffer->getValue()) < std::numeric_limits<double>::epsilon();

	}
	catch (bad_cast exception) {
		throw incorrect_input_data_exception("wrong type");
	}
}

FloatDataType::~FloatDataType()
{

}


BasicDataType* FloatDataType::clone()
{
	return new FloatDataType(this->number);
}

bool FloatDataType::moreThan(BasicDataType* Second_value){
	try {
		FloatDataType* buffer = dynamic_cast<FloatDataType*>(Second_value);
		return this->getValue() > buffer ->getValue();

	}
	catch (bad_cast exception) {
		throw incorrect_input_data_exception("wrong type");
	}
}


ObjectTypeManager* FloatDataType::GetControlTypeObject()
{
	return new ObjectTypeManager(new FloatDataType());
}

FloatDataType* FloatDataType::round_double_data_type(){

	return new FloatDataType(round(this->number* rounding_accuracy)/ rounding_accuracy);

}

FloatDataType* FloatDataType::round_double_data_type(double number,int rounding_accuracy){
	return  new FloatDataType(round(number * rounding_accuracy) / rounding_accuracy);
}

NumberDataType* FloatDataType::findSquareRoot(){

	return new FloatDataType(sqrt(this->getValue()));
}

NumberDataType* FloatDataType::absoluteValue(){
	return new FloatDataType(abs(number));
}



FloatDataType::FloatDataType(double Number) {
	number = Number;

}

double FloatDataType::getValue() {
	return number;
}