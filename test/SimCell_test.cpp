#include <gtest/gtest.h>
#include "../src/SimCell.h"
class SimCellTest : public testing::Test
{	
	virtual void SetUp() {}
	virtual void TearDown() {}

};
TEST_F(SimCellTest, KillAndRespawnCounterInitialStatus)
{
	SimCell simCell;
	ASSERT_EQ(0, simCell.GetRespawnCounter());
	ASSERT_EQ(0, simCell.GetKillCounter());
}




