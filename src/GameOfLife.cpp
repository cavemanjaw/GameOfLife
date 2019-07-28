#include "GameOfLife.h"
#include <iostream>
#include <thread>
#include "SimMatrix.h"
#include <iomanip>
#include "InputParameterParser.h"

//TODO:Object or interface for handling rules for dying and respawning cells

//TODO: Do here interface for concurrenty running thread with independent simulations

//TODO: THIS IS BIG TODO: REVERSE ENGINEERING
//Enable the possibility for showing every simulated step, investigate:
//REverse engineering possibility, that is calculating every step backward
//Storing only one instance of previous simMatrix is needed???
//The other way is to store every simulation step - will be a huge memory allocation

void ExploreSimulationResults(SimulationOutput simResults)
{
	char escapeChar = 'Y';

	//Loop for printing choosen matrix step
	while (escapeChar != 'n')
	{
		std::cout << "Which simulation step matrix do you want to see?" << std::endl;
		int numberOfSimStep;
		std::cin >> numberOfSimStep;
		
		if (numberOfSimStep < static_cast<int>(simResults.matrixSteps.size()) && numberOfSimStep >= 0)
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
	SimMatrix simMatrix(setup.matrixHeight, setup.matrixWidth, FillMode::RANDOM_FILL);
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
			simOutput.matrixSteps.push_back(simMatrix.DoSimStepReturnMatrix(setup));
		}
		else
		{
		simMatrix.DoSimStep(setup);
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

	//Set number of parameters value
	//TODO: Needs refactor, types are inconsistent, branches can be reduced
	int numberOfThreadsFromParameter = parserInstance.GetParameterIntegerValue(parameters[THREADS]);

	// If parameter was not provided
	if (numberOfThreadsFromParameter == -1)
	{
		//Parameter was not provided, run the simulation on one core
		setup.numberOfThreads = 1;
	}
	else
	{
		// Cap the maximum number of threads to HW supported number
		if (numberOfThreadsFromParameter > std::thread::hardware_concurrency())
		{
			setup.numberOfThreads = std::thread::hardware_concurrency();
		}
		else
		{
			//Set the value according to parameter that was provided
			setup.numberOfThreads = numberOfThreadsFromParameter;
		}
	}

	//For ParameterCharacter::INTEGER -1 will be returned if no value provided
	setup.stepsAmount = parserInstance.GetParameterIntegerValue(parameters[STEPS]);
	setup.stepsAmount = (setup.stepsAmount != -1) ? setup.stepsAmount : 10;
	setup.matrixHeight = parserInstance.GetParameterIntegerValue(parameters[HEIGHT]);
	setup.matrixHeight = (setup.matrixHeight != -1) ? setup.matrixHeight : 10;
	setup.matrixWidth = parserInstance.GetParameterIntegerValue(parameters[WIDTH]);
	setup.matrixWidth = (setup.matrixWidth != -1) ? setup.matrixWidth : 10;

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
	std::cout << "How big should the height of simulation matrix be?" << std::endl;
	std::cout << "> ";
	std::cin >> setup.matrixHeight;
	std::cout << "How big should the width of simulation matrix be?" << std::endl;
	std::cout << "> ";	
	std::cin >> setup.matrixWidth;
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

	//TODO: Quick fix, always use one thread in case of TUI setting-up parameters
	setup.numberOfThreads = 1;

	if (sign == 'Y')
	{
		SetSimulationRules(setup.rules);
	}
	else
	{
		SetDefaultSimulationRules(setup.rules);
	}
	std::cout << std::endl;

	//Return calculated sumulation setup, can be used to pass it to RunSimulation()
	return setup;
}


void PrintProgramHelp()
{
	std::cout << "usage: GameOfLife [--help] [--steps=<number>] [--height=<number>] [--width=<number>]\n"
			  << "                  [--print-pretty] [--store-results] [--print-status] [--explore-results]\n"
			  << "                  [--rules=[<number>,<number>,<number>,<number>]]\n"
			  << "                  [--threads=<number>]\n";
}
