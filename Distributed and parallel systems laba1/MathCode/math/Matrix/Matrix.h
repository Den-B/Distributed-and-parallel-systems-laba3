#pragma once
#include <typeinfo>
#include <vector>
#include <future>
#include <thread>
#include <Windows.h>
#include <iostream>
#include <functional>
#include "../../exceptions/number_exception.h"
#include "../../exceptions/incorrect_input_data_exception.h"
#include "../../data_types/BasicDataType.h"
#include "../../data_types/ObjectTypeManager.h"
#include "../../data_types/NumberDataType.h"
#include "../../data_types/FloatDataType.h"
#include "../../exceptions/number_cast_exception.h"


using namespace std;

struct matrixCoordinates {

	short int row;
	short int column;

};

struct processingData {

	void* firstMatrix;
	void* secondMatrix;
	void* resultMatrix;

	vector<matrixCoordinates*>* coords;

	~processingData() {
		for (vector<matrixCoordinates*>::iterator coord = coords->begin(); coord != coords->end(); coord++) {
			delete *coord;
		}
		delete coords;
	}
};


class Matrix
{
private:

	
	vector<vector<BasicDataType*>> values;
	int number_of_rows = 0;
	int number_of_columns = 0;
	int size_of_Matrix = 0;
	ObjectTypeManager* type_manager;

private:

	bool checkInaccuracy(vector<BasicDataType*>current, vector<BasicDataType*>previous, BasicDataType* inaccuracy);
	void checkSize(vector<vector<BasicDataType*>> new_values, int opening_row, int end_row, int opening_column, int end_column);
	void checkSize(vector<BasicDataType*>  new_values);

	void copy(const Matrix& other);
	void copy(const Matrix& other, int opening_row, int end_row, int opening_column, int end_column);

	void deleteAllData();
	void freeUpVector(vector<BasicDataType*> current_vector);
	void freeUpMemoryInRow(int index_of_row);

	void memoryAllocation(int Number_of_rows,int Number_of_columns);
	void definitionPart(int rows, int columns, ObjectTypeManager* object_type);
	void nullInitialization();
	void initializationPocess(vector<vector<BasicDataType*>> new_values, int opening_row, int end_row, int opening_column, int end_column);
	void rowIitializationPocess(vector<BasicDataType*>  new_values);
	void columnIitializationPocess(vector<BasicDataType*>  new_values);
	
	int indexOfFirstNonZeroElemenInColumnDown(int index_of_column, int index_of_top);
	int indexOfFirstNonZeroElemenInColumnUp(int index_of_column, int index_of_top);
	int indexOfMaximumElemenInColumn(int index_of_column, int index_of_top);
	vector<BasicDataType*> rowAddition(vector<BasicDataType*>first_row, vector<BasicDataType*>second_row);
	vector<BasicDataType*> rowMultiplicationByConstant(int index_of_row,BasicDataType* constant);
	vector<BasicDataType*> rowMultiplicationByReverseConstant(int index_of_row, BasicDataType* constant);
	vector<BasicDataType*> reduceValuesInLineN(int index_of_row, BasicDataType* constant);
	vector<BasicDataType*> convertMatrixIntoLowerTriangularMatrix(Matrix& tracking_Matrix);
	vector<BasicDataType*> convertMatrixIntoUpperTriangularMatrix(Matrix& tracking_Matrix);

	static DWORD WINAPI calculateValueAt(void* dataForCalculation);
	static void WINAPI calculateValueAtByUsingPromise(promise<processingData*>* promise);


public:

	//constructors

	Matrix(Matrix& other);
	Matrix(const Matrix& other);
	Matrix(vector<BasicDataType*>array_of_elements,ObjectTypeManager* object_type);
	Matrix(vector<BasicDataType*>array_of_elements, int Number_of_rows, int Number_of_columns, ObjectTypeManager* object_type);
	Matrix(int demension, ObjectTypeManager* object_type);
	Matrix(int Number_of_rows, int Number_of_columns, ObjectTypeManager* object_type);


	//Matrix fills with values

	void  fillMatrix(vector<vector<BasicDataType*>> new_values, int number_of_rows, int number_of_columns);
	void  fillMatrix(vector<vector<BasicDataType*>> new_values, int opening_row, int end_row, int opening_column, int end_column);
	void  fillInByColumns(vector<BasicDataType*> new_values);
	void  fillInByRows(vector<BasicDataType*> new_values);

