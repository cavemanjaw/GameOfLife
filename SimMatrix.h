#ifndef SIM_MATRIX_H
#define SIM_MATRIX_H

#include "SimCell.h"
#include <vector>

//TODO: Which function to call inside constructor?
//TODO: Which of function make private?
//TODO: Consider, that if you make some of the functions private it would be necessary to modify DoSimStep() function as it creates a locals var and assignes it to *this

class SimMatrix
{
public:
void PrintSimMatrix();

void RandPopulateSimMatrix();

// Only squared matrixes supported right now
void ResizeSimMatrix(int size);

//Returns the amount of alive adjacent cells for given x and y coordinates
int AdjacentCellsAlive(int x, int y);

void SetCellStatus(int x, int y, int aliveAdjacent);

void PrintSimMatrixPretty();

void DoSimStep();

protected:
private:
	std::vector<std::vector<SimCell>> simMatrix;
};
//TODO: Add const qualifiers for increasing security

//TODO: Encapsulate sim_matrix in a class with methods to get better interface and firlds for statisticd

//TODO: Create entire class of SimCell to obtain statistics and encaplsulate fields for better interface handling

//TODO: Make possible not squared matrixes to simulate




#endif
