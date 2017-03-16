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
protected:
private:
	bool isAlive;

	// For really long simulations ;)
	long long respawnCounter;
	long long killCounter;
};

#endif
