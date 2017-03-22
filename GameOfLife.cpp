#include "GameOfLife.h"
#include <iostream>
#include "SimMatrix.h"

//TODO: Do here interface for concurrenty running thread with independent simulations

//TODO: Also, the interface for communication with user can be implemented

//TODO: THIS IS BIG TODO: REVERSE ENGINEERING
//Enable the possibility for showing every simulated step, investigate:
//REverse engineering possibility, that is calculating every step backward
//Storing only one instance of previous simMatrix is needed???
//The other way is to store every simulation step - will be a huge memory allocation

//Running simulation shouldnt always show the intermediate state of simulation matrix
void RunSimulation(MatrixSetup setup)
{
	SimMatrix simMatrix(setup.matrixSize, FillMode::RANDOM_FILL);

	std::cout << "Initial values of simulation matrix:" << std::endl;	
	if (setup.isPretty)
	{
		simMatrix.PrintSimMatrixPretty();
	}
	else
	{		
		simMatrix.PrintSimMatrix();	
	}

	std::cout << std::endl;
	
	for (int i = 0; i < setup.stepsAmount; ++i)
	{
		simMatrix.DoSimStep();

		std::cout << std::endl;
		std::cout << (float)i/(float)setup.stepsAmount*100 << "%";
		std::cout << std::endl;

		if (setup.showSteps)
		{
			if (setup.isPretty)
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
	std::cout << "Output values of simulation matrix:" << std::endl;	
	if (setup.isPretty)
	{
		simMatrix.PrintSimMatrixPretty();
	}
	else
	{		
		simMatrix.PrintSimMatrix();	
	}
}

//Maybe change the returned type of this function to "bool" for indicationg if the operation of setting up was ended succesfully
//Setting up the simulation will not take any arguments? And do not return anything?
MatrixSetup SetSimulation()
{
	MatrixSetup setup;
	//Master iostream library ;)
	std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
	std::cout << "///////        Welcome to GameOfLife simulator       //////////" << std::endl;
	std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
 
	std::cout << "How many steps do you want to simulate?" << std::endl;
	std::cout << "> ";	
	std::cin >> setup.stepsAmount;
	std::cout << "How big the simulation matrix should be?" << std::endl;
	std::cout << "> ";	
	std::cin >> setup.matrixSize;

	std::cout << "Do you want to print the status of matrix during simulation computation? [Y/n]" << std::endl;
	//Handle it more securly ;)	

	//Only one variable is needed?
	char sign;

	std::cout << "> ";	
	std::cin >> sign;
	
	if (sign == 'Y')
	{
		setup.showSteps = true; 
	}
	else
	{
		setup.showSteps = false;
	}
	
	//Handle it more securly ;)
	std::cout << "Do you want the matrix to be printed pretty? [Y/n]" << std::endl;
	std::cout << "> ";	
	std::cin >> sign;
	
	if (sign == 'Y')
	{
		setup.isPretty = true; 
	}
	else
	{
		setup.isPretty = false;
	}

	return setup;
	//This idea has no big sence in my opinion, since the main function does the same
	//This should return some object, more structure, for holding parameters for simulation?
	//Maybe also checking will be done if the simulation is valid and proper set up can be made
}
