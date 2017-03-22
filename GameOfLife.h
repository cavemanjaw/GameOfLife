#ifndef GAME_OF_LIFE_H
#define GAME_OF_LIFE_H

#include "SimCell.h"
#include "SimMatrix.h"

//Now used struct for simulation setup
struct MatrixSetup
{
	int stepsAmount;
	int matrixSize;

	//For pretty printing, consider if is needed, if threads will execute simulation concurrently and then print the result?
	bool isPretty;
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

MatrixSetup SetSimulation();
void RunSimulation(MatrixSetup setup);

// This should be placed higher than in SimMatrix class
// Not sure, since right now it modifies only one object of SimMatrix type, pushing the simulation one step forward
// Although DoSimStep must be included in SimMatrix type since it modifies private member variable simMatrix

// Useless for now
//void DoSimStep(SimMatrix& simMatrix);

//TODO: Add const qualifiers for increasing security

//TODO: Encapsulate sim_matrix in a class with methods to get better interface and firlds for statisticd

//TODO: Create entire class of SimCell to obtain statistics and encaplsulate fields for better interface handling

#endif
