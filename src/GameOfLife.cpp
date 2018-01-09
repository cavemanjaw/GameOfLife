#include "GameOfLife.h"
#include <iostream>
#include "SimMatrix.h"
#include <iomanip>
#include "InputParameterParser.h"

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

//TODO: Infinite loop printing the one choosen matrix step
void ExploreSimulationResults(SimulationOutput simResults)
{
	char escapeChar = 'Y';
	while (escapeChar != 'n')
	{
		std::cout << "Which simulation step matrix do you want to see?" << std::endl;
		int numberOfSimStep;
		std::cin >> numberOfSimStep;
		
		if (numberOfSimStep < simResults.matrixSteps.size() && numberOfSimStep >= 0)
		{
			std::cout << "Do you want the matrix to be pretty printed? [Y/n]" << std::endl;
			char printPretty;
			std::cin >> printPretty;
			
			if (printPretty == 'Y')
			{
				simResults.matrixSteps[numberOfSimStep].PrintSimMatrixPretty();
			}
			else
			{
				simResults.matrixSteps[numberOfSimStep].PrintSimMatrix();
			}
		
		}
		else
		{
			std::cout << "There is no such step in the results!" << std::endl;
		}
	std::cout << "Do you want to continue? [Y/n]" << std::endl;
	std::cin.clear();
	std::cin >> escapeChar;
	
	}
}

SimulationOutput RunSimulation(MatrixSetup setup)
{
	SimMatrix simMatrix(setup.matrixSize, FillMode::RANDOM_FILL);
	SimulationOutput simOutput;	
	
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
		
		//Could be done in some better way ;)
		if (setup.saveMatrixSteps)
		{
			simOutput.matrixSteps.push_back(simMatrix.DoSimStepReturnMatrix(setup.rules));
		}
		else
		{
		simMatrix.DoSimStep(setup.rules);
		}

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

	//Consider that this is not the end of simulation, since we are obtaining simOutput 
	std::cout << std::endl << "Simulation has ended..." << std::endl;
	return simOutput;
}

void SetSimulationRules(SimulationRulesSetup& rulesSetup)
{
	int number;

	std::cout << "How many alive adjacent should there minimally be to keep cell alive? [integer]" << std::endl;
	std::cout << "> ";
	std::cin >> number;
	rulesSetup.minAliveAdjacentToKeepAlive = number;

	std::cout << "How many alive adjacent should there maximally be to keep cell alive? [integer]" << std::endl;
	std::cout << "> ";
	std::cin >> number;
	rulesSetup.maxAliveAdjacentToKeepAlive = number;

	std::cout << "How many alive adjacent should there minimally be to respawn dead cell? [integer]" << std::endl;
	std::cout << "> ";
	std::cin >> number;
	rulesSetup.minAliveAdjacentToRespawn = number;

	std::cout << "How many alive adjacent should there minimally be to respawn dead cell? [integer]" << std::endl;
	std::cout << "> ";
	std::cin >> number;
	rulesSetup.maxAliveAdjacentToRespawn = number;
}

void SetDefaultSimulationRules(SimulationRulesSetup& rulesSetup)
{
	//For alive cell
	rulesSetup.minAliveAdjacentToKeepAlive = 2;
	rulesSetup.maxAliveAdjacentToKeepAlive = 3;

	// For dead cell
	rulesSetup.minAliveAdjacentToRespawn = 3;
	rulesSetup.maxAliveAdjacentToRespawn = 3;
}

MatrixSetup SetSimulationFromParameters(const InputParameterParser& parserInstance)
{
	MatrixSetup setup;

	//For ParameterCharacter::BOOL false will be returned if no arg is found
	setup.saveMatrixSteps = parserInstance.IsParameterProvided(parameters[STORE_RESULTS]);
	setup.isPretty = parserInstance.IsParameterProvided(parameters[PRINT_PRETTY]);
	setup.showSteps = parserInstance.IsParameterProvided(parameters[PRINT_STATUS]);

	//For ParameterCharacter::INTEGER -1 will be returned if no value provided
	setup.stepsAmount = parserInstance.GetParameterIntegerValue(parameters[STEPS]);
	setup.stepsAmount = (setup.stepsAmount != -1) ? setup.stepsAmount : 10;
	setup.matrixSize = parserInstance.GetParameterIntegerValue(parameters[SIZE]);
	setup.matrixSize = (setup.matrixSize != -1) ? setup.matrixSize : 10;

	std::vector<int> simulationRules = parserInstance.GetParameterIntegerPackValue(parameters[RULES]);

	//TODO: Ugly, any better solution?
	if (simulationRules.size() > 0)
	{
	setup.rules.minAliveAdjacentToKeepAlive = simulationRules.at(0);
	}
	else
	{
		setup.rules.minAliveAdjacentToKeepAlive = 2;
	}

	if (simulationRules.size() > 1)
	{
		setup.rules.maxAliveAdjacentToKeepAlive = simulationRules.at(1);
	}
	else
	{
		setup.rules.maxAliveAdjacentToKeepAlive = 3;
	}

	if (simulationRules.size() > 2)
	{
		setup.rules.minAliveAdjacentToRespawn = simulationRules.at(2);
	}
	else
	{
		setup.rules.minAliveAdjacentToRespawn = 3;
	}

	if (simulationRules.size() > 3)
	{
		setup.rules.maxAliveAdjacentToRespawn = simulationRules.at(3);
	}
	else
	{
		setup.rules.maxAliveAdjacentToRespawn = 3;
	}

	return setup;

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
	
	//For setting simulation rules
	std::cout << "Do you want to set custom simulation rules? [Y/n]" << std::endl;
	std::cout << "> ";
	std::cin >> sign;
	if (sign == 'Y')
	{
		SetSimulationRules(setup.rules);
	}
	else
	{
		SetDefaultSimulationRules(setup.rules);
	}
	std::cout << std::endl;

	return setup;
	//This idea has no big sence in my opinion, since the main function does the same
	//This should return some object, more structure, for holding parameters for simulation?
	//Maybe also checking will be done if the simulation is valid and proper set up can be made
}

void PrintProgramHelp()
{
	std::cout << "To write help function!";
}
