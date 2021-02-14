#include <iostream>
#include <random>
#include "SimMatrix.h"
#include "GameOfLife.h"
#include <time.h>
#include <thread>
#include <limits>

using ThreadVec = std::vector<std::thread>;

//TODO: Consider which function can be "const" qualified
//TODO: For the abstraction type represented by class SimCell there is a need for big interface change in almost all of this functions

SimMatrix::SimMatrix(int matrixHeight, int matrixWidth, FillMode fillMode)
{
//Workaround right now, case for random filling uses member function
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
			// Argument implicit conversion from int to bool
			j->SetCellState(rand()%2); 
		}
	}
break;

case ALIVE_FILL:
	for (auto i = simMatrix.begin(); i != simMatrix.end(); ++i)
	{		
		for (auto j = i->begin(); j != i->end(); ++j)
		{
			j->SetCellState(true);
		}
	}
break;

case DEAD_FILL:
	//No need to do anything, default constructor of SimCell initializes cell state to false
break;
}
}

// Is this function ever called for gathering statistics?
std::pair<int, int> SimMatrix::GetMaxRespawnCell()
{
	// Initialize out variable to invalid value to signal no cell matching statistics
	std::pair<int, int> maxRespawnCellCoord
		(std::numeric_limits<int>::max(), std::numeric_limits<int>::max());

	// Initialze the loop counter
	int maxRespawn = 0;	

	for (auto i = simMatrix.begin(); i != simMatrix.end(); ++i)
	{
		for (auto j = i->begin(); j != i->end(); ++j)
		{
			//Can be done on iterators?
			if (j->GetRespawnCounter() > maxRespawn)
			{
				maxRespawn = j->GetRespawnCounter();

				// Getting the distance using iterator arithmetics
				maxRespawnCellCoord.first = (i - simMatrix.begin()); 
				maxRespawnCellCoord.second = (j - i->begin());
			}
			else if (j->GetRespawnCounter() == maxRespawn)
			{
				// Two cells have the same statistics
				// TODO: How to deal with that?
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
	std::cout << "\n";
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
	std::cout << "\n";
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
	int height = simMatrix.size();
	int width =simMatrix.at(0).size();

	// Variable for counting alive adjacent cells
	int aliveAdjacent = 0;
	for (int i = x - 1; i <= x + 1; ++i)
	{
		for (int j = y - 1; j <= y + 1; ++j)
		{
			// Check if cell is not out of bound and is not the cell we are checking itself
			if ((i >= 0 && i < height) && (j >= 0 && j < width) && !(x == i && y == j))
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
}

//TODO: This function works, but is somehow bad ;)
// Invoke DoSimStep() and print simulation matrix
// There was interface unmatch, iterating over simMatrix was done using iterators
// Write those using iterators for performance gains

// THERE IS A NEED TO DO A COPY OF THE ARRAY AS WE ITERATE OVR IT AND CHANGE THE VALUES DURING ITERATION!!
// Make a copy of local simMatrix, work on it, assign it to the original passed by reference
// Consider leaking resources

//Can this function be written for also returning new SimulationMatrix?
//TODO: Consider if returning something and not assigning returned variable is more costly than 'void' function

//Two of the functions can be modificated in such way to operate only on simMatrix field of SimMatrix class

void SimMatrix::DoSimStep(const MatrixSetup& setup)
{
	if (setup.numberOfThreads == 1)
	{
		SimMatrix locSimMatrix = *this;

		for (std::size_t i = 0; i < locSimMatrix.simMatrix.size(); ++i)
		{
			for (std::size_t j = 0; j < locSimMatrix.simMatrix.at(i).size(); ++j)
			{
				locSimMatrix.SetCellStatus(i, j, AdjacentCellsAlive(i, j), setup.rules);
			}
		}
		*this = locSimMatrix;
	}
	else
	{
		//TODO: Go through this flow :)

		//Create vector of threads and reserve the necessary space
		ThreadVec threads;
		threads.reserve(setup.numberOfThreads);

		// Is call to this vector constructor optimal and correct?
		std::vector<SimMatrix> localSimMatrix(setup.numberOfThreads, *this);

		//Calculate the division of work to be done by threads
		std::size_t numberOfRowsPerJob = this->simMatrix.size() / setup.numberOfThreads;
		//Remaining jobs due to mod != 0
		std::size_t remainingJobs = this->simMatrix.size() -
				setup.numberOfThreads * numberOfRowsPerJob;

		//Dispatch jobs, can it be optimized (without last if statement?)
		//Can be, just add remaining jobs to numberOfRows and then assign zero to the variable
		//Job dispatched variable?
		for (std::size_t i = 0, j = 0; i < setup.numberOfThreads; ++i, j +=numberOfRowsPerJob)
		{

			if (i != setup.numberOfThreads - 1)
			{
				threads.push_back(
						std::thread(&SimMatrix::DoSimStepThreadJob, this, std::ref(j),
								j + numberOfRowsPerJob, std::ref(localSimMatrix.at(i)), std::ref(setup)));

			}
			else //this is the last thread to dispatch include the remainingJobs rows...
			{
				threads.push_back(
						std::thread(&SimMatrix::DoSimStepThreadJob, this, std::ref(j),
								j + numberOfRowsPerJob + remainingJobs,
								std::ref(localSimMatrix.at(i)), std::ref(setup)));
			}
		}

		//Wait for the execution of all of the threads
		for (std::size_t i = 0; i < setup.numberOfThreads; ++i)
		{
			threads.at(i).join();
		}

		//Merge the inputs from threads
		for (std::size_t i = 0, j = 0; i < setup.numberOfThreads; ++i, j +=numberOfRowsPerJob)
		{
			if (i != setup.numberOfThreads - 1)
			{
				for (std::size_t k = j; k < numberOfRowsPerJob; ++k)
				{
					this->simMatrix.at(k) = localSimMatrix.at(i).simMatrix.at(k);
				}
			}
			else //work of the last thread is being done here
			{
				for (std::size_t k = j; k < numberOfRowsPerJob + remainingJobs; ++k)
				{
					this->simMatrix.at(k) = localSimMatrix.at(i).simMatrix.at(k);
				}
			}
		}
	}
}

void SimMatrix::DoSimStepThreadJob(std::size_t startRow,
		                           std::size_t endRow,
								   SimMatrix& locSimMatrix,
								   const MatrixSetup& setup)
{
	for (std::size_t i = startRow; i < endRow; ++i)
	{
		for (std::size_t j = 0; j < locSimMatrix.simMatrix.at(i).size(); ++j)
		{
			locSimMatrix.SetCellStatus(i, j, AdjacentCellsAlive(i, j), setup.rules);
		}
	}
}


SimMatrix SimMatrix::DoSimStepReturnMatrix(const MatrixSetup& setup)
{
	SimMatrix locSimMatrix = *this;

	for (std::size_t i = 0; i < locSimMatrix.simMatrix.size(); ++i)
	{		
		for (std::size_t j = 0; j < locSimMatrix.simMatrix.at(i).size(); ++j)
		{
			locSimMatrix.SetCellStatus(i, j, AdjacentCellsAlive(i, j), setup.rules);
		}
	}
	*this = locSimMatrix;
	return locSimMatrix;
}
