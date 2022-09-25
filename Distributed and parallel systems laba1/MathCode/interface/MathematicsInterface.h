#pragma once
#include "BasicConsoleInterface.h"
#include "../data_types/FloatDataType.h"
#include "../math/Matrix/Matrix.h"
#include "../../IntegralSolver.h"
#include <fstream>
#include <math.h>
using namespace std;

class MathematicsInterface :
    public BasicConsoleInterface
{

public:

    void displayAnswerWithIaccuracy(vector < BasicDataType*> array_of_elements,string name_of_elements);
    void displayMatrix(Matrix my_Matrix, string operation, int place_on_one_number);
    void displayNumberMatrix(Matrix my_Matrix, string operation, int place_on_one_number);
    void displayMatrixFile(Matrix my_Matrix, string operation, int place_on_one_number, string fileName);
    MathematicsInterface(string program_name, string record_file_name);
    vector<FloatDataType>findIaccuracy(vector<FloatDataType> set);
    Matrix inputMatrix();
    Matrix inputMatrixRandom();
    void fixChangesInFileCons(string fileName,string information);
    void taskSelection();

};

