#include "substitution_group.h"

substitution_group::substitution_group(substitution root){
	substitution first(root);
	substitution passerby(root);
	do {
		values.push_back(passerby);
		passerby = passerby.multiplication(first);
	} while (!(passerby.equal(first)));
	size = values.size();
}

vector<substitution> substitution_group::getValues(){
	return values;
}

int substitution_group::get_size()
{
	return size;
}

int substitution_group::find_index_of_neutral_element(){
	int index = 0;
	for (vector<substitution>::iterator iter = values.begin(); iter != values.end(); index ++, iter++) {
		if((*iter).equal((*iter).get_a_neutral())) return index;
	}
}

int substitution_group::find_index_of_inverse_element(substitution element) {
	int index = 0;
	for (vector<substitution>::iterator iter = values.begin(); iter != values.end(); index++, iter++) {
		if ((*iter).equal((element).get_a_reverse())) return index;
	}

}
