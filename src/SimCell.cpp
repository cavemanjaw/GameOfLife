#include "SimCell.h"

SimCell::SimCell()
	:isAlive(false),
	 killCounter(0),
	 respawnCounter(0)
{}

//Mismatch between return type and the type of field variable
int SimCell::GetRespawnCounter()
{
	return respawnCounter;
}

int SimCell::GetKillCounter()
{
	return killCounter;
}

void SimCell::SetAlive()
{
	// If it already alive do not do anything
	if (!isAlive)
	{	
		isAlive = true;
		++respawnCounter;
	}
}

void SimCell::SetDead()
{
	// If the cell is dead do not do anything
	if (isAlive)
	{
		isAlive = false;
		++killCounter;
	}
}

bool SimCell::IsAlive() const
{
	return isAlive;
}

// Dangerous, because of not incrementing any of counters, call of this function is not captured by statistics
// On the other hand, we must initialize values and this is the situation in which we do not want to update statistics
// Changing state should be done by calling interface for raspawning and killing cells
void SimCell::SetCellState(bool state)
{
	isAlive = state;
}
