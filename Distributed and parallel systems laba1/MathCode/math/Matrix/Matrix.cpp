#include "Matrix.h"

											/////////////////////constructors team/////////////////////



	Matrix::Matrix(const Matrix& other) {
		copy(other);
	}

	Matrix::Matrix(Matrix& other) {
		copy(other);
	}

	Matrix::Matrix(vector<BasicDataType*> array_of_elements,ObjectTypeManager* object_type) {

		int size_of_square_Matrix = (int)sqrt(array_of_elements.size());
		if (array_of_elements.size() / size_of_square_Matrix != size_of_square_Matrix || array_of_elements.size() == 0)throw new  incorrect_input_data_exception("It's not square Matrix");
		definitionPart(size_of_square_Matrix, size_of_square_Matrix, object_type->clone());
		fillInByRows(array_of_elements);

	}

	Matrix::Matrix(vector<BasicDataType*> array_of_elements, int Number_of_rows, int Number_of_columns, ObjectTypeManager* object_type)
	{

		definitionPart(Number_of_rows, Number_of_columns, object_type->clone());
		checkSize(array_of_elements);
		fillInByRows(array_of_elements);

	}

	Matrix::Matrix(int demension, ObjectTypeManager* object_type){
		definitionPart(demension, demension, object_type->clone());
		nullInitialization();
	}

	Matrix::Matrix(int Number_of_rows, int Number_of_columns, ObjectTypeManager* object_type) {

		if (Number_of_columns < 0 || Number_of_rows < 0) throw number_exception("wrong Matrix size");
		this->definitionPart(Number_of_rows,Number_of_columns,object_type);
		nullInitialization();
	}


													////////////////////fill guy/////////////////////



	void  Matrix::fillMatrix(vector<vector<BasicDataType*>> new_values, int number_of_rows, int number_of_columns) {

		initializationPocess(new_values, 0, number_of_rows,0, number_of_columns);
	}

	void Matrix::fillMatrix(vector<vector<BasicDataType*>> new_values, int opening_row, int end_row, int opening_column, int end_column)
	{
		initializationPocess(new_values, opening_row, end_row, opening_column, end_column);
	}

	void  Matrix::fillInByColumns(vector<BasicDataType*>  new_values) {

		columnIitializationPocess(new_values);

	}

	void  Matrix::fillInByRows(vector<BasicDataType*>  new_values) {

		rowIitializationPocess(new_values);

	}



												////////////////////setters and getters/////////////////////



	void  Matrix::changeValueAt(int Row, int Column, BasicDataType* new_value) {

		if (Column < 0 || Row < 0 || Column >= number_of_columns || Row >= number_of_rows) throw number_exception("wrong count of number of values' position");
		delete values[Row][Column];
		values[Row][Column] = new_value;

	}

	BasicDataType* Matrix::getValueAt(int Row, int Column) const {

		if (Column < 0 || Row < 0 || Column >= number_of_columns || Row >= number_of_rows) throw number_exception("wrong count of number of values' position");
		return values[Row][Column]->clone();

	}

	void Matrix::setValueAt(int Row, int Column, BasicDataType* value)
	{
		if (Column < 0 || Row < 0 || Column >= number_of_columns || Row >= number_of_rows) throw number_exception("wrong count of number of values' position");
		delete values[Row][Column];
		values[Row][Column] = value;
	}

	BasicDataType* Matrix::getNeutralElementWithRespectToAddition(){

		return this->type_manager->getNeutralElementWithRespectToAddition()->clone();

	}

	BasicDataType* Matrix::getNeutralElementWithRespectToMultiplication(){

		return this->type_manager->getNeutralElementWithRespectToMultiplication()->clone();
	}

	ObjectTypeManager* Matrix::getCurrentTypeManager(){
		return type_manager->clone();				
	}

	vector<BasicDataType*> Matrix::getRow(int row_index){
		if (row_index > this->number_of_rows)throw incorrect_input_data_exception("Wrong index of Matrix row");
		vector<BasicDataType*>result_row;
		for (int index = 0; index < this->number_of_columns;index++) {
			result_row.push_back(this->getValueAt(row_index,index)->clone());
		}
		return result_row;
	}

	int  Matrix::getNumberOfColumns() const {
		return number_of_columns;
	}

	int  Matrix::getNumberOfRows() const {
		return number_of_rows;
	}

	void Matrix::fillRow(int index_of_row, vector<BasicDataType*> array_of_elements){

		if (index_of_row >= this->number_of_rows)throw incorrect_input_data_exception("There isn't row with this index.");
		if(array_of_elements.size() > number_of_columns)throw incorrect_input_data_exception("There are not enough elements.");
		int column_index = 0;
		for (vector<BasicDataType*>::iterator iter = array_of_elements.begin(); column_index < number_of_columns; column_index++, iter++) {
			this->setValueAt(index_of_row, column_index, *iter);
		}
		
	}

	vector<vector<BasicDataType*>> Matrix::getValues() const {
		vector<vector<BasicDataType*>> result;
		result.resize(number_of_rows);
		for (int row_index = 0; row_index < number_of_rows; row_index++) {
			for (int column_index = 0; column_index<number_of_columns; column_index++) {
				result[row_index].push_back(getValueAt(row_index, column_index));
			}
		}
		return result;
	}

	int Matrix::getMatrixSize()
	{
		return size_of_Matrix;
	}



													////////////////////operators/////////////////////



	Matrix Matrix::operator +(Matrix& Second_Matrix) {

		if (this->number_of_columns != Second_Matrix.number_of_columns && this->number_of_rows != Second_Matrix.number_of_rows) throw new  incorrect_input_data_exception("these matrices are not equal");
		Matrix result_Matrix(number_of_rows, number_of_columns,this->type_manager->clone());
		try {
			for (int i = 0; i < number_of_rows; i++) {
				for (int k = 0; k < number_of_columns; k++) {
					result_Matrix.values[i][k] = this->getValueAt(i, k)->addition(Second_Matrix.getValueAt(i, k));
				}
			}
			return result_Matrix;
		}
		catch (number_cast_exception exception) {
			throw new  incorrect_input_data_exception("it is impossible to perform an addition");

		}
	}

	Matrix Matrix::operator *(Matrix& Second_Matrix) {

		if (this->number_of_columns != Second_Matrix.number_of_rows) throw incorrect_input_data_exception("these matrices are not compatible");
		int rows_of_new_Matrix = this->number_of_rows;
		int columns_of_new_Matrix = Second_Matrix.number_of_columns;
		vector<BasicDataType*> buffer_array;
		BasicDataType* sum;
		Matrix result(rows_of_new_Matrix, columns_of_new_Matrix, this->type_manager->clone());
		try{
		for (int i = 0; i < this->number_of_rows; i++) {
				for (int k = 0; k < Second_Matrix.getNumberOfColumns(); k++) {
					
					sum = this->getNeutralElementWithRespectToAddition();
					for (int j = 0; j < Second_Matrix.getNumberOfRows(); j++) {
						BasicDataType* firstMatrixValue = this->getValueAt(i, j);
						BasicDataType* secondMatrixValue = Second_Matrix.getValueAt(j, k);
						BasicDataType* multiplicationResult = firstMatrixValue->multiplication(secondMatrixValue);
						delete secondMatrixValue;
						delete firstMatrixValue;
						BasicDataType* buffer = sum ->addition(multiplicationResult);
						delete sum;
						delete multiplicationResult;
						sum = buffer;
					}
					
					result.setValueAt(i, k, sum);
				}
			}
			
			return result;
		}
		catch (number_cast_exception exception) {
			throw incorrect_input_data_exception("it is impossible to perform multiplication");
		}
	}



	void Matrix::operator+=(Matrix& Second_Matrix){
		
		Matrix  buffer(*this);
		buffer = buffer + Second_Matrix;
		this->copy(buffer);

	}

	void Matrix::operator *=(Matrix& Second_Matrix) {

		Matrix  buffer(*this);
		buffer = buffer * Second_Matrix;
		this->copy(buffer);
	}

	void Matrix::operator=(Matrix Second_Matrix)
	{
		this->copy(Second_Matrix);
	}

	bool Matrix::operator==(Matrix& Second_Matrix){
		return this->isEqual(Second_Matrix);
	}



													////////////////////operation methods/////////////////////



	Matrix  Matrix::powForMatrix(Matrix current_Matrix, int degree) {

		Matrix initial_value_Matrix(current_Matrix);
		if (degree < 0)throw incorrect_input_data_exception("Wrong degree.");
		if (current_Matrix.getNumberOfRows() == current_Matrix.getNumberOfColumns() && degree == 0) {
			return createUnitMatrix(current_Matrix.getNumberOfRows(),current_Matrix.getCurrentTypeManager());
		}
		for (int i = 1; i < degree; i++) {
			current_Matrix *= initial_value_Matrix;
		}
		return current_Matrix;
	}


	Matrix Matrix::createUnitMatrix(int Matrix_dimensions,ObjectTypeManager* type_manager) {

		if (Matrix_dimensions < 1)throw incorrect_input_data_exception("Invalid data for the unit Matrix.");
		vector<BasicDataType*>result_array;
		for (int i = 0; i < Matrix_dimensions; i++) {
			for (int k = 0; k < Matrix_dimensions; k++) {
				if (i == k)result_array.push_back(type_manager->getNeutralElementWithRespectToMultiplication()->clone());
				else result_array.push_back(type_manager->getNeutralElementWithRespectToAddition()->clone());
			}
		}
		return Matrix(result_array,Matrix_dimensions, Matrix_dimensions,type_manager);
	}

	Matrix* Matrix::multithreadedMultiplication(Matrix* firstMatrix, Matrix* secondMatrix,short int numberOfThreads)
	{

		if (firstMatrix->getNumberOfColumns() != secondMatrix->getNumberOfRows()) throw incorrect_input_data_exception("these matrices are not compatible");
		int rows_of_new_Matrix = firstMatrix->getNumberOfRows();
		int columns_of_new_Matrix = secondMatrix->getNumberOfColumns();
		Matrix* result = new Matrix(rows_of_new_Matrix, columns_of_new_Matrix, firstMatrix->getCurrentTypeManager());
		int step = ceil(double(result->getMatrixSize()) / double(numberOfThreads));
		short int row = 0;
		short int column = 0;
		try {
			vector<processingData*> allDataForTreads;
			for (unsigned short int thread = 0; thread < numberOfThreads;thread++) {
				processingData* packForThread = new processingData();
				packForThread->coords = new vector<matrixCoordinates*>;
				packForThread->firstMatrix = firstMatrix;
				packForThread->secondMatrix = secondMatrix;
				packForThread->resultMatrix = result;
				unsigned int element = 0;
				do{
					matrixCoordinates* data = new matrixCoordinates({ row,column });
					packForThread->coords->push_back(data);
					element++;
				} while (result->tryToGoForward(row, column) && element < step);

				allDataForTreads.push_back(packForThread);
			}
			HANDLE* matrixThreads = new HANDLE[numberOfThreads];
			for (unsigned int thread = 0; thread < numberOfThreads;thread++) {
				matrixThreads[thread] = CreateThread(NULL, 0, Matrix::calculateValueAt,(void*)allDataForTreads[thread],NULL,NULL);
			}
			WaitForMultipleObjects(numberOfThreads, matrixThreads, true, INFINITE);
			return result;
		}
		catch (number_cast_exception exception) {
			throw incorrect_input_data_exception("it is impossible to perform multiplication");
		}
		
	}



	Matrix* Matrix::multithreadedMultiplicationByUsingPromise(Matrix* firstMatrix, Matrix* secondMatrix, short int numberOfThreads)
	{

		if (firstMatrix->getNumberOfColumns() != secondMatrix->getNumberOfRows()) throw incorrect_input_data_exception("these matrices are not compatible");
		int rows_of_new_Matrix = firstMatrix->getNumberOfRows();
		int columns_of_new_Matrix = secondMatrix->getNumberOfColumns();
		Matrix* result = new Matrix(rows_of_new_Matrix, columns_of_new_Matrix, firstMatrix->getCurrentTypeManager());
		int step = ceil(double(result->getMatrixSize()) / double(numberOfThreads));
		short int row = 0;
		short int column = 0;
		
		vector<thread*> threadPool;
		vector<promise<processingData*>*> threadPromises;

		for (int currentThread = 0; currentThread < numberOfThreads; currentThread++) {
			promise<processingData*>* promiseOfData = new promise<processingData*>();
			thread* newThread = new thread(calculateValueAtByUsingPromise,promiseOfData);
			threadPromises.push_back(promiseOfData);
			threadPool.push_back(newThread);
		}

		try {

			for (unsigned short int thread = 0; thread < numberOfThreads; thread++) {
				processingData* packForThread = new processingData();
				packForThread->coords = new vector<matrixCoordinates*>;
				packForThread->firstMatrix = firstMatrix;
				packForThread->secondMatrix = secondMatrix;
				packForThread->resultMatrix = result;
				unsigned int element = 0;
				do {
					matrixCoordinates* data = new matrixCoordinates({ row,column });
					packForThread->coords->push_back(data);
					element++;
				} while (result->tryToGoForward(row, column) && element < step);

				threadPromises[thread]->set_value(packForThread);
			}

			for (unsigned int thread = 0; thread < numberOfThreads; thread++) {
				threadPool[thread]->join();
			}
			return result;
		}
		catch (number_cast_exception exception) {
			throw incorrect_input_data_exception("it is impossible to perform multiplication");
		}
	}

	vector<BasicDataType*> Matrix::iterativeStepwiseMethod(BasicDataType* inaccurancy){
		Matrix buffer_Matrix = this->clone();
		vector<BasicDataType*> MatrixX_elements;

		for (int i = 0; i < this->getNumberOfRows(); i++) {
			MatrixX_elements.push_back(this->getNeutralElementWithRespectToMultiplication());
		}
		Matrix MatrixX(MatrixX_elements, this->getNumberOfRows(), 1, this->getCurrentTypeManager());
		BasicDataType* l_value = this->getNeutralElementWithRespectToMultiplication();
		BasicDataType* previous_l_value;

		do {
			previous_l_value = l_value->clone();
			BasicDataType* previous_x_value = MatrixX.getValueAt(0,0);
			MatrixX = buffer_Matrix * MatrixX;
			l_value = dynamic_cast<NumberDataType*>(MatrixX.getValueAt(0, 0))->multiplicationByReverseElement(dynamic_cast<NumberDataType*>(previous_x_value));

		} while (checkInaccuracy({ l_value }, { previous_l_value }, inaccurancy));
		vector<BasicDataType*>values = MatrixX.getFullArrayOfValues();
		values.push_back(l_value);
		return values;
	}

	vector<vector<BasicDataType*>> Matrix::DanilevskyMethod(vector<BasicDataType*> L_array){

		Matrix MatrixA = this->clone();
		Matrix MatrixS = Matrix::createUnitMatrix(this->getNumberOfRows(), this->getCurrentTypeManager());
		for(int row_index = this->getNumberOfRows() - 1; row_index > 0; row_index--) {
			Matrix MatrixM = Matrix::createUnitMatrix(this->getNumberOfRows(), this->getCurrentTypeManager());
			Matrix reverse_MatrixM = Matrix::createUnitMatrix(this->getNumberOfRows(), this->getCurrentTypeManager());

			MatrixM.rowReplacement(row_index-1,MatrixA.getRow(row_index));
			MatrixM.rowReplacement(row_index-1,MatrixM.rowMultiplicationByReverseConstant(row_index-1,dynamic_cast<NumberDataType*>(MatrixA.getValueAt(row_index , row_index-1))->inverseOfAddition()));
			MatrixM.setValueAt(row_index-1,row_index-1, dynamic_cast<NumberDataType*>(MatrixM.getValueAt(row_index-1,row_index-1))->multiplicationByReverseElement(dynamic_cast<NumberDataType*>(MatrixA.getValueAt(row_index, row_index-1))->inverseOfAddition()));

			reverse_MatrixM.rowReplacement(row_index-1, MatrixA.getRow(row_index));

			MatrixA = reverse_MatrixM * MatrixA * MatrixM;
			MatrixS = MatrixS * MatrixM;
		}

		vector<BasicDataType*> p_array;
		for (int column_index = 0; column_index < this->getNumberOfColumns(); column_index++) {
			p_array.push_back(MatrixA.getValueAt(0, column_index));
		}

		/*vector<BasicDataType*> current_y_array;

		vector<BasicDataType*> current_l_array;
		vector<BasicDataType*> previous_l_array;

		for (int column_index = 0; column_index < this->getNumberOfColumns(); column_index++) {
			current_y_array.push_back(start_value);
			current_l_array.push_back(start_value);
		}
		Matrix Matrix_Y(current_y_array, current_y_array.size(), 1,  this->getCurrentTypeManager());
		vector<Matrix> Matrix_X_array;
		for (int i = 0; i < current_y_array.size(); i++) {
			Matrix_Y = Matrix_Y.MatrixTranspose();
			Matrix_Y = MatrixA * Matrix_Y;
			Matrix_Y = Matrix_Y.MatrixTranspose();
			Matrix Matrix_X = MatrixS * Matrix_Y;
			Matrix_X_array.push_back(Matrix_X);
		}
		int i_round = 0;
		do {

			previous_l_array = current_l_array;
			BasicDataType* sum = this->getNeutralElementWithRespectToAddition();
			for (int i = 0; i < current_y_array.size(); i++) {
				sum = sum->addition(p_array[i]->multiplication(current_l_array[i]->multiplication(Matrix_X_array[i].getValueAt(i,i_round))));
			}

			
			i_round++;
		} while (checkInaccuracy(current_l_array, previous_l_array, inaccurancy));

		*/
		
		vector<vector<BasicDataType*>> result;
		for (int i = 0; i < L_array.size(); i++) {
			vector<BasicDataType*>array_of_y_elements(L_array.size());
			array_of_y_elements[array_of_y_elements.size()-1] = this->getNeutralElementWithRespectToMultiplication();
			for (int k = L_array.size()-1; k>0; k--) {
				array_of_y_elements[k - 1] = array_of_y_elements[k]->multiplication(L_array[i]);
			}
			Matrix Matrix_Y_I(array_of_y_elements, array_of_y_elements.size(), 1,this->getCurrentTypeManager());
			Matrix result_X_Matrix = MatrixS * Matrix_Y_I;
			result.push_back(result_X_Matrix.getFullArrayOfValues());
		}

		return result;
	}

	Matrix Matrix::SeidelMethod(BasicDataType* inaccurancy){
		vector<BasicDataType*>current_array_of_x;
		for (int i = 0; i < this->getNumberOfRows(); i++) {
			current_array_of_x.push_back(this->getNeutralElementWithRespectToAddition());
		}
		vector<BasicDataType*>previous_array_of_x;

		do {
			previous_array_of_x = current_array_of_x;
			for (int row_index = 0; row_index < this->getNumberOfRows(); row_index++) {
				BasicDataType* sum = this->getNeutralElementWithRespectToAddition();
				sum = sum->addition(this->getValueAt(row_index, this->getNumberOfColumns() - 1));
				for (int column_index = 0; column_index < this->getNumberOfColumns() - 1; column_index++) {
					if (row_index < column_index) {
						sum = sum->addition(dynamic_cast<NumberDataType*>(previous_array_of_x[column_index]->multiplication(this->getValueAt(row_index, column_index)))->inverseOfAddition());
					}
					if (row_index > column_index) {
						sum = sum->addition(dynamic_cast<NumberDataType*>(current_array_of_x[column_index]->multiplication(this->getValueAt(row_index, column_index)))->inverseOfAddition());
					}

				}
				current_array_of_x[row_index] = dynamic_cast<NumberDataType*>(sum)->multiplicationByReverseElement(dynamic_cast<NumberDataType*>(this->getValueAt(row_index, row_index)));
			}
		} while (checkInaccuracy(current_array_of_x, previous_array_of_x, inaccurancy));

		return Matrix(current_array_of_x, current_array_of_x.size(), 1, this->getCurrentTypeManager());
	}

	Matrix Matrix::methodOfSimpleIterations(BasicDataType* inaccurancy){
		vector<BasicDataType*>current_array_of_x;
		for (int i = 0; i < this->getNumberOfRows(); i++) {
			current_array_of_x.push_back(this->getNeutralElementWithRespectToAddition());
		}
		vector<BasicDataType*>previous_array_of_x;
	
		do {
			previous_array_of_x = current_array_of_x;
			for (int row_index = 0; row_index < this->getNumberOfRows();row_index++) {
				BasicDataType* sum = this->getNeutralElementWithRespectToAddition();
				sum = sum->addition(this->getValueAt(row_index,this->getNumberOfColumns()-1));
				for (int column_index = 0; column_index < this->getNumberOfColumns() - 1; column_index++) {
					if (row_index != column_index){
						sum = sum->addition(dynamic_cast<NumberDataType*>(previous_array_of_x[column_index]->multiplication(this->getValueAt(row_index, column_index)))->inverseOfAddition());
					}
					
				}
				current_array_of_x[row_index] = dynamic_cast<NumberDataType*>(sum)->multiplicationByReverseElement(dynamic_cast<NumberDataType*>(this->getValueAt(row_index, row_index)));
			}
		} while (checkInaccuracy(current_array_of_x,previous_array_of_x, inaccurancy));
		
		return Matrix(current_array_of_x,current_array_of_x.size(),1,this->getCurrentTypeManager());
	}

	Matrix Matrix::runThroughMethod() {
		if (this->number_of_columns <= 2)throw incorrect_input_data_exception("Wrong Matrix");
		Matrix buffer_Matrix = this->clone();
		if (buffer_Matrix.getNumberOfRows() != buffer_Matrix.getNumberOfColumns()-1) throw incorrect_input_data_exception("This is not square Matrix");
		if (!buffer_Matrix.clone(buffer_Matrix.getNumberOfRows(), buffer_Matrix.getNumberOfColumns() - 1).IsThreeDiagonalMatrix())throw incorrect_input_data_exception("This is not three-diagonal Matrix");


		try {
			for (int row_index = 1, expressed_index = 1; row_index < buffer_Matrix.getNumberOfRows(); row_index++, expressed_index++) {
				BasicDataType* result = dynamic_cast<NumberDataType*>((dynamic_cast<NumberDataType*>(buffer_Matrix.getValueAt(row_index, expressed_index-1)->multiplication(buffer_Matrix.getValueAt(row_index-1,row_index)))
					->inverseOfAddition())->addition(buffer_Matrix.getValueAt(row_index - 1, row_index-1)->multiplication(buffer_Matrix.getValueAt(row_index, row_index))))->multiplicationByReverseElement(dynamic_cast<NumberDataType*>(buffer_Matrix.getValueAt(row_index - 1, row_index-1)));
				buffer_Matrix.setValueAt(row_index, row_index, result);
				result = buffer_Matrix.getValueAt(row_index, buffer_Matrix.getNumberOfColumns() - 1)
					->addition((dynamic_cast<NumberDataType*>((dynamic_cast<NumberDataType*>(buffer_Matrix.getValueAt(row_index-1, buffer_Matrix.getNumberOfColumns() - 1)->multiplication(buffer_Matrix.getValueAt(row_index,row_index-1)))->multiplicationByReverseElement(dynamic_cast<NumberDataType*>(buffer_Matrix.getValueAt(row_index - 1, row_index-1))))))->inverseOfAddition());
				buffer_Matrix.setValueAt(row_index, buffer_Matrix.getNumberOfColumns() - 1, result);
				buffer_Matrix.setValueAt(row_index, expressed_index - 1,this->getNeutralElementWithRespectToAddition());
			}

			vector<BasicDataType*> answer_array(buffer_Matrix.getNumberOfRows());
			answer_array[buffer_Matrix.getNumberOfRows()-1] = (dynamic_cast<NumberDataType*>(buffer_Matrix.getValueAt(buffer_Matrix.getNumberOfRows() - 1, buffer_Matrix.getNumberOfColumns() - 1))
				->multiplicationByReverseElement(dynamic_cast<NumberDataType*>(buffer_Matrix.getValueAt(buffer_Matrix.getNumberOfRows() - 1, buffer_Matrix.getNumberOfColumns() - 2))));

			for(int row_index = buffer_Matrix.getNumberOfRows() - 2;row_index>=0; row_index--) {
				
				BasicDataType* current_b_value = answer_array[row_index + 1]->multiplication(buffer_Matrix.getValueAt(row_index,row_index+1));
				answer_array[row_index] = (dynamic_cast<NumberDataType*>(buffer_Matrix.getValueAt(row_index, buffer_Matrix.getNumberOfColumns() - 1)->addition(dynamic_cast<NumberDataType*>(current_b_value)->inverseOfAddition()))
					->multiplicationByReverseElement(dynamic_cast<NumberDataType*>(buffer_Matrix.getValueAt(row_index, row_index))));

			}
			
			return Matrix(answer_array,buffer_Matrix.getNumberOfRows(),1,this->getCurrentTypeManager());

		}
		catch (number_cast_exception exception) {
			throw new  incorrect_input_data_exception("it is impossible to perform searching of SLAU solution");
		}
	}


	Matrix Matrix::squareRootsMethod(){
		if (this->number_of_columns <= 1)throw incorrect_input_data_exception("Wrong Matrix");
		Matrix buffer_Matrix = this->clone(this->number_of_rows, this->number_of_columns - 1);
		Matrix f_column = this->clone(0, this->number_of_rows, this->number_of_columns - 1, this->number_of_columns);
		if (buffer_Matrix.getNumberOfRows() != buffer_Matrix.getNumberOfColumns()) throw incorrect_input_data_exception("This is not square Matrix");
		if ((buffer_Matrix.findMatrixDeterminantN()->equal(buffer_Matrix.getNeutralElementWithRespectToAddition())))throw number_exception("there are no solutions");

		try {
			Matrix MatrixS(buffer_Matrix.getNumberOfRows(), buffer_Matrix.getNumberOfColumns(),this->getCurrentTypeManager());
			Matrix MatrixD = Matrix::createUnitMatrix(buffer_Matrix.getNumberOfRows(), this->getCurrentTypeManager());
			for (int row_index = 0; row_index < MatrixS.getNumberOfRows(); row_index++) {

				BasicDataType* sum_value = this->getNeutralElementWithRespectToAddition();
				for (int inner_index = 0; inner_index < row_index; inner_index++) {
					sum_value = sum_value->addition((MatrixS.getValueAt(inner_index, row_index)->multiplication(MatrixS.getValueAt(inner_index, row_index))));
				}
				BasicDataType* result = buffer_Matrix.getValueAt(row_index, row_index)->addition(dynamic_cast<NumberDataType*>(sum_value)->inverseOfAddition());
				if (!result->moreThan(this->getNeutralElementWithRespectToAddition()) && !result->equal(this->getNeutralElementWithRespectToAddition())) {
					MatrixD.setValueAt(row_index, row_index, dynamic_cast<NumberDataType*>(MatrixD.getValueAt(row_index,row_index))->inverseOfAddition());
					result = dynamic_cast<NumberDataType*>(result)->inverseOfAddition();
				}
				MatrixS.setValueAt(row_index, row_index, dynamic_cast<NumberDataType*>(result)->findSquareRoot());
				for (int column_index = row_index+1; column_index < MatrixS.getNumberOfColumns(); column_index++) {
					BasicDataType* sum_value = this->getNeutralElementWithRespectToAddition();
					for (int inner_index = 0; inner_index < row_index; inner_index++) {
						sum_value = sum_value->addition(MatrixS.getValueAt(inner_index, row_index)->multiplication(MatrixS.getValueAt(inner_index, column_index)));
					}
					sum_value = buffer_Matrix.getValueAt(row_index, column_index)->addition((dynamic_cast<NumberDataType*>(sum_value)->inverseOfAddition()));
					sum_value = (dynamic_cast<NumberDataType*>(sum_value)->multiplicationByReverseElement(dynamic_cast<NumberDataType*>(MatrixS.getValueAt(row_index,row_index))));
					MatrixS.setValueAt(row_index, column_index, sum_value->clone());
					delete sum_value;
				}
			}

			vector<BasicDataType*> result_array;
			Matrix MatrixSTD = MatrixS.MatrixTranspose() * MatrixD;
			for (int index_of_column = 0, index_of_row = 0; index_of_row < MatrixSTD.getNumberOfRows()  && index_of_column < MatrixSTD.getNumberOfColumns(); index_of_column++, index_of_row++) {
				BasicDataType* right_side_of_the_equation = f_column.getValueAt(index_of_row, 0)->clone();
				for (int x = 0; x < index_of_column;x++) {
					right_side_of_the_equation = right_side_of_the_equation->addition(dynamic_cast<NumberDataType*>((MatrixSTD.getValueAt(index_of_row, x))->multiplication((result_array[x])))->inverseOfAddition());
				}
				result_array.push_back(dynamic_cast<NumberDataType*>(right_side_of_the_equation)->multiplicationByReverseElement(dynamic_cast<NumberDataType*>(MatrixSTD.getValueAt(index_of_row, index_of_row))));
			}

			Matrix Y_column(result_array,result_array.size(),1, MatrixS.getCurrentTypeManager());
			for (int index_of_row = MatrixS.getNumberOfRows()-1, index_of_column = MatrixS.getNumberOfColumns() - 1; index_of_row >=0 && index_of_column >=0; index_of_column--, index_of_row--) {
				BasicDataType* right_side_of_the_equation = Y_column.getValueAt(index_of_row, 0)->clone();
				for (int x = MatrixS.getNumberOfRows() - 1; x > index_of_column;x--) {
					right_side_of_the_equation = right_side_of_the_equation->addition(dynamic_cast<NumberDataType*>((MatrixS.getValueAt(index_of_row, x))->multiplication((result_array[x])))->inverseOfAddition());
				}
				result_array[index_of_row] = (dynamic_cast<NumberDataType*>(right_side_of_the_equation)->multiplicationByReverseElement(dynamic_cast<NumberDataType*>(MatrixS.getValueAt(index_of_row, index_of_row))));
			}

			return Matrix(result_array,result_array.size(),1,MatrixS.getCurrentTypeManager());
		}
		catch (number_cast_exception exception) {
			throw new  incorrect_input_data_exception("it is impossible to perform searching of SLAU solution");
		}

	}

	Matrix Matrix::MatrixTranspose(){
		vector<BasicDataType*>buffer_array = this->getFullArrayOfValues();
		Matrix result_Matrix(number_of_columns,number_of_rows,this->getCurrentTypeManager());
		result_Matrix.fillInByColumns(buffer_array);
		freeUpVector(buffer_array);
		return result_Matrix;
	}

	Matrix Matrix::findReverseMatrixN(){
		try {
			if (this->number_of_rows != this->number_of_columns) throw incorrect_input_data_exception("This is not square Matrix");
			BasicDataType* determiner = this->findMatrixDeterminantN();
			if (determiner->equal(this->getNeutralElementWithRespectToAddition()))throw incorrect_input_data_exception("This Matrix has't a reverse Matrix");
			Matrix transposed_Matrix = this->MatrixTranspose();
			Matrix reverse_Matrix(this->number_of_rows,this->number_of_columns,this->getCurrentTypeManager());
			vector<BasicDataType*>array_of_values;
			for (int i = 0; i < this->number_of_rows; i++) {
				for (int k = 0; k < this->number_of_columns; k++) {
					NumberDataType* buffer = dynamic_cast<NumberDataType*>((transposed_Matrix.cloneWithoutRowAndColumn(i, k)).findMatrixDeterminantN());
					if ((i + k) % 2 != 0)buffer = buffer->inverseOfAddition();
					array_of_values.push_back(buffer);
				}
			}
			reverse_Matrix.fillInByRows(array_of_values);
			reverse_Matrix = reverse_Matrix.multiplyMatrixByReverseConstantN(determiner);
			return reverse_Matrix;
		}
		catch (number_exception) {
			throw incorrect_input_data_exception("There are not reverse Matrix");
		}
		catch (bad_cast) {
			throw incorrect_input_data_exception("There are not reverse Matrix");
		}
	}

	BasicDataType* Matrix::findMatrixDeterminantN(){
		try {

			if (this->number_of_rows != this->number_of_columns) throw incorrect_input_data_exception("This is not square Matrix");
			
			vector<BasicDataType*>distortion;
			vector<NumberDataType*>buffer_distortion;
			Matrix buffer_Matrix = this->findUpperTriangularMatrix(distortion);
			vector<NumberDataType*>main_diagonal_multipliers;

			for (int i = 0; i < buffer_Matrix.getNumberOfRows(); i++) {
				main_diagonal_multipliers.push_back(dynamic_cast<NumberDataType*>(buffer_Matrix.getValueAt(i, i)));
			}

			for (vector<BasicDataType*>::iterator distortion_iter = distortion.begin(); distortion_iter != distortion.end(); distortion_iter++) {
				buffer_distortion.push_back(dynamic_cast<NumberDataType*>(*distortion_iter));
			}

			return dynamic_cast<NumberDataType*>(this->getCurrentTypeManager()->getAccessToObject())->reduceValuesOfNumbersInArrays(main_diagonal_multipliers, buffer_distortion);
		}
		catch (number_cast_exception exception) {
			throw new  incorrect_input_data_exception("it is impossible to perform searching of determine");
		}
		catch (bad_cast) {
			throw new  incorrect_input_data_exception("it is impossible to perform searching of determine");
		}
		catch (number_exception) {
			return this->getNeutralElementWithRespectToAddition();
		}
	}

	Matrix Matrix::GaussMethodN(){

		if (this->number_of_columns <= 1)throw incorrect_input_data_exception("Wrong Matrix");
		Matrix buffer_Matrix = this->clone(this->number_of_rows,this->number_of_columns-1); 
		Matrix answer_column = this->clone(0,this->number_of_rows, this->number_of_columns - 1, this->number_of_columns);
		if (buffer_Matrix.getNumberOfRows() != buffer_Matrix.getNumberOfColumns()) throw incorrect_input_data_exception("This is not square Matrix");
		if ((buffer_Matrix.findMatrixDeterminantN()->equal(buffer_Matrix.getNeutralElementWithRespectToAddition())))throw number_exception("there are no solutions");

		try {
			
			vector<BasicDataType*>result_array;
			buffer_Matrix = buffer_Matrix.findUpperTriangularMatrix(answer_column);

			for (int i = buffer_Matrix.getNumberOfRows() - 1, k = 0; i >= 0 && k < buffer_Matrix.getNumberOfRows(); i--, k++) {
				BasicDataType* right_side_of_the_equation = answer_column.getValueAt(i, 0)->clone();
				for (int j = 0,l = buffer_Matrix.getNumberOfRows() - 1 ; j < k && l >= 0; j++,l--) {
					right_side_of_the_equation = right_side_of_the_equation->addition(dynamic_cast<NumberDataType*>((buffer_Matrix.getValueAt(i, l))->multiplication((result_array[j])))->inverseOfAddition());
				}
				result_array.push_back(dynamic_cast<NumberDataType*>(right_side_of_the_equation)->multiplicationByReverseElement(dynamic_cast<NumberDataType*>(buffer_Matrix.getValueAt(i, i))));
			}
			vector<BasicDataType*> column_array;
			for (vector<BasicDataType*>::reverse_iterator iter = result_array.rbegin(); iter != result_array.rend(); iter++) {
				column_array.push_back(*iter);
			}

			return Matrix(column_array, this->number_of_rows, 1, this->getCurrentTypeManager());
		}
		catch (number_cast_exception exception) {
			throw new  incorrect_input_data_exception("it is impossible to perform searching of SLAU solution");
		}
		
	}

	Matrix Matrix::GaussJordanMethodF()
	{

		if (this->number_of_columns <= 1)throw incorrect_input_data_exception("Wrong Matrix");
		Matrix buffer_Matrix = this->clone(this->number_of_rows, this->number_of_columns - 1);
		Matrix answer_column = this->clone(0, this->number_of_rows, this->number_of_columns - 1, this->number_of_columns);
		if (buffer_Matrix.getNumberOfRows() != buffer_Matrix.getNumberOfColumns()) throw incorrect_input_data_exception("This is not square Matrix");
		if ((buffer_Matrix.findMatrixDeterminantN()->equal(buffer_Matrix.getNeutralElementWithRespectToAddition())))throw number_exception("there are no solutions");

		try {

			for (int i = 0; i < this->getNumberOfColumns() - 1; i++) {

				int index_of_first_non_zero_object = this->indexOfFirstNonZeroElemenInColumnUp(i, i);
				if (index_of_first_non_zero_object == -1)throw number_exception("there is not solution ");
				if (index_of_first_non_zero_object != i)rowSwap(i, index_of_first_non_zero_object);


				answer_column.rowReplacement(i,answer_column.rowMultiplicationByReverseConstant(i, dynamic_cast<NumberDataType*>(buffer_Matrix.getValueAt(i, i))));
				buffer_Matrix.rowReplacement(i,buffer_Matrix.rowMultiplicationByReverseConstant(i, dynamic_cast<NumberDataType*>(buffer_Matrix.getValueAt(i, i)))); 

				for (int k = i + 1; k < buffer_Matrix.getNumberOfRows(); k++) {
					if (!(getValueAt(k, i)->equal(this->getNeutralElementWithRespectToAddition()))) {

						vector<BasicDataType*> top_row = buffer_Matrix.rowMultiplicationByConstant(i, dynamic_cast<NumberDataType*>(buffer_Matrix.getValueAt(k, i))->inverseOfAddition());
						vector<BasicDataType*> top_answer_row = answer_column.rowMultiplicationByConstant(i, dynamic_cast<NumberDataType*>(buffer_Matrix.getValueAt(k, i))->inverseOfAddition());
						buffer_Matrix.rowReplacement(k,buffer_Matrix.rowAddition(top_row, buffer_Matrix.getRow(k)));
						answer_column.rowReplacement(k,answer_column.rowAddition(top_answer_row, answer_column.getRow(k)));
						this->freeUpVector(top_row);
						this->freeUpVector(top_answer_row);

					}
				}
			}


			for (int i =  buffer_Matrix.getNumberOfColumns() - 1; i>=0 ; i--) {

				int index_of_first_non_zero_object = this->indexOfFirstNonZeroElemenInColumnDown(i, i);
				if (index_of_first_non_zero_object == -1)throw number_exception("there is not solution ");
				if (index_of_first_non_zero_object != i)rowSwap(i, index_of_first_non_zero_object);

				for (int k = i - 1; k >=0 ; k--) {
					if (!(getValueAt(k, i)->equal(this->getNeutralElementWithRespectToAddition()))) {

						vector<BasicDataType*> top_row = buffer_Matrix.rowMultiplicationByConstant(i, dynamic_cast<NumberDataType*>(buffer_Matrix.getValueAt(k, i))->inverseOfAddition());
						vector<BasicDataType*> top_answer_row = answer_column.rowMultiplicationByConstant(i, dynamic_cast<NumberDataType*>(buffer_Matrix.getValueAt(k, i))->inverseOfAddition());
						buffer_Matrix.rowReplacement(k,buffer_Matrix.rowAddition(top_row, buffer_Matrix.getRow(k)));
						answer_column.rowReplacement(k,answer_column.rowAddition(top_answer_row, answer_column.getRow(k)));
						this->freeUpVector(top_row);
						this->freeUpVector(top_answer_row);

					}
				}
			}

			return answer_column;
		}
		catch (number_cast_exception exception) {
			throw new  incorrect_input_data_exception("it is impossible to perform searching of SLAU solution");
		}

	}

	Matrix Matrix::GaussMethodWithMainElementF(){
		
		if (this->number_of_columns <= 1)throw incorrect_input_data_exception("Wrong Matrix");
		Matrix buffer_Matrix = this->clone(this->number_of_rows, this->number_of_columns - 1);
		Matrix answer_column = this->clone(0, this->number_of_rows, this->number_of_columns - 1, this->number_of_columns);
		if (buffer_Matrix.getNumberOfRows() != buffer_Matrix.getNumberOfColumns()) throw incorrect_input_data_exception("This is not square Matrix");
		if ((buffer_Matrix.findMatrixDeterminantN()->equal(buffer_Matrix.getNeutralElementWithRespectToAddition())))throw number_exception("there are no solutions");

		try {

			vector<BasicDataType*>result_array;
			
			for (int i = 0; i < this->getNumberOfColumns()-1; i++) {

				int index_of_first_non_zero_object = this->indexOfFirstNonZeroElemenInColumnUp(i, i);
				if (index_of_first_non_zero_object == -1)throw number_exception("there is not solution ");
				int max_index = this->indexOfMaximumElemenInColumn(i, i);
				if (max_index != i)rowSwap(i, max_index);


				answer_column.rowReplacement(i,answer_column.rowMultiplicationByReverseConstant(i, dynamic_cast<NumberDataType*>(buffer_Matrix.getValueAt(i, i))));
				buffer_Matrix.rowReplacement(i,buffer_Matrix.rowMultiplicationByReverseConstant(i, dynamic_cast<NumberDataType*>(buffer_Matrix.getValueAt(i, i))));
				
				
				for (int k = i + 1; k < buffer_Matrix.getNumberOfRows(); k++) {
					if (!(getValueAt(k, i)->equal(this->getNeutralElementWithRespectToAddition()))) {

						vector<BasicDataType*> top_row = buffer_Matrix.rowMultiplicationByConstant(i,dynamic_cast<NumberDataType*>(buffer_Matrix.getValueAt(k,i))->inverseOfAddition());
						vector<BasicDataType*> top_answer_row = answer_column.rowMultiplicationByConstant(i, dynamic_cast<NumberDataType*>(buffer_Matrix.getValueAt(k, i))->inverseOfAddition());
						buffer_Matrix.rowReplacement(k,buffer_Matrix.rowAddition(top_row, buffer_Matrix.getRow(k)));
						answer_column.rowReplacement(k,answer_column.rowAddition(top_answer_row, answer_column.getRow(k)));
						this->freeUpVector(top_row);
						this->freeUpVector(top_answer_row);

					}
				}
			}

			for (int i = buffer_Matrix.getNumberOfRows() - 1, k = 0; i >= 0 && k < buffer_Matrix.getNumberOfRows(); i--, k++) {
				BasicDataType* right_side_of_the_equation = answer_column.getValueAt(i, 0)->clone();
				for (int j = 0, l = buffer_Matrix.getNumberOfRows() - 1; j < k && l >= 0; j++, l--) {
					right_side_of_the_equation = right_side_of_the_equation->addition(dynamic_cast<NumberDataType*>((buffer_Matrix.getValueAt(i, l))->multiplication((result_array[j])))->inverseOfAddition());
				}
				result_array.push_back(dynamic_cast<NumberDataType*>(right_side_of_the_equation)->multiplicationByReverseElement(dynamic_cast<NumberDataType*>(buffer_Matrix.getValueAt(i, i))));
			}
			vector<BasicDataType*> column_array;
			for (vector<BasicDataType*>::reverse_iterator iter = result_array.rbegin(); iter != result_array.rend(); iter++) {
				column_array.push_back(*iter);
			}

			return Matrix(column_array, this->number_of_rows, 1, this->getCurrentTypeManager());
		}
		catch (number_cast_exception exception) {
			throw new  incorrect_input_data_exception("it is impossible to perform searching of SLAU solution");
		}

	}

	Matrix Matrix::multiplyMatrixByReverseConstantN(BasicDataType* constant){

		try {
			vector<BasicDataType*> array_of_values;
			Matrix result_Matrix(this->number_of_rows, number_of_columns, this->getCurrentTypeManager());

			for (int row_index = 0; row_index < number_of_rows; row_index++) {
				for (int column_index = 0; column_index < this->getNumberOfColumns(); column_index++) {
					array_of_values.push_back(dynamic_cast<NumberDataType*>(getValueAt(row_index, column_index))->multiplicationByReverseElement(dynamic_cast<NumberDataType*>(constant)));
				}
			}

			result_Matrix.fillInByRows(array_of_values);
			this->freeUpVector(array_of_values);
			return result_Matrix;
		}
		catch (number_exception) {
			throw incorrect_input_data_exception("there is not reverse element for current constant");
		}
	
	}

	bool Matrix::empty(){
		return this->values.size()== 0;
	}

	Matrix Matrix::multiplyMatrixByConstant(BasicDataType* constant){
		
		vector<BasicDataType*> array_of_values;
		Matrix result_Matrix(this->number_of_rows,number_of_columns,this->getCurrentTypeManager());
		try {
			for (int row_index = 0; row_index < number_of_rows; row_index++) {
				for (int column_index = 0; column_index < number_of_columns; column_index++) {
					array_of_values.push_back(getValueAt(row_index, column_index)->multiplication(constant));
				}
			}
		}
		catch (number_exception) {
			throw incorrect_input_data_exception("there is not reverse element for current constant");
		}

		result_Matrix.fillInByRows(array_of_values);
		this->freeUpVector(array_of_values);
		return result_Matrix;

	}


	int Matrix::indexOfFirstNonZeroElemenInColumnUp(int index_of_column, int index_of_top){
		BasicDataType* neutral_element = this->getNeutralElementWithRespectToAddition();
		for (int i = index_of_top; i < this->number_of_rows;i++) {
			if (!values[i][index_of_column]->equal(neutral_element)) {
				delete neutral_element;
				return i;
			}
		}
		delete neutral_element;
		return -1;
	}

	int Matrix::indexOfMaximumElemenInColumn(int index_of_column, int index_of_top){
		BasicDataType* max_element = values[index_of_top][index_of_column]->clone();
		int result_index = index_of_top;
		for (int i = index_of_top; i < number_of_rows; i++) {
			if (values[i][index_of_column]->moreThan(max_element)) {
				delete max_element;
				max_element = values[i][index_of_column]->clone();
				result_index = i;
			}
		}
		return result_index;
	}

	int Matrix::indexOfFirstNonZeroElemenInColumnDown(int index_of_column, int index_of_top) {
		BasicDataType* neutral_element = this->getNeutralElementWithRespectToAddition();
		for (int i = index_of_top; i >= 0; i--) {
			if (!(values[i][index_of_column]->equal(neutral_element))) {
				delete neutral_element;
				return i;
			}
		}
		delete neutral_element;
		return -1;
	}

	vector<BasicDataType*> Matrix::rowAddition(vector<BasicDataType*> first_row, vector<BasicDataType*> second_row)
	{
		vector<BasicDataType*> result_row;
		if (first_row.size() != second_row.size())throw incorrect_input_data_exception("These rows are not equal");
		try {
			for (vector<BasicDataType*>::iterator first_row_iter = first_row.begin(), second_row_iter = second_row.begin();
				first_row_iter != first_row.end() && second_row_iter != second_row.end();
				first_row_iter++, second_row_iter++) {
				result_row.push_back((*first_row_iter)->addition(*second_row_iter));
			}
			return result_row;
		}
		catch (number_cast_exception exception) {
			throw new  incorrect_input_data_exception("it is impossible to perform an addition");
		}
	}

	vector<BasicDataType*> Matrix::rowMultiplicationByConstant(int index_of_row, BasicDataType* constant){
		vector<BasicDataType*> result;
		if (index_of_row >= this->number_of_rows)throw incorrect_input_data_exception("There isn't row with this index.");
		try{
			for (int column_index = 0; column_index < number_of_columns; column_index++) {
				result.push_back(this->getValueAt(index_of_row,column_index)->multiplication(constant));
			}
			return result;
		}
		catch (number_cast_exception exception) {
			throw new  incorrect_input_data_exception("it is impossible to perform an addition");
		}

	}

	vector<BasicDataType*> Matrix::rowMultiplicationByReverseConstant(int index_of_row, BasicDataType* constant)
	{
		vector<BasicDataType*> result;
		if (index_of_row >= this->number_of_rows)throw incorrect_input_data_exception("There isn't row with this index.");
		try {
			for (int column_index = 0; column_index < number_of_columns; column_index++) {
				result.push_back(dynamic_cast<NumberDataType*>(this->getValueAt(index_of_row, column_index))->multiplicationByReverseElement(dynamic_cast<NumberDataType*>(constant)));
			}
			return result;
		}
		catch (number_cast_exception exception) {
			throw new  incorrect_input_data_exception("it is impossible to perform an addition");
		}
	}

	void Matrix::rowReplacement(int index_of_row,vector<BasicDataType*> new_row){
		if (this->number_of_columns != new_row.size()) throw incorrect_input_data_exception("row sizes are not the same");
		if (index_of_row > this->getNumberOfRows()) throw incorrect_input_data_exception("wrong index of current row");
		this->freeUpMemoryInRow(index_of_row);
		this->fillRow(index_of_row, new_row);
	}

	void Matrix::rowSwap(int index_of_first_row, int index_of_second_row){
		if (this->number_of_rows < index_of_first_row || this->number_of_rows < index_of_second_row)throw incorrect_input_data_exception("wrong Matrix size");
		vector<BasicDataType*> buffer_row = values[index_of_first_row];
		values[index_of_first_row] = values[index_of_second_row];;
		values[index_of_second_row] = buffer_row;
	}

	bool Matrix::IsThreeDiagonalMatrix(){

		if (this->getNumberOfColumns() != this->getNumberOfRows())return false;
		for (int row_index = 0; row_index < this->getNumberOfRows(); row_index++) {
			for (int column_index = 0; column_index < this->getNumberOfRows(); column_index++) {
				if (abs(column_index-row_index) <= 1) {
					if (this->getValueAt(row_index, column_index)->equal(this->getNeutralElementWithRespectToAddition()))return false;
				}
				else {
					if (!(this->getValueAt(row_index, column_index)->equal(this->getNeutralElementWithRespectToAddition())))return false;
				}
			}
		}

		return true;
	}

	BasicDataType* Matrix::goForward(int& currentRow, int& currentColumn)
	{
		if(currentColumn < 0 || currentRow < 0 || (currentRow + 1 >= this->getNumberOfRows() && currentColumn+ 1 >= this->getNumberOfColumns()))
			throw  incorrect_input_data_exception("Invalid currentRow or column when you are trying to go forward in this matrix.");
		if (currentColumn + 1 < this->getNumberOfColumns()) {
			currentColumn++;
		}
		else {
			currentColumn = 0;
			currentRow++;
		}
	}

	bool Matrix::isPossibleToGoForward(int currentRow, int currentColumn)
	{
		if (currentColumn < 0 || currentRow < 0 || (currentRow + 1 >= this->getNumberOfRows() && currentColumn + 1 >= this->getNumberOfColumns())) return false;
		else return true;
	}

	bool Matrix::tryToGoForward(short int& currentRow,short int& currentColumn){
		if (currentColumn < 0 || currentRow < 0 || (currentRow + 1 >= this->getNumberOfRows() && currentColumn + 1 >= this->getNumberOfColumns()))
			return false;
		if (currentColumn + 1 < this->getNumberOfColumns()) {
			currentColumn++;
		}
		else {
			currentColumn = 0;
			currentRow++;
		}
		return true;
	}

	vector<BasicDataType*> Matrix::reduceValuesInLineN(int index_of_row, BasicDataType* constant){
		if (index_of_row >= this->number_of_rows)throw incorrect_input_data_exception("There isn't row with this index.");
		vector<BasicDataType*> result;
		try {
			
			for (int column_index = 0; column_index < number_of_columns;column_index++) {
				result.push_back(dynamic_cast<NumberDataType*>(this->getValueAt(index_of_row,column_index))->multiplicationByReverseElement(dynamic_cast<NumberDataType*>(constant)));
			}

			return result;
		}
		catch (bad_cast exception) {
			this->freeUpVector(result);
			throw number_cast_exception("it is impossible to cast values");
		}
		catch (number_exception exception) {
			this->freeUpVector(result);
			throw number_cast_exception("it is impossible to perform an reuducing of values");
		}
	}

	vector<BasicDataType*> Matrix::getFullArrayOfValues(){
		vector<BasicDataType*> result;

		for (int row_index = 0; row_index < number_of_rows;row_index++) {
			for (int column_index = 0; column_index < number_of_columns; column_index++)
			{
				result.push_back(this->getValueAt(row_index,column_index)->clone());
			}
		}
		return result;
	}

	vector<BasicDataType*> Matrix::convertMatrixIntoLowerTriangularMatrix(Matrix& tracking_Matrix){
		vector<BasicDataType*> tracking_array;
		for (int i = this->getNumberOfColumns()-1; i >=0 ; i--) {

			int index_of_first_non_zero_object = this->indexOfFirstNonZeroElemenInColumnDown(i, i);
			if (index_of_first_non_zero_object != i)rowSwap(i, index_of_first_non_zero_object);

			for (int k = i - 1; k >=0 ; k--) {
				if (!(getValueAt(k, i)->equal(this->getNeutralElementWithRespectToAddition()))) {
					vector<NumberDataType*> multipliers = dynamic_cast<NumberDataType*>(this->getValueAt(i, i))
						->searchingForMultipliersForLeastCommonMultiple(dynamic_cast<NumberDataType*>(this->getValueAt(k, i)));
					if (multipliers.size() != 2)throw incorrect_input_data_exception("Wrong count of multipliers");
					if (!this->getValueAt(i, i)->multiplication(multipliers[0])
						->equal(this->getValueAt(k, i)->multiplication(multipliers[1])))throw number_exception("is not the smallest multiple of");
					tracking_array.push_back(multipliers[1]);
					vector<BasicDataType*> top_row = this->rowMultiplicationByConstant(i, multipliers[0]->inverseOfAddition());
					vector<BasicDataType*> top_answer_row = tracking_Matrix.rowMultiplicationByConstant(i, multipliers[0]->inverseOfAddition());

					vector<BasicDataType*> bottom_row = this->rowMultiplicationByConstant(k, multipliers[1]);
					vector<BasicDataType*> bottom_answer_row = tracking_Matrix.rowMultiplicationByConstant(k, multipliers[1]);

					this->rowReplacement(k,this->rowAddition(top_row, bottom_row));
					tracking_Matrix.rowReplacement(k,tracking_Matrix.rowAddition(top_answer_row, bottom_answer_row));

					this->freeUpVector(top_row);
					this->freeUpVector(top_answer_row);
					this->freeUpVector(bottom_row);
					this->freeUpVector(bottom_answer_row);
				}
			}
		}

		return tracking_array;
	}

	vector<BasicDataType*> Matrix::convertMatrixIntoUpperTriangularMatrix(Matrix& tracking_Matrix)
	{
		vector<BasicDataType*> tracking_array;
		for (int i = 0; i < this->getNumberOfColumns(); i++) {

			int index_of_first_non_zero_object = this->indexOfFirstNonZeroElemenInColumnUp(i, i);
			if (index_of_first_non_zero_object == -1)throw number_exception("there is not solution ");
			if (index_of_first_non_zero_object != i)rowSwap(i, index_of_first_non_zero_object);

			for (int k = i + 1; k < this->getNumberOfRows(); k++) {
				if (!(getValueAt(k, i)->equal(this->getNeutralElementWithRespectToAddition()))) {
					vector<NumberDataType*> multipliers = dynamic_cast<NumberDataType*>(this->getValueAt(i, i))
						->searchingForMultipliersForLeastCommonMultiple(dynamic_cast<NumberDataType*>(this->getValueAt(k, i)));
					if (multipliers.size() != 2)throw incorrect_input_data_exception("Wrong count of multipliers");
					if (!this->getValueAt(i, i)->multiplication(multipliers[0])
						->equal(this->getValueAt(k, i)->multiplication(multipliers[1])))throw number_exception("is not the smallest multiple of");
					tracking_array.push_back(multipliers[1]);

					vector<BasicDataType*> top_row = this->rowMultiplicationByConstant(i, multipliers[0]->inverseOfAddition());
					vector<BasicDataType*> top_answer_row = tracking_Matrix.rowMultiplicationByConstant(i, multipliers[0]->inverseOfAddition());

					vector<BasicDataType*> bottom_row = this->rowMultiplicationByConstant(k, multipliers[1]);
					vector<BasicDataType*> bottom_answer_row = tracking_Matrix.rowMultiplicationByConstant(k, multipliers[1]);

					this->rowReplacement(k,this->rowAddition(top_row, bottom_row));
					tracking_Matrix.rowReplacement(k,tracking_Matrix.rowAddition(top_answer_row, bottom_answer_row));

					this->freeUpVector(top_row);
					this->freeUpVector(top_answer_row);
					this->freeUpVector(bottom_row);
					this->freeUpVector(bottom_answer_row);
				}
			}
		}

		return tracking_array;
	}

	DWORD __stdcall Matrix::calculateValueAt(void* dataForCalculation)
	{
			
			processingData* globalData = (processingData*)dataForCalculation;
			Matrix* fMatrix = (Matrix*)(globalData->firstMatrix);
			Matrix* sMatrix = (Matrix*)(globalData->secondMatrix);
			Matrix* rMatrix = (Matrix*)(globalData->resultMatrix);
			vector<matrixCoordinates*>::iterator end = globalData->coords->end();
			for (vector<matrixCoordinates*>::iterator data = globalData->coords->begin(); data != end; data++) {
				double value = 0;

				for (unsigned int index = 0; index < fMatrix->getNumberOfColumns(); index++) {

					BasicDataType* firstMatrixValue = fMatrix->getValueAt((*data)->row, index);
					BasicDataType* secondMatrixValue = sMatrix->getValueAt(index, (*data)->column);
					BasicDataType* resultValue = firstMatrixValue->multiplication(secondMatrixValue);
					value += dynamic_cast<FloatDataType*>(resultValue)->getValue();
					delete resultValue;
					delete firstMatrixValue;
					delete secondMatrixValue;
					
				}

				rMatrix->changeValueAt((*data)->row, (*data)->column, new FloatDataType(value));
			}
			cout << "!" << globalData->coords->size()<<endl;
			delete globalData;
			
		return 0;

	}

	void __stdcall Matrix::calculateValueAtByUsingPromise(promise<processingData*>* promise)
	{
		future<processingData*> futureObject = promise->get_future();
		processingData* globalData = futureObject.get();
		Matrix* fMatrix = (Matrix*)(globalData->firstMatrix);
		Matrix* sMatrix = (Matrix*)(globalData->secondMatrix);
		Matrix* rMatrix = (Matrix*)(globalData->resultMatrix);
		vector<matrixCoordinates*>::iterator end = globalData->coords->end();
		for (vector<matrixCoordinates*>::iterator data = globalData->coords->begin(); data != end; data++) {
			double value = 0;

			for (unsigned int index = 0; index < fMatrix->getNumberOfColumns(); index++) {

				BasicDataType* firstMatrixValue = fMatrix->getValueAt((*data)->row, index);
				BasicDataType* secondMatrixValue = sMatrix->getValueAt(index, (*data)->column);
				BasicDataType* resultValue = firstMatrixValue->multiplication(secondMatrixValue);
				value += dynamic_cast<FloatDataType*>(resultValue)->getValue();
				delete resultValue;
				delete firstMatrixValue;
				delete secondMatrixValue;

			}

			rMatrix->changeValueAt((*data)->row, (*data)->column, new FloatDataType(value));
		}
		cout << "!" << globalData->coords->size() << endl;

	}

	Matrix Matrix::findUpperTriangularMatrix() {

		Matrix buffer(*this);
		Matrix tracking_Matrix(this->number_of_rows, 1, this->getCurrentTypeManager());
		buffer.convertMatrixIntoUpperTriangularMatrix(tracking_Matrix);
		return buffer;
	}

	Matrix Matrix::findUpperTriangularMatrix(Matrix& tracking_Matrix) {

		Matrix buffer(*this);
		buffer.convertMatrixIntoUpperTriangularMatrix(tracking_Matrix);
		return buffer;
	}

	Matrix Matrix::findUpperTriangularMatrix(vector<BasicDataType*>& tracking_array) {

		Matrix buffer(*this);
		Matrix tracking_Matrix(this->number_of_rows, 1, this->getCurrentTypeManager());
		tracking_array = buffer.convertMatrixIntoUpperTriangularMatrix(tracking_Matrix);
		return buffer;
	}

	Matrix Matrix::findUpperTriangularMatrix(Matrix& tracking_Matrix, vector<BasicDataType*>& tracking_array) {

		Matrix buffer(*this);
		tracking_array = buffer.convertMatrixIntoUpperTriangularMatrix(tracking_Matrix);
		return buffer;

	}

	bool Matrix::isEqual(Matrix Second_Matrix){

		if (this->number_of_columns != Second_Matrix.number_of_rows || this->number_of_columns != Second_Matrix.number_of_columns)return false;
		for (int row_index = 0; row_index < number_of_rows; row_index++) {
			for (int column_index = 0; column_index < number_of_columns; column_index++)
			{
				if (!((this->getValueAt(row_index, column_index))->equal(Second_Matrix.getValueAt(row_index, column_index))))return false;
			}
		}
		return false;
	}

	Matrix Matrix::mergeMatrices(Matrix Second_Matrix){

		vector<BasicDataType*>new_Matrix;
		if (this->number_of_rows != Second_Matrix.getNumberOfRows()) throw incorrect_input_data_exception("Wrong Matrix size");
		for (int row_index = 0; row_index < number_of_rows;row_index++) {

			for (int column_index = 0; column_index < this->number_of_columns; column_index++) {
				new_Matrix.push_back(this->getValueAt(row_index,column_index));
			}
				
			for (int column_index = 0; column_index < Second_Matrix.number_of_columns; number_of_columns++) {
				new_Matrix.push_back(Second_Matrix.getValueAt(row_index, column_index));
			}

		}

		Matrix result(this->number_of_rows, this->number_of_columns + Second_Matrix.getNumberOfColumns(), this->getCurrentTypeManager());
		return result;
	}

	Matrix Matrix::findLowerTriangularMatrix() {

		Matrix buffer(*this);
		Matrix tracking_Matrix(this->number_of_rows, 1, this->getCurrentTypeManager());
		buffer.convertMatrixIntoLowerTriangularMatrix(tracking_Matrix);
		return buffer;
	}

	Matrix Matrix::findLowerTriangularMatrix(Matrix& tracking_Matrix) {

		Matrix buffer(*this);
		buffer.convertMatrixIntoLowerTriangularMatrix(tracking_Matrix);
		return buffer;
	}

	Matrix Matrix::findLowerTriangularMatrix(vector<BasicDataType*>& tracking_array) {

		Matrix buffer(*this);
		Matrix tracking_Matrix(this->number_of_rows, 1, this->getCurrentTypeManager());
		tracking_array = buffer.convertMatrixIntoLowerTriangularMatrix(tracking_Matrix);
		return buffer;
	}

	Matrix Matrix::findLowerTriangularMatrix(Matrix& tracking_Matrix, vector<BasicDataType*>& tracking_array) {

		Matrix buffer(*this);
		tracking_array = buffer.convertMatrixIntoLowerTriangularMatrix(tracking_Matrix);
		return buffer;

	}



											////////////////////clone team/////////////////////



	Matrix* Matrix::newClone(){
		return new Matrix(this->getFullArrayOfValues(),this->getNumberOfRows(), this->getNumberOfColumns(), this->getCurrentTypeManager());
	}

	Matrix Matrix::clone(){
		return *this;
	}

	Matrix Matrix::clone(int count_of_rows, int count_of_columns){
		return clone(0, count_of_rows, 0, count_of_columns);
	}

	Matrix Matrix::clone(int opening_row, int end_row, int opening_column, int end_column){

		Matrix result_Matrix(end_row - opening_row, end_column - opening_column, this->getCurrentTypeManager()) ;
		result_Matrix.fillMatrix(this->getValues(), opening_row, end_row, opening_column, end_column);
		return result_Matrix;
		
	}

	Matrix Matrix::cloneWithoutRowAndColumn(int row, int column){
		if (this->number_of_rows == 1 || this->number_of_columns == 1)throw incorrect_input_data_exception("This Matrix is too small");
		Matrix result_Matrix(this->number_of_rows - 1, this->number_of_columns - 1, this->getCurrentTypeManager());
		vector <BasicDataType*> result_array;

		for (int row_index = 0; row_index < number_of_rows;row_index++) {
			if (row_index != row) {
				for (int column_index = 0; column_index < number_of_columns; column_index++) {
					if (column_index != column){
						result_array.push_back(this->getValueAt(row_index,column_index));
					}
				}
			}
		}

		result_Matrix.fillInByRows(result_array);
		return result_Matrix;
	}



													/////////////////////check/////////////////////



	bool Matrix::checkInaccuracy(vector<BasicDataType*> current, vector<BasicDataType*> previous,BasicDataType* inaccuracy){
		for (int i = 0; i < current.size(); i++) {
			if (((dynamic_cast<NumberDataType*>(current[i]->addition(dynamic_cast<NumberDataType*>(previous[i])->inverseOfAddition()))
				->absoluteValue())->multiplicationByReverseElement(dynamic_cast<NumberDataType*>(current[i]))->moreThan(inaccuracy))) return true;
		}
		return false;
	}

	void Matrix::checkSize(vector<vector<BasicDataType*>> new_values, int opening_row, int end_row, int opening_column, int end_column){

		if (opening_row < 0 || end_row < 0 || opening_column < 0 || end_column < 0 || 
			end_column - opening_column != this->number_of_columns || end_row - opening_row !=this->number_of_rows ||
			this->number_of_rows > new_values.size() || end_row > new_values.size()) throw incorrect_input_data_exception("wrong size of Matrix for copy");

		for (vector<vector<BasicDataType*>>::iterator iter = new_values.begin(); iter != new_values.end(); iter++) {
			if (this->number_of_columns > (*iter).size() || end_column > (*iter).size())throw incorrect_input_data_exception("wrong size of Matrix for copy");
		}
	}

	void Matrix::checkSize(vector<BasicDataType*> new_values){

		if (new_values.size() != this->size_of_Matrix || number_of_rows < 1 ||number_of_columns<1) throw number_exception("this array is too long");
	}


											////////////////////copy/////////////////////



	void Matrix::copy(const Matrix& other) {

		if(!this->empty())clear();
		definitionPart(other.number_of_rows, other.number_of_columns, other.type_manager->clone());
		this->fillMatrix(other.getValues(), number_of_rows, number_of_columns);

	}

	void Matrix::copy(const Matrix& other, int opening_row, int end_row, int opening_column, int end_column) {

		clear();
		definitionPart(other.number_of_rows, other.number_of_columns, other.type_manager->clone());
		
	}


										////////////////////initialization part/////////////////////



	void Matrix::memoryAllocation(int Number_of_rows, int Number_of_columns)
	{
		if (Number_of_rows < 0 || Number_of_columns < 0)throw incorrect_input_data_exception("wrong input size of Matrix");
		values.resize(Number_of_rows);
		for (int row = 0; row < Number_of_rows;row++) {
			values[row].resize(Number_of_columns);
		}

	}


	void Matrix::definitionPart(int rows, int columns, ObjectTypeManager* object_type){

		if (rows < 0 || columns < 0)throw incorrect_input_data_exception("wrong input size of Matrix");
		number_of_rows = rows;
		number_of_columns = columns;
		size_of_Matrix = rows * columns;
		type_manager = object_type;
		memoryAllocation(number_of_rows, number_of_columns);

	}

	void Matrix::nullInitialization() {

		for (int row_index = 0; row_index < number_of_rows; row_index++) {
			for(int column_index = 0; column_index<number_of_columns; column_index++) {
				this->setValueAt(row_index, column_index, this->getNeutralElementWithRespectToAddition());
			}
		}
	}

	void Matrix::initializationPocess(vector<vector<BasicDataType*>> new_values, int opening_row, int end_row, int opening_column, int end_column){
		checkSize(new_values, opening_row, end_row, opening_column, end_column);
		int row_index = 0;
		for (vector<vector<BasicDataType*>>::iterator new_Matrix_row_iter = (new_values.begin() + opening_row);
			new_Matrix_row_iter < (new_values.begin() + end_row) && row_index <this->number_of_rows && new_Matrix_row_iter < new_values.end();
			new_Matrix_row_iter++, row_index++) 
		{
			int column_index = 0;
			for (vector<BasicDataType*>::iterator new_Matrix_column_iter = ((*new_Matrix_row_iter).begin() + opening_column);
				new_Matrix_column_iter < ((*new_Matrix_row_iter).begin() + end_column) && column_index < number_of_columns && new_Matrix_column_iter < (*new_Matrix_row_iter).end();
				new_Matrix_column_iter++, column_index++)
			{
				this->setValueAt(row_index,column_index, (*new_Matrix_column_iter)->clone());
			}
		}
	}

	void Matrix::rowIitializationPocess(vector<BasicDataType*>  new_values){
		checkSize(new_values);
		int row_index = 0;
		for (vector<BasicDataType*>::iterator value = new_values.begin(); row_index < number_of_rows; row_index++) {
			for(int column_index = 0; value != new_values.end() && column_index < number_of_columns; value++, column_index++)
			{
				this->setValueAt(row_index,column_index,  (*value)->clone());
			}
		}
	}

	void Matrix::columnIitializationPocess(vector<BasicDataType*> new_values) {
		checkSize(new_values);
		vector<BasicDataType*>::iterator value = new_values.begin();
		for (int column_index = 0; column_index<number_of_columns; column_index++) {
			for (int row_index = 0; row_index < number_of_rows && value != new_values.end(); value++, row_index++)
			{
				this->setValueAt(row_index, column_index, (*value)->clone());
			}
		}
	}

											///////////////////destructors team/////////////////////


	void Matrix::freeUpMemoryInRow(int index_of_row) {
		if (index_of_row > this->getNumberOfRows()) throw incorrect_input_data_exception("wrong index of current row");
		freeUpVector(this->getRow(index_of_row));

	}

	void Matrix::deleteAllData(){

		for (int row = 0; row < number_of_rows;row++) {
			for(int column = 0; column < number_of_columns; column++) {
				delete this->values[row][column];
			}
		}
		for (int row = 0; row < number_of_rows; row++) {
			this->values[row].clear();
		}
		values.clear();
		delete this->type_manager;
	}

	void Matrix::freeUpVector(vector<BasicDataType*> current_vector){
		for (vector<BasicDataType*>::iterator array_iter = current_vector.begin(); array_iter != current_vector.end(); array_iter++) {
			delete* array_iter;
		}
	}

	void Matrix::clear() {
		deleteAllData();
	}

	Matrix::~Matrix(){
		clear();
	}


	