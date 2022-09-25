#pragma once
#include "substitution.h"

class substitution_group{
private:
	vector<substitution>values;
	int size;

public:

	substitution_group(substitution root);
	vector<substitution> getValues();
	int get_size();
	int find_index_of_inverse_element(substitution element);
	int find_index_of_neutral_element();

};

