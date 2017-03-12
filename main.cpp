#include "GameOfLife.h"
#include "SimMatrix.h"
#include <iostream>

//TODO: Completly rebuild main, better interface is a priority

int main()
{
	SimMatrix simMatrix;
	int matrixSize;
	bool isPrettySet = 0;
	int simSteps;

	std::cout << "Type matrix size" << std::endl;
	std::cin >> matrixSize;
	
	std::cout << "How many steps to simulate?" << std::endl;
	std::cin >> simSteps;

	std::cout << "Type 1 for pretty printing" << std::endl;
	std::cin >> isPrettySet;

	simMatrix.ResizeSimMatrix(matrixSize);

	simMatrix.RandPopulateSimMatrix();
	
	if (isPrettySet)
	{
		simMatrix.PrintSimMatrixPretty();
	}
	else
	{		
		simMatrix.PrintSimMatrix();	
	}

	std::cout << std::endl;
	for (int i = 0; i < simSteps; ++i)
	{
		simMatrix.DoSimStep();
		
		if (isPrettySet)
		{
			simMatrix.PrintSimMatrixPretty();
		}
		else
		{		
			simMatrix.PrintSimMatrix();	
		}
		std::cout << std::endl;
	}
}
