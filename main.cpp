#include "GameOfLife.h"
#include "SimMatrix.h"
#include <iostream>
#include <gtest/gtest.h>
#include <utility>

//TODO: Completly rebuild main, better interface is a priority
//Interface for making simulation can be done in GameOfLife translation unit

//TODO:Write tests for covering whole project
//TODO:Make complex interface in "GameOfLife" with concurrently running :wthreads

//TODO: Possible encapsulate whole interaction with user in one function

int ReturnDoubled(int number)
{
	return number * 2;
}

TEST(ReturnDoubled, ZeroTest)
{
	ASSERT_EQ(0, ReturnDoubled(0));
}

TEST(ReturnDoubled, NormalNumber)
{
	ASSERT_EQ(4, ReturnDoubled(2));
}

//Example testing of gTest, not working right now
/*
TEST(TestSuite, IsAlive)
{
	SimMatrix simulationMatrixTest(2, FillMode::RANDOM_FILL)
	ASSERT_EQ(simulationMatrix[0][0]->IsAlive(), false);
} 
*/

int main()
{
	RunSimulation(SetSimulation());

	//Memory of the simulation can done, one can push to the vector the previos value of simMatrix
	//What is the obsacle?
	//Right now it is modyfying 'this' pointer so it is not possible to get the previous vector value?	
	std::pair<int, int> tmp;
	
	//tmp = simMatrix.GetMaxRespawnCell();
	
	//std::cout << tmp.first << " ";
	
	//std::cout << tmp.second << std::endl;
	
	
	//There is no ostream overload for std::pair 
	//For getting the coordinates for max respawn cell
	//std::cout << simMatrix.GetMaxRespawnCell(); 
}
