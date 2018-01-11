#include <iostream>
#include <random>
#include "SimMatrix.h"
#include "GameOfLife.h"
#include <time.h>

//TODO: Consider which function can be "const" qualified
//TODO: For the abstraction type represented by class SimCell there is a need for big interface change in almost all of this functions

SimMatrix::SimMatrix(int matrixHeight, int matrixWidth, FillMode fillMode)
{
//Workaroung right now, case for random filling uses member function
//Consider if checking inside two loops (if that is on top of assignment is faster than if before two loops

//First of all, resize the matrix
ResizeSimMatrix(matrixHeight, matrixWidth);

switch(fillMode)
{
case RANDOM_FILL:
	srand(time(NULL));
	for (auto i = simMatrix.begin(); i != simMatrix.end(); ++i)
	{		
		for (auto j = i->begin(); j != i->end(); ++j)
		{
			j->SetCellState(rand()%2); 
		}
	}
break;

case ALIVE_FILL:
	for (auto i = simMatrix.begin(); i != simMatrix.end(); ++i)
	{		
		for (auto j = i->begin(); j != i->end(); ++j)
		{
			j->SetAlive(); 
		}
	}
break;

case DEAD_FILL:
	for (auto i = simMatrix.begin(); i != simMatrix.end(); ++i)
	{		
		for (auto j = i->begin(); j != i->end(); ++j)
		{
			j->SetDead(); 
		}
	}
break;
}
}

std::pair<int, int> SimMatrix::GetMaxRespawnCell()
{
	std::pair<int, int> maxRespawnCellCoord(0, 0);
	int maxRespawn = 0;	

	for (auto i = simMatrix.begin(); i != simMatrix.end(); ++i)
	{
		for (auto j = i->begin(); j != i->end(); ++j)
		{
			//Can be done on iterators?
			if (j->GetRespawnCounter() > maxRespawn)
			{
				//Recent bug, not assigning value to max counter
				maxRespawn = j->GetRespawnCounter();
				maxRespawnCellCoord.first = (i - simMatrix.begin()); 
				maxRespawnCellCoord.second = (j - i->begin());
			}
		}
	}
	return maxRespawnCellCoord;
}

void SimMatrix::PrintSimMatrix() const
{
	for (auto i = simMatrix.begin(); i != simMatrix.end(); ++i)
	{
		for (auto j = i->begin(); j != i->end(); ++j)
		{
			std::cout << j->IsAlive() << " ";
		}
	std::cout << std::endl;
	}
}

void SimMatrix::PrintSimMatrixPretty() const
{ 
	for (auto i = simMatrix.begin(); i != simMatrix.end(); ++i)
	{
		for (auto j = i->begin(); j != i->end(); ++j)
		{
			if (j->IsAlive())
			{
				std::cout << "*";
			}
			else
			{
				std::cout << "-";
			}
		}
	std::cout << std::endl;
	}
}

// Change this function to have an enum for populating with certain output
void SimMatrix::RandPopulateSimMatrix()
{
	for (auto i = simMatrix.begin(); i != simMatrix.end(); ++i)
	{		
		for (auto j = i->begin(); j != i->end(); ++j)
		{
			j->SetCellState(rand()%2); 
		}
	}
}

void SimMatrix::ResizeSimMatrix(int height, int width)
{
	simMatrix.resize(height);
	for (auto i = simMatrix.begin(); i != simMatrix.end(); ++i)
	{
		i->resize(width);
	}
}

