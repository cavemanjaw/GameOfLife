#include <gtest/gtest.h>
//#include "../src/GameOfLife.h"
//#include "../src/SimCell.h"
//#include "../src/SimMatrix.h"

int ReturnDoubled(int number)
{
	return number * 2;
}

//First argument is test suite, second is the name of test case
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
	ASSERT_EQ(simulationMatrixTest[0][0]->IsAlive(), false);
} 
*/

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
