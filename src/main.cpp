#include "GameOfLife.h"
#include "SimMatrix.h"
#include <iostream>

//TODO: Completly rebuild main, better interface is a priority
//Interface for making simulation can be done in GameOfLife translation unit

//TODO:Write tests for covering whole project
//TODO:Make complex interface in "GameOfLife" with concurrently running :wthreads

//TODO: Possible encapsulate whole interaction with user in one function

int main()
{
	SimulationOutput simOutput;

	simOutput = RunSimulation(SetSimulation());

	std::cout << "Do you want to explore simulation results? [Y/n]" << std::endl;
	char exploreResults;
	std::cin >> exploreResults;

	if (exploreResults == 'Y')
	{
		ExploreSimulationResults(simOutput);	
	}

	//Memory of the simulation can done, one can push to the vector the previos value of simMatrix
	//What is the obsacle?
	//Right now it is modyfying 'this' pointer so it is not possible to get the previous vector value?	
	std::pair<int, int> tmp;
	
	//tmp = simMatrix.GetMaxRespawnCell();
	
	//std::cout << tmp.first << " ";
	
	//std::cout << tmp.second << std::endl;
	
	
	//There is no ostream overload for std::pair 
	//For getting the coordinates for max respawn cell
	//std::cout << simMatrix.GetMaxRespawnCell(); 
}
