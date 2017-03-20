#include "GameOfLife.h"
#include "SimMatrix.h"
#include <iostream>
#include <gtest/gtest.h>

//TODO: Completly rebuild main, better interface is a priority
//Interface for making simulation can be done in GameOfLife translation unit


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

	int matrixSize;
	bool isPrettySet = 0;
	int simSteps;

	std::cout << "Type matrix size" << std::endl;
	std::cin >> matrixSize;
	
	SimMatrix simMatrix(matrixSize, FillMode::RANDOM_FILL);
	
	std::cout << "How many steps to simulate?" << std::endl;
	std::cin >> simSteps;

	std::cout << "Type 1 for pretty printing" << std::endl;
	std::cin >> isPrettySet;
	
	//Move resize to constructor!
	//simMatrix.ResizeSimMatrix(matrixSize);
	
	//Would be not necessarly with constructor!
	//simMatrix.RandPopulateSimMatrix();
	
	if (isPrettySet)
	{
		simMatrix.PrintSimMatrixPretty();
	}
	else
	{		
		simMatrix.PrintSimMatrix();	
	}

	std::cout << std::endl;
	for (int i = 0; i < simSteps; ++i)
	{
		simMatrix.DoSimStep();
		
		if (isPrettySet)
		{
			simMatrix.PrintSimMatrixPretty();
		}
		else
		{		
			simMatrix.PrintSimMatrix();	
		}
		std::cout << std::endl;
	}
}
