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
