#include <iostream>
#include <random>
#include "SimMatrix.h"

// TODO: For the abstraction type represented by class SimCell there is a need for big interface change in almost all of this functions
// This could be done with constructors for random initailize values in matrix simulation grid, changes need to me made in SimCell class

void SimMatrix::PrintSimMatrix()
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

void SimMatrix::PrintSimMatrixPretty()
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

void SimMatrix::ResizeSimMatrix(int size)
{
	simMatrix.resize(size);
	for (auto i = simMatrix.begin(); i != simMatrix.end(); ++i)
	{
		i->resize(size);
	}
}

// TODO: Make a function IsInBound or something like this, for checking if the adjacent cells are in bound of matrix grid
// One could check for the status of cell in next step (that is bool - alive or dead)
// Or one could check how many adjescet cells are alive and return that value (it is more extensible, introduces more modularity)
int SimMatrix::AdjacentCellsAlive(int x, int y)
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
				if (simMatrix[i][j].IsAlive() == true)
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
void SimMatrix::SetCellStatus(int x, int y, int aliveAdjacent)
{
	if (simMatrix[x][y].IsAlive() == true && (aliveAdjacent == 2 || aliveAdjacent == 3))
	{
		simMatrix[x][y].SetAlive();
	}
	else if (simMatrix[x][y].IsAlive() == false && aliveAdjacent == 3)
	{
		simMatrix[x][y].SetAlive();
	}
	else
	{
		simMatrix[x][y].SetDead();
	}
}

//TODO: This function works, but is somehow bad ;)
// Invoke DoSimStep() and print simulation matrix
// There was interface unmatch, iterating over simMatrix was done using iterators
// Write those using iterators for performance gains

// THERE IS A NEED TO DO A COPY OF THE ARRAY AS WE ITERATE OVR IT AND CHANGE THE VALUES DURING ITERATION!!
// Make a copy of local simMatrix, work on it, assign it to the original passed by reference
void SimMatrix::DoSimStep()
{
	SimMatrix locSimMatrix = *this;

	for (int i = 0; i < locSimMatrix.simMatrix.size(); ++i)
	{		
		for (int j = 0; j < locSimMatrix.simMatrix.at(i).size(); ++j)
		{
			locSimMatrix.SetCellStatus(i, j, AdjacentCellsAlive(i, j));
		}
	}
	*this = locSimMatrix;
}
