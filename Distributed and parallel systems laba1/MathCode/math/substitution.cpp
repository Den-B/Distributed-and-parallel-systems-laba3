#include "substitution.h"

void substitution::ñheck_the_uniqueness_of_the_numbers_displayed(vector<BasicDataType*> set_of_data){
	for (vector<BasicDataType*>::iterator iter = set_of_data.begin(); iter != set_of_data.end(); iter++) {
		for (vector<BasicDataType*>::iterator inner_iter = (iter + 1); inner_iter != set_of_data.end(); inner_iter++) {
			if ((*inner_iter)->equal(*iter))throw incorrect_input_data_exception("It's not unique display");
		}
	}

}

substitution::substitution(vector<BasicDataType*> address_array, vector<BasicDataType*> set_of_mappings,ObjectTypeManager* manager){

	ñheck_the_uniqueness_of_the_numbers_displayed(address_array);
	ñheck_the_uniqueness_of_the_numbers_displayed(set_of_mappings);

	if (address_array.size() != set_of_mappings.size() && address_array.size()!=0)throw incorrect_input_data_exception("wrong size of set of mapping");
	size = address_array.size();
	vector<BasicDataType*>data;
	for (vector<BasicDataType*>::iterator iter = address_array.begin(); iter != address_array.end(); iter++) {
		data.push_back(*iter);
	}
	for (vector<BasicDataType*>::iterator iter = set_of_mappings.begin(); iter != set_of_mappings.end(); iter++) {
		data.push_back(*iter);
	}
	main_Matrix = new Matrix(data, 2, size,manager);

}

substitution::substitution(const substitution& other){
	main_Matrix = other.main_Matrix->newClone();
	size = other.size;
}

Matrix substitution::get_Matrix()
{
	return main_Matrix->clone();
}

BasicDataType* substitution::get_the_value_from_the_address(BasicDataType* address){

	int address_index = -1;
	bool is_end_of_searching = false;
	vector<BasicDataType*> search_area = main_Matrix->getRow(0);

	for (vector<BasicDataType*>::iterator iter = search_area.begin(); is_end_of_searching == false && iter != search_area.end(); iter++, address_index++) {
		if(address->equal(*iter))is_end_of_searching = true;
	}
	if (is_end_of_searching == false)throw incorrect_input_data_exception("there are not this address in this subtitution.");
	return main_Matrix->getValueAt(1, address_index);
}

BasicDataType* substitution::get_the_value_from_the_index(int index){

	return main_Matrix->getValueAt(1, index);
}

void substitution::set_the_value_from_the_index(int index, BasicDataType* value){
	main_Matrix->changeValueAt(1,index, value);
}

void substitution::set_the_value_from_the_address(BasicDataType* address, BasicDataType* value){


	int address_index = 0;
	bool is_end_of_searching = false;
	vector<BasicDataType*> search_area = main_Matrix->getRow(0);

	for (vector<BasicDataType*>::iterator iter = search_area.begin(); is_end_of_searching == false && iter != search_area.end(); iter++, address_index++) {
		if (address->equal(*iter))is_end_of_searching = true;
	}
	if (is_end_of_searching == false)throw incorrect_input_data_exception("there are not this address in this subtitution.");
	 main_Matrix->changeValueAt(1,address_index,value);
}

substitution substitution::multiplication(substitution Second_value){

	if (this->size != Second_value.get_size())throw incorrect_input_data_exception("wrong subtitution");
	vector<BasicDataType*>address_array = Second_value.getRow(0);
	vector<BasicDataType*>result_array;
	int index=0;
	for (int i = 0; i < size;i++) {
		result_array.push_back(this->get_the_value_from_the_address(Second_value.get_the_value_from_the_index(i)));
	}

	return substitution(address_array,result_array,this->main_Matrix->getCurrentTypeManager());
}

vector<BasicDataType*> substitution::getRow(int index)
{
	return main_Matrix->getRow(index);
}

bool substitution::equal(substitution Second_substitution){
	return this->main_Matrix->isEqual(Second_substitution.get_Matrix());
}

substitution substitution::get_a_neutral(){
	vector<BasicDataType*> row = this->main_Matrix->getRow(0);
	return substitution(row, row,this->main_Matrix->getCurrentTypeManager());
}

substitution substitution::get_a_reverse(){
	vector<BasicDataType*> data;
	vector<BasicDataType*> address = this->main_Matrix->getRow(0);
	substitution reverse = substitution(this->main_Matrix->getRow(1), this->main_Matrix->getRow(0), main_Matrix->getCurrentTypeManager());
	for (vector<BasicDataType*>::iterator iter = address.begin(); iter != address.end(); iter++) {
		data.push_back(reverse.get_the_value_from_the_address(*iter));
	}
	return substitution(address, data, main_Matrix->getCurrentTypeManager());

}

void substitution::operator=(substitution Second_substitution){
	this->main_Matrix = Second_substitution.get_Matrix().newClone();
}

string substitution::convertToString(){
	string result;
	vector<BasicDataType*> row = main_Matrix->getRow(0);
	for (vector<BasicDataType*>::iterator iter = row.begin(); iter != row.end(); iter++) {
		result += (*iter)->convertToString()+" ";
	}
	result += "\n";
	row = main_Matrix->getRow(1);
	for (vector<BasicDataType*>::iterator iter = row.begin(); iter != row.end(); iter++) {
		result += (*iter)->convertToString() + " ";
	}
	return result;
}

int substitution::get_size(){
	return size;
}

substitution::~substitution(){
	delete main_Matrix;
}
