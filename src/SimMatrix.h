#ifndef SIM_MATRIX_H
#define SIM_MATRIX_H

#include "SimCell.h"
#include "GameOfLife.h"
#include <vector>
#include <utility>

//TODO: Return a pair of ints for the coordinates?
//TODO: Which function to call inside constructor?
//TODO: Which of function make private?
//TODO: Consider, that if you make some of the functions private it would be necessary to modify DoSimStep() function as it creates a locals var and assignes it to *this
//TODO: Function for getting statistics of fields

struct SimulationRulesSetup;

//Move to GameOfLife.h?
enum FillMode
{
	RANDOM_FILL = 2,
	ALIVE_FILL = 1,
	DEAD_FILL = 0
};

class SimMatrix
{
public:
	SimMatrix(int matrixHeight, int matrixWidth, FillMode fillMode);

	std::pair<int, int> GetMaxRespawnCell();

	void PrintSimMatrix() const;

	void PrintSimMatrixPretty() const;

	void DoSimStep(SimulationRulesSetup rules);

	SimMatrix DoSimStepReturnMatrix(SimulationRulesSetup rules);

	//TODO: Move to private section if testing part is ready
	//Returns the amount of alive adjacent cells for given x and y coordinates
	int AdjacentCellsAlive(int x, int y) const;

protected:
private:
	std::vector<std::vector<SimCell>> simMatrix;

	void ResizeSimMatrix(int height, int width);

	void SetCellStatus(int x, int y, int aliveAdjacent, SimulationRulesSetup rules);

};

//TODO: Encapsulate sim_matrix in a class with methods to get better interface and fields for statistics

//TODO: Create entire class of SimCell to obtain statistics and encaplsulate fields for better interface handling

#endif