	//setters and getters

	void  changeValueAt(int Row, int Column, BasicDataType* new_value);
	BasicDataType* getValueAt(int Row, int Column) const;
	void setValueAt(int Row, int Column,BasicDataType* value);
	BasicDataType* getNeutralElementWithRespectToAddition();
	BasicDataType* getNeutralElementWithRespectToMultiplication();
	ObjectTypeManager* getCurrentTypeManager();
	vector<BasicDataType*>getRow(int row_index);
	int  getNumberOfColumns() const;
	int  getNumberOfRows() const;
	void fillRow(int index_of_row, vector<BasicDataType*> array_of_elements);
	vector<BasicDataType*> getFullArrayOfValues();
	vector<vector<BasicDataType*>> getValues() const;
	int getMatrixSize();

	//operators

	Matrix operator +(Matrix&  Second_Matrix);
	Matrix operator *(Matrix& Second_Matrix);

	void  operator +=(Matrix&  Second_Matrix);
	void operator *=(Matrix& Second_Matrix);
	void operator = (Matrix Second_Matrix);
	bool operator ==(Matrix& Second_Matrix);

			//all methods

	//static methods
	static Matrix powForMatrix(Matrix  current_Matrix, int degree);
	static Matrix createUnitMatrix(int Matrix_dimensions, ObjectTypeManager* type_manager);
	static Matrix* multithreadedMultiplication(Matrix* firstMatrix, Matrix* secondMatrix, short int numberOfThreads);
	static Matrix* multithreadedMultiplicationByUsingPromise(Matrix* firstMatrix, Matrix* secondMatrix, short int numberOfThreads);

	//object methods

	bool isEqual(Matrix Second_Matrix);
	Matrix mergeMatrices(Matrix Second_Matrix);
	void rowReplacement(int index_of_row,vector<BasicDataType*> new_row);
	void rowSwap(int index_of_first_row, int index_of_second_row);
	bool IsThreeDiagonalMatrix();
	BasicDataType* goForward(int& currentRow, int& currentColumn);
	bool isPossibleToGoForward(int currentRow, int currentColumn);
	bool tryToGoForward(short int& currentRow,short int& currentColumn);

	Matrix findLowerTriangularMatrix();
	Matrix findLowerTriangularMatrix(Matrix& tracking_Matrix);
	Matrix findLowerTriangularMatrix(vector<BasicDataType*>& tracking_array);
	Matrix findLowerTriangularMatrix(Matrix& tracking_Matrix,vector<BasicDataType*>& tracking_array);
	Matrix findUpperTriangularMatrix();
	Matrix findUpperTriangularMatrix(Matrix& tracking_Matrix);
	Matrix findUpperTriangularMatrix(vector<BasicDataType*>& tracking_array);
	Matrix findUpperTriangularMatrix(Matrix& tracking_Matrix,vector<BasicDataType*>& tracking_array);

	vector<BasicDataType*> iterativeStepwiseMethod(BasicDataType* inaccurancy);
	vector<vector<BasicDataType*>> DanilevskyMethod(vector<BasicDataType*> L_array);
	Matrix SeidelMethod(BasicDataType* inaccurancy);
	Matrix methodOfSimpleIterations(BasicDataType* inaccurancy);
	Matrix runThroughMethod();
	Matrix squareRootsMethod();
	Matrix MatrixTranspose();
	Matrix findReverseMatrixN();
	BasicDataType* findMatrixDeterminantN();
	Matrix GaussMethodN();
	Matrix GaussJordanMethodF();
	Matrix GaussMethodWithMainElementF();
	Matrix multiplyMatrixByConstant(BasicDataType* constant);
	Matrix multiplyMatrixByReverseConstantN(BasicDataType* constant);

	bool empty();

	//clone army

	Matrix* newClone();
	Matrix clone();
	Matrix clone(int count_of_rows, int count_of_columns);
	Matrix clone(int opening_row, int end_row, int opening_column, int end_column);
	Matrix cloneWithoutRowAndColumn(int row, int column);

	//destructors

	void clear();
	~Matrix();

};

