#ifndef SIM_CELL_H
#define SIM_CELL_H

//Do the statistics count!
//And interface on SimMatrix side!

class SimCell
{
public:
	SimCell();
	void SetAlive();
	void SetDead();
	bool IsAlive() const;
	void SetCellState(bool state);
	int GetRespawnCounter();
	int GetKillCounter();
	void IncreaseMyLifeNeighbors();
	void ResetLifeNeighborsCounter();
{
protected:
private:
	bool isAlive;
	int killCounter;
	int respawnCounter;
	// in the end of analize phase this variable decidade compare with simulation rules to still live or dead
	// dead neighbours is 9 - life neighbours (not counting cell on edge - solution in progress)
	int myLiveNeighbors;
};

#endif
