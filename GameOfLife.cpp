#include "GameOfLife.h"
#include <iostream>
#include <random>

void PrintSimMatrix(sim_matrix& simMatrix)
{
	for (auto i = simMatrix.begin(); i != simMatrix.end(); ++i)
	{
		for (auto j = i->begin(); j != i->end(); ++j)
		{
			std::cout << *j << " ";
		}
	std::cout << std::endl;
	}
}

// Change this function to have an enum for populating with certain output
void RandPopulateSimMatrix(sim_matrix& simMatrix)
{
	for (auto i = simMatrix.begin(); i != simMatrix.end(); ++i)
	{		
		for (auto j = i->begin(); j != i->end(); ++j)
		{
			*j = rand()%2; 
		}
	}
}

void ResizeSimMatrix(sim_matrix& simMatrix, int size)
{
	simMatrix.resize(size);
	for (auto i = simMatrix.begin(); i != simMatrix.end(); ++i)
	{
		i->resize(size);
	}
}

// One could check for the status of cell in next step (that is bool - alive or dead)
// Or one could check how many adjescet cells are alive and return that value (it is more extensible, introduces more modularity)
int AdjacentCellsAlive(sim_matrix& simMatrix, int x, int y)
{
	// For now only squared matrix are supported
	int N = simMatrix.size();

	// Variable for counting alive adjescent cells
	int aliveAdjacent = 0;
	for (int i = x - 1; i <= x + 1; ++i)
	{
		for (int j = y - 1; j <= y + 1; ++j)
		{
			// Check if cell is not out of bound and analyzed cell
			if ((i >= 0 && i < N) && (j >= 0 && j < N) && !(x == i && y == i))
			{
				if (simMatrix[i][j] == true)
				{
					++aliveAdjacent;
				}		
			}
		}
	}
	return aliveAdjacent;
}

// How about modifying and checkint with passing an iterator for cell??
// Function decides if cell is alive or dead at next step

// This function should work on copy!
// Make it return the copy at the end 
// This is possible bad idea, because it will be copied each time SetCellStatus is invoked
void SetCellStatus(sim_matrix& simMatrix, int x, int y, int aliveAdjacent)
{
	if (simMatrix[x][y] == true && (aliveAdjacent == 2 || aliveAdjacent == 3))
	{
		simMatrix[x][y] = true;
	}
	else if (simMatrix[x][y] == false && aliveAdjacent == 3)
	{
		simMatrix[x][y] = true;
	}
	else
	{
		simMatrix[x][y] = false;
	}
}

// Invoke DoSimStep() and print simulation matrix
// There was interface unmatch, iterating over simMatrix was done using iterators
// Write those using iterators for performance gains

// THERE IS A NEED TO DO A COPY OF THE ARRAY AS WE ITERATE OVR IT AND CHANGE THE VALUES DURING ITERATION!!
// Make a copy of local simMatrix, work on it, assign it to the original passed by reference
void DoSimStep(sim_matrix& simMatrix)
{
	sim_matrix locSimMatrix = simMatrix;

	for (int i = 0; i < locSimMatrix.size(); ++i)
	{		
		for (int j = 0; j < locSimMatrix.at(i).size(); ++j)
		{
			SetCellStatus(locSimMatrix, i, j, AdjacentCellsAlive(simMatrix, i, j));
		}
	}
	simMatrix = locSimMatrix;
}
