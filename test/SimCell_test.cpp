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

TEST_F(SimCellTest, SetDeadTest)
{
	SimCell simCell;
	simCell.SetDead();
	ASSERT_EQ(false, simCell.IsAlive());
	ASSERT_EQ(0, simCell.GetKillCounter());
}

TEST_F(SimCellTest, SetDeadManyTimes)
{
	SimCell simCell;
	for (int i = 0; i < 10; ++i)
	{
		simCell.SetDead();
	}
	ASSERT_EQ(false, simCell.IsAlive());
	ASSERT_EQ(0, simCell.GetKillCounter());
}

TEST_F(SimCellTest, SetDeadAndAliveAlternately)
{
	SimCell simCell;

	//Set dead and alive alternately
	simCell.SetAlive();
	simCell.SetDead();
	simCell.SetAlive();
	simCell.SetDead();
	simCell.SetAlive();

	ASSERT_EQ(true, simCell.IsAlive());
	ASSERT_EQ(2, simCell.GetKillCounter());
	ASSERT_EQ(3, simCell.GetRespawnCounter());
}