// TODO: Make a function IsInBound or something like this, for checking if the adjacent cells are in bound of matrix grid
// One could check for the status of cell in next step (that is bool - alive or dead)
// Or one could check how many adjescet cells are alive and return that value (it is more extensible, introduces more modularity)
int SimMatrix::AdjacentCellsAlive(int x, int y) const
{
	// For now only squared matrix are supported
	int N = simMatrix.size();

	// Variable for counting alive adjacent cells
	int aliveAdjacent = 0;
	for (int i = x - 1; i <= x + 1; ++i)
	{
		for (int j = y - 1; j <= y + 1; ++j)
		{
			// Check if cell is not out of bound and is not the cell we are checking itself
			if ((i >= 0 && i < N) && (j >= 0 && j < N) && !(x == i && y == i))
			{
				if (simMatrix[i][j].IsAlive() == true)
				{
					++aliveAdjacent;
				}		
			}
		}
	}
	return aliveAdjacent;
}

// How about modifying and checking with passing an iterator for cell??
// Function decides if cell is alive or dead at next step

// This function should work on copy!
// Make it return the copy at the end 
// This is possible bad idea, because it will be copied each time SetCellStatus is invoked
// Pass SimulationRulesSetup here
void SimMatrix::SetCellStatus(int x, int y, int aliveAdjacent, SimulationRulesSetup rules)
{
	bool isCellAlive = simMatrix[x][y].IsAlive();
	//TODO: Analyze this part, it could be done better :)
	//Check the interval
	if (isCellAlive &&
			(aliveAdjacent >= rules.minAliveAdjacentToKeepAlive && aliveAdjacent <= rules.maxAliveAdjacentToKeepAlive))
	{
		//simMatrix[x][y].SetAlive();
		//Do nothing, cell is already alive and should be kept in this state
	}
	else if (isCellAlive &&
			(aliveAdjacent < rules.minAliveAdjacentToKeepAlive || aliveAdjacent > rules.maxAliveAdjacentToKeepAlive))
	{
		simMatrix[x][y].SetDead();
	}
	else if (!isCellAlive &&
			(aliveAdjacent >= rules.minAliveAdjacentToRespawn && aliveAdjacent <= rules.maxAliveAdjacentToRespawn))
	{
		simMatrix[x][y].SetAlive();
	}
	else if (!isCellAlive &&
			(aliveAdjacent < rules.minAliveAdjacentToRespawn || aliveAdjacent > rules.maxAliveAdjacentToRespawn))
	{
		//simMatrix[x][y].SetDead();
		//Do nothing cell is dead and so it should be
	}
	else
	{
		//Should not happen
		//TODO:Add assert
	}
}

//TODO: This function works, but is somehow bad ;)
// Invoke DoSimStep() and print simulation matrix
// There was interface unmatch, iterating over simMatrix was done using iterators
// Write those using iterators for performance gains

// THERE IS A NEED TO DO A COPY OF THE ARRAY AS WE ITERATE OVR IT AND CHANGE THE VALUES DURING ITERATION!!
// Make a copy of local simMatrix, work on it, assign it to the original passed by reference
// Consider leaking resources

//Can this function be written for also returning new SimulationMatrix?
//TODO: Consider if returning something and not assignint returned variable is more costly than 'void' function

//Two of the functions can be modificated in such way to operate only on simMatrix field of SimMatrix class

void SimMatrix::DoSimStep(SimulationRulesSetup rules)
{
	SimMatrix locSimMatrix = *this;

	for (int i = 0; i < locSimMatrix.simMatrix.size(); ++i)
	{		
		for (int j = 0; j < locSimMatrix.simMatrix.at(i).size(); ++j)
		{
			locSimMatrix.SetCellStatus(i, j, AdjacentCellsAlive(i, j), rules);
		}
	}
	*this = locSimMatrix;
}


SimMatrix SimMatrix::DoSimStepReturnMatrix(SimulationRulesSetup rules)
{
	SimMatrix locSimMatrix = *this;

	for (int i = 0; i < locSimMatrix.simMatrix.size(); ++i)
	{		
		for (int j = 0; j < locSimMatrix.simMatrix.at(i).size(); ++j)
		{
			locSimMatrix.SetCellStatus(i, j, AdjacentCellsAlive(i, j), rules);
		}
	}
	*this = locSimMatrix;
	return locSimMatrix;
}
