#pragma once

#include <vector>
#include <iterator>
#include <queue>
#include "Matrix/Matrix.h"
#include "../exceptions/number_exception.h"
#include "../exceptions/incorrect_input_data_exception.h"
#include "../data_types/IntegerDataType.h"
#include <stack>


using namespace std;

class ultimate_mathematics
{
private:

	ultimate_mathematics();
	static queue<int>binary_demultiplication(int number);
	
	static int get_a_degree_value(int number,int divider);
	static int get_a_degree_value_in_the_number(int number, int divider);
	static vector<int> get_array_of_all_mutually_prime_dividers(int number);

public:

	static int number_of_numbers_in_the_number(int number);
	static int max_number(int first_number, int second_number);
	static int min_number(int first_number, int second_number);


	static int InverseClass(int number, int number_module);
	static int InverseBezu(int number, int number_module);

	static int Euler_function(int number, int version);
	static int Euler_function_for_prime_number(int number);
	static int Euler_function_for_prime_number_to_the_degree_of(int number);
	static int Euler_function_for_mutually_prime_numbers(int number);
	static int Euler_function_in_common_case(int number);

	static Matrix create_a_table_of_modulo_addition(int rows,int columns, int number_module);
	static Matrix create_a_table_of_modulo_multiplication(int rows,int columns, int number_module);
	static int modulo_addition(int first_number, int second_number, int module);
	static int modulo_multiplication(int first_number, int second_number, int module);

	static vector<int> factorization(int number);
	static vector<int> factorization_only_unique(int natural_number);
	static int NodFactorization(int first_number, int second_number);
	static int NodEuclidean(int first_number, int second_number);
	static stack<int> IdentityBezu(int first_number, int second_number);

	static int DegreeRemainder1(int number, int extent, int divider);
	static int DegreeRemainder2(int number, int extent, int divider);

	static int normalize_the_number(int number, int number_module);
};

