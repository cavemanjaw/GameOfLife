#include "GameOfLife.h"
#include <iostream>
#include "SimMatrix.h"
#include <iomanip>

//TODO:Object or interface for handling rules for dying and respawning cells

//TODO: IT SEEMS TO BE THE MOST IMPORTANT TODO, the random values of sim grid are always the same for given input
//CHange it, seed the random, for exmaple with current time

//TODO: Do here interface for concurrenty running thread with independent simulations

//TODO: Also, the interface for communication with user can be implemented

//TODO: THIS IS BIG TODO: REVERSE ENGINEERING
//Enable the possibility for showing every simulated step, investigate:
//REverse engineering possibility, that is calculating every step backward
//Storing only one instance of previous simMatrix is needed???
//The other way is to store every simulation step - will be a huge memory allocation

//Running simulation shouldnt always show the intermediate state of simulation matrix
//Should this function return some struct for the output of siumulation?
SimulationOutput RunSimulation(MatrixSetup setup)
{
	SimMatrix simMatrix(setup.matrixSize, FillMode::RANDOM_FILL);
	
	std::cout << "Simulation starts..." << std::endl << std::endl;	

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

		//For only one "%" sign during printing simulation status
		std::cout << std::fixed;
		std::cout << std::setprecision(2);

		simMatrix.DoSimStep();
		std::cout << static_cast<float>(i)/static_cast<float>(setup.stepsAmount)*100 << "%\r";
		std::cout.flush();

		if (setup.showSteps)
		{
			std::cout << "Simulation step number: " << i + 1 << std::endl;

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
	
	std::cout << std::endl << "Simulation has ended..." << std::endl;
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
	
	std::cout << "Do you want to store every state of simulation matrix? [Y/n]" << std::endl;
	
	//Only one variable is needed?
	char sign;

	std::cout << "> ";	
	std::cin >> sign;

	if (sign == 'Y')
	{
		setup.saveMatrixSteps = true; 
	}
	else
	{
		setup.saveMatrixSteps = false;
	}

	std::cout << "Do you want to print the status of matrix during simulation computation? [Y/n]" << std::endl;
	//Handle it more securly ;)	

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
	
	std::cout << std::endl;

	return setup;
	//This idea has no big sence in my opinion, since the main function does the same
	//This should return some object, more structure, for holding parameters for simulation?
	//Maybe also checking will be done if the simulation is valid and proper set up can be made
}
