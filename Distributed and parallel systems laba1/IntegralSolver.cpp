#include "IntegralSolver.h"


DWORD IntegralSolver::findVolume(void* params)
{

	dataForThread*  dataForCalculation = static_cast<dataForThread*>(params);
	double sumVolume = 0;
	vector<coordinates> calculationArea = dataForCalculation->coordinates;
	for (vector<coordinates>::iterator iter = calculationArea.begin(); iter != calculationArea.end(); iter++) {
		sumVolume += findOneParallelogramVolume(*iter, dataForCalculation->function);
	}
	dataForCalculation->globalMutex->lock();
	*dataForCalculation->globalVolume += sumVolume;
	cout << "LoG: " << "Thread counted " << sumVolume << "." << endl;
	cout << "LoG:" << "Thread has " << dataForCalculation->coordinates.size() << " values" << endl << endl;
	dataForCalculation->globalMutex->unlock();
	delete dataForCalculation;
	return 0;
}

coordinates IntegralSolver::goForward( coordinates workArea,double& currentX, double& currentY, double stepX, double stepY)
{
	coordinates answer;
	if (currentX + stepX <= workArea.xEnd) {

		answer.xBegin = currentX;
		answer.xEnd = currentX + stepX;
		answer.yBegin = currentY;
		answer.yEnd = currentY + stepY;
		currentX = currentX + stepX;

	}
	else {

		if (currentY + 2 * stepY <= workArea.yEnd) {

			answer.xBegin = workArea.xBegin;
			answer.xEnd = workArea.xBegin + stepX;
			answer.yBegin = currentY+stepY;
			answer.yEnd = currentY + 2 * stepY;
			currentX = workArea.xBegin + stepX;
			currentY = currentY + stepY;

		} 
		else {
			throw exception("There isn't way to go forward in this work area.");
		}
	}

	return answer;
}

bool IntegralSolver::isPossibleToGoForward(coordinates workArea, double currentX, double currentY, double stepX, double stepY)
{
	if (currentX + stepX <= workArea.xEnd) {
		return true;
	}
	else {

		if (currentY + 2 * stepY <= workArea.yEnd) {
			return true;
		}
		else {
			return false;
		}
	}
}

double IntegralSolver::findOneParallelogramVolume(coordinates coords, double(*function)(double currentX, double currentY))
{
	return function((coords.xBegin + coords.xEnd) / 2, (coords.yBegin + coords.yEnd) / 2) * (coords.xEnd - coords.xBegin) * (coords.yEnd - coords.yBegin);

}

IntegralSolver::IntegralSolver(double(*function)(double xCoordinate, double yCoordinate))
{
	this->function = function;
}

double IntegralSolver::solve(coordinates baseCoordinates, int numberOfThreads,int xFragmentation,int yFragmentation)
{
	globalVolume = 0;
	if (numberOfThreads < 1 || numberOfThreads > 63)throw new exception(("Incorrect number of threads. You want to  use " + to_string(numberOfThreads) + " threads.").data());
	if (xFragmentation < 1 || yFragmentation < 1) throw new exception("Incorrect fragmentation.");
	if (baseCoordinates.xBegin >= baseCoordinates.xEnd || baseCoordinates.yBegin >= baseCoordinates.yEnd) throw new exception("Wrong basic coordinates of calculation area.");

	vector<vector<coordinates>> arrayOfData;
	
	int lengthOfCoordinatesArray = ceil(double(xFragmentation * yFragmentation) / numberOfThreads);
	double xStep = (baseCoordinates.xEnd - baseCoordinates.xBegin) / xFragmentation;
	double yStep = (baseCoordinates.yEnd - baseCoordinates.yBegin) / yFragmentation;
	double currentX = baseCoordinates.xBegin;
	double currentY = baseCoordinates.yBegin;

	for (int thread = 0; thread < numberOfThreads; thread++) {

		vector<coordinates> arrayOfCoordinates;
		for (int element = 0; element < lengthOfCoordinatesArray && isPossibleToGoForward(baseCoordinates,currentX,currentY,xStep,yStep); element++) {

			coordinates currentStep = goForward(baseCoordinates, currentX, currentY, xStep, yStep);
			arrayOfCoordinates.push_back(currentStep);

		}
		arrayOfData.push_back(arrayOfCoordinates);

	}
	HANDLE* threadHandles = new HANDLE[numberOfThreads];
	for (int thread = 0; thread < numberOfThreads;thread++) {
		dataForThread* data = new dataForThread({this->globalMutex,&this->globalVolume,this->function,arrayOfData[thread]});
		threadHandles[thread] = CreateThread(NULL, 0, findVolume, (void*)data, NULL, NULL);
	}
	WaitForMultipleObjects(numberOfThreads, threadHandles, true, INFINITE);
	return globalVolume;
}

void IntegralSolver::changeCalculationFucntion(double(*newFunction)(double xCoordinates, double yCoordinates))
{
	this->function = newFunction; 
}

IntegralSolver::~IntegralSolver()
{
	delete this->globalMutex;
}


