#include "ultimate_mathematics.h"


ultimate_mathematics::ultimate_mathematics() {

}

int ultimate_mathematics::get_a_degree_value(int number, int divider) {

	int counter = 0;
	if (number % divider != 0) throw number_exception("invalid divider");
	while(number!=1){
		number =number/ divider;
		counter++;
	}
	return counter;

}

int ultimate_mathematics::get_a_degree_value_in_the_number(int number, int divider) {

	int counter = 0;
	while (number % divider == 0) {
		number = number / divider;
		counter++;
	}
	return counter;
}

vector<int> ultimate_mathematics::get_array_of_all_mutually_prime_dividers(int number) {

	vector<int> all_dividers = factorization_only_unique(number);
	vector<int> all_mutually_prime_dividers;
	for (vector<int>::iterator number_iterator = all_dividers.begin(); number_iterator != all_dividers.end(); number_iterator++) {
		all_mutually_prime_dividers.push_back(pow(*number_iterator, get_a_degree_value_in_the_number(number, *number_iterator)));
	}
	return all_mutually_prime_dividers;
}

int ultimate_mathematics::number_of_numbers_in_the_number(int number){
	number = abs(number);
	int counter = 0;
	while (number != 0) {
		number /= 10;
		counter++;
	}	
	return counter;
}

int ultimate_mathematics::max_number(int first_number, int second_number)
{
	if (first_number > second_number) return first_number;
	else return second_number;
	
}

int ultimate_mathematics::min_number(int first_number, int second_number)
{
	if (first_number < second_number) return first_number;
	else return second_number;
}

Matrix ultimate_mathematics::create_a_table_of_modulo_addition(int rows, int columns, int number_module) {

	if (rows < 0 || columns < 0 || number_module <= 1) throw number_exception("invalid params for table of modulo addition");
	Matrix my_Matrix(rows, columns, IntegerDataType::GetControlTypeObject());
	vector<BasicDataType*> buffer_array;
	for (int i = 0; i < rows; i++) {
		for (int k = 0; k < columns; k++) {
			BasicDataType* buffer = new IntegerDataType(modulo_addition(i, k, number_module));
			buffer_array.push_back(buffer);
		}
	}
	my_Matrix.fillInByRows(buffer_array);
	return my_Matrix;
}

Matrix ultimate_mathematics::create_a_table_of_modulo_multiplication(int rows, int columns, int number_module) {

	if (rows < 0 || columns < 0 || number_module <= 1) throw number_exception("invalid params for table of modulo multiplication");
	Matrix my_Matrix(rows, columns,new ObjectTypeManager(new IntegerDataType(4)));
	vector<BasicDataType*> buffer_array;
	for (int i = 0; i < rows; i++) {
		for (int k = 0; k < columns; k++) {
			buffer_array.push_back(new IntegerDataType(modulo_multiplication(i, k, number_module)));
		}
	}
	my_Matrix.fillInByRows(buffer_array);
	return my_Matrix;

}

queue<int> ultimate_mathematics::binary_demultiplication(int number) {

	queue<int> binary_demultiplication;
	while (number != 0 && number != 1) {
		binary_demultiplication.push(number % 2);
		number = number / 2;
	}
	binary_demultiplication.push(number);
	return binary_demultiplication;

}

int ultimate_mathematics::modulo_addition(int first_number, int second_number, int number_module) {

	first_number = normalize_the_number(first_number,number_module);
	second_number = normalize_the_number(second_number,number_module);
	return normalize_the_number(first_number + second_number, number_module);


}

int ultimate_mathematics::modulo_multiplication(int first_number, int second_number, int number_module) {

	first_number = normalize_the_number(first_number, number_module);
	second_number = normalize_the_number(second_number, number_module);
	return normalize_the_number(first_number * second_number, number_module);

}

int ultimate_mathematics::normalize_the_number(int number, int number_module) {

	if (number_module <= 1) throw number_exception("wrong module");
	int quotient = number / number_module;
	int remains;
	if (number < number_module && number >= 0)return number;
	if (number < 0) {
		quotient = quotient - 1;
		remains = number - (quotient * number_module);
	}
	else {
		remains = number % number_module;
	}
	return remains;

}

