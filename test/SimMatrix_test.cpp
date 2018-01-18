#include <gtest/gtest.h>
#include "../src/SimMatrix.h"

class SimMatrixTest : public testing::Test
{
	virtual void SetUp() {}
	virtual void TearDown() {}

};

TEST_F(SimMatrixTest, AdjacentAliveOnTheEdge)
{
	SimMatrix simMatrix(10, 10, FillMode::ALIVE_FILL);

	simMatrix.AdjacentCellsAlive(0,0);

	//On the corners
	EXPECT_EQ(3, simMatrix.AdjacentCellsAlive(0,0));
	EXPECT_EQ(3, simMatrix.AdjacentCellsAlive(9,0));
	EXPECT_EQ(3, simMatrix.AdjacentCellsAlive(0,9));
	EXPECT_EQ(3, simMatrix.AdjacentCellsAlive(9,9));

	//Adjacent to one of the edges
	EXPECT_EQ(5, simMatrix.AdjacentCellsAlive(0,5));
	EXPECT_EQ(5, simMatrix.AdjacentCellsAlive(5,0));
	EXPECT_EQ(5, simMatrix.AdjacentCellsAlive(5,9));
	EXPECT_EQ(5, simMatrix.AdjacentCellsAlive(9,5));
}
