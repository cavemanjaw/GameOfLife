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

TEST_F(SimCellTest, SetAliveTest)
{
	SimCell simCell;
	simCell.SetAlive();
	ASSERT_EQ(true, simCell.IsAlive());
	ASSERT_EQ(1, simCell.GetRespawnCounter());
}

TEST_F(SimCellTest, SettingAliveManyTimes)
{
	SimCell simCell;
	for (int i = 0; i < 10; ++i)
	{ 
		simCell.SetAlive();
	}
	ASSERT_EQ(true, simCell.IsAlive());
	ASSERT_EQ(1, simCell.GetRespawnCounter());
}
