#ifndef GAME_OF_LIFE_H
#define GAME_OF_LIFE_H

#include "SimCell.h"
#include <vector>

//TODO: Encapsulate sim_matrix in a class with methods to get better interface and firlds for statisticd

//TODO: Create entire class of SimCell to obtain statistics and encaplsulate fields for better interface handling

typedef std::vector<std::vector<SimCell>> sim_matrix;

void PrintSimMatrix(sim_matrix& simMatrix);

void RandPopulateSimMatrix(sim_matrix& simMatrix);

void ResizeSimMatrix(sim_matrix& simMatrix, int size);

int AdjacentCellsAlive(sim_matrix& simMatrix, int x, int y);

void SetCellStatus(sim_matrix& simMatrix, int x, int y, int aliveAdjacent);

void DoSimStep(sim_matrix& simMatrix);

void PrintSimMatrixPretty(sim_matrix& simMatrix);

#endif
