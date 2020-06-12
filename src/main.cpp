#include "GameOfLife.h"
#include "SimMatrix.h"
#include "InputParameterParser.h"
#include <iostream>

//TODO: Completly rebuild main, better interface is a priority
//Interface for making simulation can be done in GameOfLife translation unit

//TODO:Write tests for covering whole project
//TODO:Make complex interface in "GameOfLife" with concurrently running :wthreads

int main(int argc, const char* argv[])
{
	SimulationOutput simOutput;
	InputParameterParser parserInstance(argc, argv);

	// Configure iostream global object cout for the simulation printing
	ConfigureCout();

	//TODO: simOutput is actually on the stack, investigate what optimizations could be made

	//TODO: Do better handling of initial start menu of program
	if (parserInstance.IsParameterProvided(parameters[HELP]))
	{
		PrintProgramHelp();
		//Handle this menu in a loop?
		return 0;
	}

	//TODO: General branching for use-the-parser and do-not-use-the-parser should be done here
	if (argc > 1)
	{
		simOutput = RunSimulation(SetSimulationFromParameters(parserInstance));

		if(parserInstance.IsParameterProvided(parameters[EXPLORE_RESULTS]))
		{
			ExploreSimulationResults(simOutput);
		}
	}
	else
	{
		simOutput = RunSimulation(SetSimulation());

		//Menu for exploring simulation results
		std::cout << "Do you want to explore simulation results? [Y/n]" << "\n";
		char exploreResults;
		std::cin >> exploreResults;

		if (exploreResults == 'Y')
		{
			ExploreSimulationResults(simOutput);
		}
	}
}
