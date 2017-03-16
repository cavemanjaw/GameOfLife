#include "SimCell.h"

SimCell::SimCell()
	:killCounter(0),
	 respawnCounter(0)
{}

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
	if (isAlive)
	{
		return true;
	}
	return false;
}

// Dangerous, because of not incrementing any of counters, call of this function is not captured by statistics
// On the other hand, we must initialize values and this is the situation in which we do not want to update statistics
// This could be done by constructor!!!!!!!
void SimCell::SetCellState(bool state)
{
	isAlive = state;
}
