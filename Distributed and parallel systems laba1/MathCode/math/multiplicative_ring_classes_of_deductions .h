#pragma once

#include <vector>
#include "../data_types/BasicDataType.h"
#include "../exceptions/number_exception.h"
#include "../exceptions/incorrect_input_data_exception.h"
#include "../math/ultimate_mathematics.h"
#include "../data_types/DeductibleClass.h"

using namespace std;


class  multiplicative_ring_classes_of_deductions 
{
protected:

	int module_value;
	int size;
	vector<DeductibleClass> array_of_classes;
	

public:

	static vector<DeductibleClass> find_a_set_of_degrees(int number, int module_value);
	static bool does_the_set_of_degrees_form_a_group(int number, int module_value);
	static bool does_the_set_of_degrees_form_a_group(vector<DeductibleClass> set, int module_value);
	static int find_the_order_of_the_group(int number, int module_value);
	bool is_it_a_cyclical_group();
	vector<DeductibleClass> find_all_primordial_roots();
	bool is_this_the_primordial_root(DeductibleClass number);
	static bool is_this_the_primordial_root(int root, int module_value);
	int get_size();
	int the_order_of_the();
	multiplicative_ring_classes_of_deductions(int Module_value);
	static DeductibleClass* perform_an_multiplication_operation(DeductibleClass* first_number, DeductibleClass* second_number);
	vector<DeductibleClass> get_array_of_classes();
	void set_number(DeductibleClass number, int position);
	DeductibleClass get_number(int position);
	

};



