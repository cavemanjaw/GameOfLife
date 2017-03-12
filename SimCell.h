#ifndef SIM_CELL_H
#define SIM_CELL_H

class SimCell
{
public:
	SimCell();
	void SetAlive();
	void SetDead();
	bool IsAlive();
	void SetCellState(bool state);
protected:
private:
	bool isAlive;

	// For really long simulations ;)
	long long respawnCounter;
	long long killCounter;
};

#endif
