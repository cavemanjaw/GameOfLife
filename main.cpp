#include "GameOfLife.h"
#include <iostream>

int main()
{
	sim_matrix simMatrix;
	int matrixSize;
	bool isPrettySet = 0;


	std::cout << "Type matrix size" << std::endl;
	std::cin >> matrixSize;

	std::cout << "Type 1 for pretty printing" << std::endl;
	std::cin >> isPrettySet;

	ResizeSimMatrix(simMatrix, matrixSize);

	RandPopulateSimMatrix(simMatrix);
	
	if (isPrettySet)
	{
		PrintSimMatrixPretty(simMatrix);
	}
	else
	{		
		PrintSimMatrix(simMatrix);	
	}

	std::cout << std::endl;
	for (int i = 0; i < 10; ++i)
	{
		DoSimStep(simMatrix);
		
		if (isPrettySet)
		{
			PrintSimMatrixPretty(simMatrix);
		}
		else
		{		
			PrintSimMatrix(simMatrix);	
		}
		std::cout << std::endl;
	}
}
