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
protected:
private:
	bool isAlive;
	int killCounter;
	int respawnCounter;
};

#endif