vector<int> ultimate_mathematics::factorization(int number) {

	int local_number = number;
	vector<int> array_of_common_divisors;
	for (int divider = 2;  local_number != 1 && local_number != -1 && local_number != 0; divider++) {
		if (local_number % divider == 0) {
			local_number = local_number / divider;
			array_of_common_divisors.push_back(divider);
			divider--;
		}
	}
	if (number < 0)array_of_common_divisors[0] *= -1;
	return array_of_common_divisors;

}

vector<int> ultimate_mathematics::factorization_only_unique(int natural_number) {

	if (natural_number <= 0) throw number_exception("It's not  natural number");
	int local_natural_number = natural_number;
	int previous_number = 1;
	vector<int> array_of_common_divisors;
	for (int number = 2; local_natural_number != 1 && local_natural_number != -1 && local_natural_number != 0; number++) {
		if (local_natural_number % number == 0 ) {
			local_natural_number = local_natural_number / number;
			if (number != previous_number) {
				array_of_common_divisors.push_back(number);
			}
			previous_number = number;
			number--;
		}
	}
	return array_of_common_divisors;

}

int ultimate_mathematics::NodFactorization(int first_number, int second_number) {

	vector<int> array_of_common_divisors_of_first_number = factorization(abs(first_number));
	vector<int> array_of_common_divisors_of_second_number = factorization(abs(second_number));
	int result_nod = 1;
	bool is_end_of_iteration;
	for (int i = 0; i < array_of_common_divisors_of_first_number.size(); i++) {
		is_end_of_iteration = false;
		for (int k = 0; k < array_of_common_divisors_of_second_number.size() && !is_end_of_iteration; k++) {
			if (array_of_common_divisors_of_first_number[i] == array_of_common_divisors_of_second_number[k]) {
				result_nod *= array_of_common_divisors_of_second_number[k];
				array_of_common_divisors_of_second_number.erase(array_of_common_divisors_of_second_number.begin() + k);
				is_end_of_iteration = true;
			}
		}

	}
	return result_nod;

}

int ultimate_mathematics::NodEuclidean(int first_number, int second_number) {

	int remainder_of_the_division;
	if (second_number == 0) throw new number_cast_exception("division by zero");
		do {
		remainder_of_the_division = first_number % second_number;
		first_number = second_number;
		second_number = remainder_of_the_division;
	} while (remainder_of_the_division != 0);
	return first_number;

}

stack<int> ultimate_mathematics::IdentityBezu(int first_number, int second_number) {

	if (first_number < 0 || second_number < 0 || (first_number == 0 && second_number == 0)) throw number_exception("negative number");
	stack<int> answer;
	int buffer;
	int u0 = 1, v0 = 0, u1 = 0, v1 = 1, u2 = 0, v2 = 1;

	while ((first_number % second_number) != 0) {
		u2 = u0 - (first_number / second_number) * u1;
		v2 = v0 - (first_number / second_number) * v1;
		v0 = v1;
		u0 = u1;
		v1 = v2;
		u1 = u2;
		buffer = first_number % second_number;
		first_number = second_number;
		second_number = buffer;
	}

	answer.push(v2);
	answer.push(u2);
	return answer;

}

int ultimate_mathematics::DegreeRemainder1(int number, int degree, int divider) {

	queue<int>binary_demultiplication_of_number = binary_demultiplication(degree);
	if (binary_demultiplication_of_number.empty()) throw number_exception("this is wrong number");

	vector<int> buffer_array;
	int temporary_number = number;

	while (!binary_demultiplication_of_number.empty()) {
		temporary_number = normalize_the_number(temporary_number, divider);
		if (binary_demultiplication_of_number.front() == 1) {
			buffer_array.push_back(temporary_number);
		}
		temporary_number = temporary_number * temporary_number;
		binary_demultiplication_of_number.pop();
	}

	int result = 1;
	for (vector<int>::iterator vector_iter = buffer_array.begin(); vector_iter != buffer_array.end(); vector_iter++) {
		result *= *vector_iter;
		result = normalize_the_number(result, divider);
	}
	return result;

}

