#include "multiplicative_ring_classes_of_deductions .h"


vector<DeductibleClass> multiplicative_ring_classes_of_deductions::find_a_set_of_degrees(int number, int module_value) {
	if (module_value <= 1)throw incorrect_input_data_exception("Wrong module");
	vector<DeductibleClass> result;
	DeductibleClass first(number, module_value);
	DeductibleClass passerby(number, module_value);
	do {
		result.push_back(passerby);
		DeductibleClass* buffer = dynamic_cast<DeductibleClass*>(passerby.multiplication(&first));
		passerby = *buffer;
		delete buffer;
	} while ((!(passerby.equal(&first)) && (!(passerby.equal(passerby.getNeutralElementWithRespectToAddition())))));
	if(passerby.equal(passerby.getNeutralElementWithRespectToAddition()))result.push_back(passerby);

	return result;
}

bool multiplicative_ring_classes_of_deductions::does_the_set_of_degrees_form_a_group(int number, int module_value) {
	if (module_value <= 1)throw incorrect_input_data_exception("Wrong module");
	vector<DeductibleClass>set_of_degrees = multiplicative_ring_classes_of_deductions::find_a_set_of_degrees(number, module_value);
	DeductibleClass one(1,module_value);
	for (vector<DeductibleClass>::iterator iter = set_of_degrees.begin(); iter != set_of_degrees.end(); iter++){
		if (one.equal(&(*iter))) return true;
	}
	return false;
}

bool multiplicative_ring_classes_of_deductions::does_the_set_of_degrees_form_a_group(vector<DeductibleClass> set,int module_value){
	if (module_value <= 1)throw incorrect_input_data_exception("wrong module value");
	vector<DeductibleClass>set_of_degrees = set;
	DeductibleClass one(1, module_value);
	for (vector<DeductibleClass>::iterator iter = set_of_degrees.begin(); iter != set_of_degrees.end(); iter++) {
		if (one.equal(&(*iter))) return true;
	}
	return false;
}

int multiplicative_ring_classes_of_deductions::find_the_order_of_the_group(int number, int module_value){
	vector<DeductibleClass> set = find_a_set_of_degrees(number, module_value);
	if (does_the_set_of_degrees_form_a_group(set,module_value)) {
		return set.size();
	}
	else throw incorrect_input_data_exception("this is not group");
}

bool multiplicative_ring_classes_of_deductions::is_it_a_cyclical_group(){
	for (vector<DeductibleClass>::iterator set_iter = array_of_classes.begin(); set_iter != array_of_classes.end(); set_iter++) {
		if (this->is_this_the_primordial_root(*set_iter)) return true;
	}
	return false;
}

vector<DeductibleClass> multiplicative_ring_classes_of_deductions::find_all_primordial_roots(){
	if (!this->is_it_a_cyclical_group())throw number_exception("this is not a cyclical group");
	vector<DeductibleClass>result_vector;
	for (vector<DeductibleClass>::iterator set_iter = array_of_classes.begin(); set_iter != array_of_classes.end(); set_iter++) {
		if (this->is_this_the_primordial_root(*set_iter))result_vector.push_back(*set_iter);
	}
	return result_vector;
}

bool multiplicative_ring_classes_of_deductions::is_this_the_primordial_root(DeductibleClass number){
	vector<DeductibleClass> set = find_a_set_of_degrees(number.getValue(), module_value);
	if (set.size() == ultimate_mathematics::Euler_function_in_common_case(module_value)) return true;
	else return false;
}

bool multiplicative_ring_classes_of_deductions::is_this_the_primordial_root(int root,int module_value){
	vector<DeductibleClass> set = find_a_set_of_degrees(root,module_value);
	if (set.size() == ultimate_mathematics::Euler_function_in_common_case(module_value)) return true;
	else return false;
}

int multiplicative_ring_classes_of_deductions::get_size(){
	return size;
}

int multiplicative_ring_classes_of_deductions::the_order_of_the()
{
	return array_of_classes.size();
}

multiplicative_ring_classes_of_deductions::multiplicative_ring_classes_of_deductions(int Module_value) {

	if (Module_value <= 1)throw incorrect_input_data_exception("wrong module value");
	module_value = Module_value;
	for (int i = 0; i < module_value; i++) {
		if (ultimate_mathematics::NodEuclidean(i, module_value) == 1) {
			array_of_classes.push_back(DeductibleClass(i, this->module_value));
		}
	}
	size = array_of_classes.size();
}


DeductibleClass* multiplicative_ring_classes_of_deductions::perform_an_multiplication_operation(DeductibleClass* first_number, DeductibleClass* second_number) {
	
	return dynamic_cast<DeductibleClass*>(first_number->multiplication(second_number));

}

vector<DeductibleClass> multiplicative_ring_classes_of_deductions::get_array_of_classes(){
	return this->array_of_classes;
}

void multiplicative_ring_classes_of_deductions::set_number(DeductibleClass number, int position) {
	if (array_of_classes.size() <= position)throw incorrect_input_data_exception("out of range");
	array_of_classes[position] = number;
}

DeductibleClass multiplicative_ring_classes_of_deductions::get_number(int position){
	if (array_of_classes.size() <= position)throw incorrect_input_data_exception("out of range");
	return array_of_classes[position];
}
