#include "MathematicsInterface.h"
#include "../math/ultimate_mathematics.h"
#include <iomanip>

void MathematicsInterface::displayAnswerWithIaccuracy(vector<BasicDataType*> array_of_elements, string name_of_elements){
	vector<FloatDataType> result_vector;
	for (int i = 0; i < array_of_elements.size(); i++) {
		result_vector.push_back(*(dynamic_cast<FloatDataType*>(array_of_elements[i])));
	}
	this->lineIntent();
	cout << "����������:" << endl;
	for (int i = 0; i < result_vector.size(); i++) {
		cout << name_of_elements << i + 1 << " = " << result_vector[i].convertToString() << endl;
	}
	this->lineIntent();
	cout << "�����������: " << endl;
	vector<FloatDataType> inaccuracy = findIaccuracy(result_vector);
	for (int i = 0; i < result_vector.size(); i++) {
		cout << name_of_elements << i + 1 << " = " << inaccuracy[i].convertToString() << endl;
	}
	this->lineIntent();
	this->lineIntent();
}

void MathematicsInterface::displayMatrix(Matrix my_Matrix, string operation, int place_on_one_number) {
	cout << setw(place_on_one_number) << operation << "  ";
	for (int i = 0; i < my_Matrix.getNumberOfColumns(); i++) {
		cout << setw(place_on_one_number) << i << " ";
	}
	cout << endl << endl;
	for (int i = 0; i < my_Matrix.getNumberOfRows(); i++) {
		cout << setw(place_on_one_number) << i << "  ";
		for (int k = 0; k < my_Matrix.getNumberOfColumns(); k++) {
			cout << setw(place_on_one_number) << my_Matrix.getValueAt(i, k)->convertToString() << " ";
		}
		cout << endl;
	}
}

void MathematicsInterface::displayNumberMatrix(Matrix my_Matrix, string operation, int place_on_one_number)
{
	cout << setw(place_on_one_number) << operation << "  ";
	for (int i = 0; i < my_Matrix.getNumberOfColumns(); i++) {
		cout << setw(place_on_one_number) << i << " ";
	}
	cout << endl << endl;
	for (int i = 0; i < my_Matrix.getNumberOfRows(); i++) {
		cout << setw(place_on_one_number) << i << "  ";
		for (int k = 0; k < my_Matrix.getNumberOfColumns(); k++) {
			cout << setw(place_on_one_number) << dynamic_cast<FloatDataType*>(my_Matrix.getValueAt(i, k))->getValue() << " ";
		}
		cout << endl;
	}
	
}

void MathematicsInterface::displayMatrixFile(Matrix my_Matrix, string operation, int place_on_one_number,string fileName)
{
	ofstream output(fileName);
	output << setw(place_on_one_number) << operation << "  ";
	for (int i = 0; i < my_Matrix.getNumberOfColumns(); i++) {
		output << setw(place_on_one_number) << i << " ";
	}
	output << endl << endl;
	for (int i = 0; i < my_Matrix.getNumberOfRows(); i++) {
		output << setw(place_on_one_number) << i << "  ";
		for (int k = 0; k < my_Matrix.getNumberOfColumns(); k++) {
			output << setw(place_on_one_number) << my_Matrix.getValueAt(i, k)->convertToString() << " ";
		}
		output << endl;
	}
	output.close();
}

MathematicsInterface::MathematicsInterface(string program_name, string record_file_name) :BasicConsoleInterface(program_name, record_file_name) {
}

vector<FloatDataType> MathematicsInterface::findIaccuracy(vector<FloatDataType> set) {

	vector<FloatDataType> result;
	for (vector<FloatDataType>::iterator iter = set.begin(); iter != set.end(); iter++) {
		result.push_back(FloatDataType(fabs((*iter).getValue() - FloatDataType::round_double_data_type((*iter).getValue(), 1000)->getValue())));
	}
	return result;
}

Matrix MathematicsInterface::inputMatrix() {
	cout << "������� ������� �������." << endl;
	int number_of_rows = inputNumber("���������� �����");
	int number_of_columns = inputNumber("���������� �������");
	cout << endl;
	cout << "������� ������,���������������� ������ �������." << endl;
	double buffer;
	vector<BasicDataType*> array_of_numbers;
	for (int i = 0; i < number_of_rows; i++) {
		for (int k = 0; k < number_of_columns; k++) {
			cout << to_string(i) << "," << to_string(k) << ": ";
			cin >> buffer;
			array_of_numbers.push_back(new FloatDataType(buffer));
		}
	}
	return Matrix(array_of_numbers, number_of_rows, number_of_columns, FloatDataType::GetControlTypeObject());
}

Matrix MathematicsInterface::inputMatrixRandom()
{
	cout << "������� ������� �������." << endl;
	int number_of_rows = inputNumber("���������� �����");
	int number_of_columns = inputNumber("���������� �������");
	cout << endl;
	double buffer;
	srand(time(NULL));
	vector<BasicDataType*> array_of_numbers;
	for (int i = 0; i < number_of_rows; i++) {
		for (int k = 0; k < number_of_columns; k++) {
			buffer = rand() % 100 - 50;
			array_of_numbers.push_back(new FloatDataType(buffer));
		}
	}
	return Matrix(array_of_numbers, number_of_rows, number_of_columns, FloatDataType::GetControlTypeObject());
}