int ultimate_mathematics::DegreeRemainder2(int number, int degree, int divider) {

	if (degree == 0) return 1;
	number = normalize_the_number(number, divider);
	if (degree % 2 == 0) {
		degree = degree / 2;
		int buffer = DegreeRemainder2(number, degree, divider);
		return normalize_the_number(buffer * buffer, divider);
	}
	else {
		degree = (degree - 1) / 2;
		int buffer = DegreeRemainder2(number, degree, divider);
		return normalize_the_number(normalize_the_number(buffer * buffer, divider) * number, divider);
	}

}

int ultimate_mathematics::Euler_function_for_prime_number(int number) {

	vector<int>array_of_dividers = factorization(number);
	if (array_of_dividers.size() != 1 || array_of_dividers[0] != number) throw number_exception("It's not  prime number");
	return number - 1;

}

int ultimate_mathematics::Euler_function_for_prime_number_to_the_degree_of(int number) {

	vector<int> degress_of_prime_number = factorization_only_unique(number);
	if (degress_of_prime_number.size() != 1) throw number_exception("It's not p^k.p <- P.");
	int divider = degress_of_prime_number[0];
	int prime_number = divider;
	int value_of_degree = get_a_degree_value(number, divider);
	return pow(prime_number, (value_of_degree - 1)) * (prime_number - 1);

}

int ultimate_mathematics::Euler_function_for_mutually_prime_numbers(int number) {

	if (number == 1)return 1;
	vector<int> array_of_dividers = get_array_of_all_mutually_prime_dividers(number);
	int result = 1;
	for (vector<int>::iterator number_iterator = array_of_dividers.begin(); number_iterator != array_of_dividers.end(); number_iterator++) {
		result*= Euler_function_for_prime_number_to_the_degree_of (*number_iterator);
	}
	return result;

}

int ultimate_mathematics::Euler_function_in_common_case(int number) {

	if (number == 1)return 1;
	vector<int>array_of_dividers = factorization_only_unique(number);
	for (vector<int>::iterator number_iterator = array_of_dividers.begin(); number_iterator != array_of_dividers.end(); number_iterator++) {
		number = number * (1.0 - 1.0 / (*number_iterator));
	}
	
	return number;

}

int ultimate_mathematics::InverseClass(int number, int number_module){

	number = normalize_the_number(number,number_module);
	int nod_number_and_module = NodEuclidean(number, number_module);
	if (nod_number_and_module != 1 && nod_number_and_module != -1)throw incorrect_input_data_exception("There is no inverse number");
	for (int i = 0; i < number_module; i++) {
		if (normalize_the_number(number * i, number_module) == 1) return i;
	}
	throw incorrect_input_data_exception("It's impossible to find an existing inverse number");
}

int ultimate_mathematics::InverseBezu(int number, int number_module){

	number = normalize_the_number(number, number_module);
	int nod_number_and_module = NodEuclidean(number, number_module);
	if (nod_number_and_module != 1 && nod_number_and_module != -1)throw incorrect_input_data_exception("There is no inverse number");
	stack<int> Bezu_demultiplication = IdentityBezu(number, number_module);
	return normalize_the_number(Bezu_demultiplication.top(),number_module);

}

int ultimate_mathematics::Euler_function(int number, int version) {

	switch (version) {
	case 1:
		return Euler_function_for_prime_number(number);
		break;
	case 2:
		return Euler_function_for_prime_number_to_the_degree_of(number);
		break;
	case 3:
		return Euler_function_for_mutually_prime_numbers(number);
		break;
	case 4:
		return Euler_function_in_common_case(number);
		break;
	default:
		throw incorrect_input_data_exception("Incorrect variant of Euler funcrtion.");
	}

}