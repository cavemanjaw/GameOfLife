#ifndef GAME_OF_LIFE_H
#define GAME_OF_LIFE_H

#include "SimCell.h"
#include "SimMatrix.h"
#include "InputParameterParser.h"
#include <memory>
#include <vector>

class SimMatrix;

//Interface for simulation and only printing the current value of simualtion matrix

//Make it a class, so there are possible actions to take for the output
struct SimulationOutput
{
	std::vector<SimMatrix> matrixSteps;
	//Also, some statistics can be gathered here
};

struct SimulationRulesSetup
{
	// For alive cell
	int minAliveAdjacentToKeepAlive;
	int maxAliveAdjacentToKeepAlive;

	// For dead cell
	int minAliveAdjacentToRespawn;
	int maxAliveAdjacentToRespawn;
};

//Currently used struct for simulation setup
struct MatrixSetup
{
	bool saveMatrixSteps;
	int stepsAmount;
	int matrixHeight;
	int matrixWidth;

	//For pretty printing, consider if is needed, if threads will execute simulation concurrently and then print the result?
	bool isPretty;

	//For choosing the option of showing simulation status for every step
	bool showSteps;

	//The number of hardware threads that simulation will be run on
	unsigned numberOfThreads;

	//Struct for custom simulation rules
	SimulationRulesSetup rules;
};

//For concurrently running multiple simulations, not supported right now
struct SimulationSetup
{
	//What fields should be defined here?
	//Take them for the main function	
	int simulationInstances;

	//Redundant information, simulationInstances can be derived from 
	std::vector<MatrixSetup> instanceSetup;

	//Any non-redundant info, that is information that cant be derived form above defined vector?
};

void ExploreSimulationResults(SimulationOutput);
MatrixSetup SetSimulation();
MatrixSetup SetSimulationFromParameters(const InputParameterParser& parserInstance);
SimulationOutput RunSimulation(MatrixSetup setup);

//This could be done by constructor when SimulationRulesSetup will be changed from struct to class
void SetSimulationRules(SimulationRulesSetup& rulesSetup);
void SetDefaultSimulationRules(SimulationRulesSetup& rulesSetup);
void PrintProgramHelp();
void ConfigureCout();

// This should be placed higher than in SimMatrix class
// Not sure, since right now it modifies only one object of SimMatrix type, pushing the simulation one step forward
// Although DoSimStep must be included in SimMatrix type since it modifies private member variable simMatrix


//TODO: Add const qualifiers for increasing security

//TODO: Encapsulate sim_matrix in a class with methods to get better interface and fields for statistics

//TODO: Create entire class of SimCell to obtain statistics and encaplsulate fields for better interface handling

#endif
