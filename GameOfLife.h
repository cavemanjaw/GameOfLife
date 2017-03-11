#ifndef GAME_OF_LIFE_H
#define GAME_OF_LIFE_H

#include <vector>

typedef std::vector<std::vector<bool>> sim_matrix;

void PrintSimMatrix(sim_matrix& simMatrix);

void RandPopulateSimMatrix(sim_matrix& simMatrix);

void ResizeSimMatrix(sim_matrix& simMatrix, int size);

int AdjacentCellsAlive(sim_matrix& simMatrix, int x, int y);

void SetCellStatus(sim_matrix& simMatrix, int x, int y, int aliveAdjacent);

void DoSimStep(sim_matrix& simMatrix);

#endif
