#pragma once

#include "./Matrix/Matrix.h"

class substitution{
private:

	Matrix* main_Matrix;
	int size;

	void ñheck_the_uniqueness_of_the_numbers_displayed(vector<BasicDataType*> set_of_data);

public:

	substitution(vector<BasicDataType*>  address_array, vector<BasicDataType*> set_of_mappings, ObjectTypeManager* manager);
	substitution(const substitution& other);
	Matrix get_Matrix();
	BasicDataType* get_the_value_from_the_address(BasicDataType* address);
	BasicDataType* get_the_value_from_the_index(int index);
	void set_the_value_from_the_index(int index, BasicDataType* value);
	void set_the_value_from_the_address(BasicDataType* address, BasicDataType* value);
	substitution multiplication(substitution Second_value);
	vector<BasicDataType*>getRow(int index);
	bool equal(substitution Second_substitution);
	substitution get_a_neutral();
	substitution get_a_reverse();
	void operator = (substitution Second_substitution);
	string convertToString();
	int get_size();
	~substitution();
};

