#include "GameOfLife.h"
#include <iostream>

int main()
{
	sim_matrix simMatrix;
	int matrixSize;
	std::cout << "Type matrix size" << std::endl;
	std::cin >> matrixSize;

	ResizeSimMatrix(simMatrix, matrixSize);

	RandPopulateSimMatrix(simMatrix);
	PrintSimMatrix(simMatrix);	
	std::cout << std::endl;
	for (int i = 0; i < 10; ++i)
	{
		DoSimStep(simMatrix);
		PrintSimMatrix(simMatrix);
		std::cout << std::endl;
	}
}
