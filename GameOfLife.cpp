#include "GameOfLife.h"

struct MatrixSetup
{
	int stepsAmount;
	int matrixSize;

	//For pretty printing, consider if is needed, if threads will execute simulation concurrently and then print the result?
	bool isPretty;
};

struct SimulationSetup
{
	//What fields should be defined here?
	//Take them for the main function	
	int simulationInstances;

	//Redundant information, simulationInstances can be derived from 
	std::vector<MatrixSetup> instanceSetup;

	//Any non-redundant info, that is information that cant be derived form above defined vector?

};
//TODO: Do here interface for concurrenty running thread with independent simulations

//TODO: Also, the interface for communication with user can be implemented

//Maybe change the returned type of this function to "bool" for indicationg if the operation of setting up was ended succesfully
//Setting up the simulation will not take any arguments? And do not return anything?
void SetSimulation()
{
	//This idea has no big sence in my opinion, since the main function does the same
	//This should return some object, more structure, for holding parameters for simulation?
	//Maybe also checking will be done if the simulation is valid and proper set up can be made
}
