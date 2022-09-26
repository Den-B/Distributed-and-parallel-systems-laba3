#pragma once
#include <Windows.h>
#include <vector>
#include <mutex>
#include <math.h>
#include <string>
#include <iostream>
#include <future>

using namespace std; 


struct coordinates {

	double xBegin;
	double xEnd;
	double yBegin;
	double  yEnd;

};

struct dataForThread {

	mutex* globalMutex;
	double* globalVolume;
	double (*function)(double xCoordinate, double yCoordinate);
	vector<coordinates> coordinates;

};

class IntegralSolver
{
private:

	mutex* globalMutex = new mutex();
	double globalVolume = 0;
	double (*function)(double xCoordinate, double yCoordinate);

	static DWORD WINAPI findVolume(void* params);
	static double findVolumeByFuture(double (*function)(double xCoordinate, double yCoordinate),vector<coordinates>* vector);
	coordinates goForward(coordinates workArea, double& currentX, double& currentY, double stepX, double stepY);
	bool isPossibleToGoForward(coordinates workArea, double currentX, double currentY, double stepX, double stepY);
	static double findOneParallelogramVolume(coordinates coords, double(*function)(double currentX, double currentY));
		
public:

	IntegralSolver(double (*function)(double xCoordinate, double yCoordinate));
	double solve(coordinates  baseCoordinates, int numberOfThreads, int xFragmentation, int yFragmentation);
	double solveAsync(coordinates  baseCoordinates, int numberOfThreads, int xFragmentation, int yFragmentation);
	void changeCalculationFucntion(double(*newFunction)(double xCoordinates, double yCoordinates));
	~IntegralSolver();

};