void MathematicsInterface::fixChangesInFileCons(string fileName, string information)
{
	cout << information << endl;;
	ofstream stream(fileName, std::ios::app);
	stream << information << endl;
	stream.close();
}


double function1(double x, double y) {
	return exp(x) * sin(y);
}
double function2(double x, double y) {
	return sin(x + 2 * y);
}

double function3(double x, double y) {
	return  cos(x * exp(y));
}

double function4(double x, double y) {
	return  exp(cos(x * x + y));
}




void MathematicsInterface::taskSelection() {

	
	bool isEndOfGlobal = false;
	bool isEndOfLocal = false;
	coordinates basicCoordinates;
	int numberOfThreads;
	int xFragmentation;
	int yFragmentation;
	char globalOption,localOption;
	double integralResult;
	Matrix* firstMatrix;
	Matrix* secondMatrix;
	Matrix* resultMatrixMulti;
	Matrix* resultMatrixOne;
	time_t beginTime;
	time_t endTime;
	IntegralSolver* solver = nullptr;
	while (!isEndOfGlobal) {
		this->lineIntent();
		this->printString("�������� ������ �������: ");
		this->printString("1. ���������� �������� ���������.");
		this->printString("2. ���������� ������������ ������.");
		cin >> globalOption;
		switch (globalOption) {

			case '1':
				
				while (!isEndOfLocal) {

					this->lineIntent();
					this->printString("�������� ������ �������: ");
					this->printString("1.e^x * sin(y).");
					this->printString("2.sin(x + 2 * y).");
					this->printString("3.x * e^y.");
					this->printString("4.e^(x^2 + y).");
					cin >> localOption;

					switch (localOption) {
						case '1':
							solver = new IntegralSolver(function1);
							isEndOfLocal = true;
							break;
						case '2':
							solver = new IntegralSolver(function2);
							isEndOfLocal = true;
							break;
						case '3':
							solver = new IntegralSolver(function3);
							isEndOfLocal = true;
							break;
						case '4':
							solver = new IntegralSolver(function4);
							isEndOfLocal = true;
							break;
						default:
							
							this->printString("������ ������������ �������.");
							break;
					}
				}
				
				this->printString("������� ��������� ��� x � y.");
				this->printString("������� ��������� X: ");
				cin >> basicCoordinates.xBegin;
				this->printString("������� �������� X: ");
				cin >> basicCoordinates.xEnd;
				this->printString("������� ��������� Y: ");
				cin >> basicCoordinates.yBegin;
				this->printString("������� �������� Y: ");
				cin >> basicCoordinates.yEnd;
				xFragmentation = this->inputNumber("���������� ��������� �� X");
				yFragmentation = this->inputNumber("���������� ��������� �� Y");
				numberOfThreads = this->inputNumber("���������� �������");
				beginTime = time(NULL);
				integralResult = solver->solveAsync(basicCoordinates,numberOfThreads,xFragmentation,yFragmentation);
				endTime = time(NULL);
				this->printString("����� ����������: " + to_string(endTime - beginTime)+".");
				this->printResultString(to_string(integralResult));
				isEndOfGlobal = true;
					 
			break;
			case '2':

				this->printString("������� ��� �������.");
				firstMatrix = new Matrix(this->inputMatrixRandom());
				this->printString("������������� �������: ");
				this->lineIntent();
				displayNumberMatrix(*firstMatrix, "", 4);
				this->lineIntent();
				secondMatrix = new Matrix(this->inputMatrixRandom());
				this->printString("������������� �������: ");
				this->lineIntent();
				displayNumberMatrix(*secondMatrix, "", 4);
				this->lineIntent();


				numberOfThreads = this->inputNumber("���������� �������");

				this->printString("�������������� �������: ");
				beginTime = time(NULL);
				resultMatrixMulti = Matrix::multithreadedMultiplicationByUsingPromise(firstMatrix,secondMatrix,numberOfThreads);
				endTime = time(NULL);
				this->displayNumberMatrix(*resultMatrixMulti, "*", 8);
				this->displayMatrixFile(*resultMatrixMulti, "*", 6, "MatrixMultiThread.txt");
				fixChangesInFileCons("MatrixMultiThread.txt", "����� ����������: " + to_string(endTime - beginTime) + ".");
				
				this->printString("������������ �������: ");
				beginTime = time(NULL);
				resultMatrixOne = new Matrix(*firstMatrix * *secondMatrix);
			    endTime = time(NULL);
				this->displayNumberMatrix(*resultMatrixOne, "*", 8);
			    this->displayMatrixFile(*resultMatrixOne, "*", 6, "MatrixOneThread.txt");
				fixChangesInFileCons("MatrixOneThread.txt", "����� ����������: " + to_string(endTime - beginTime) + ".");

				this->printString("�������� �������:");
				this->lineIntent();
				
				delete firstMatrix;
				delete secondMatrix;
				delete resultMatrixOne;
				delete resultMatrixMulti;
				
				isEndOfGlobal = true;

			break;

			default:
				this->printString("������ �������� ���.�������� ��� ���");
				
		}
	}


	this->lineIntent();

}