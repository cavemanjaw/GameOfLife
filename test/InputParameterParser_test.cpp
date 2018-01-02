#include <gtest/gtest.h>
#include "../src/InputParameterParser.h"
class InputParameterParserTest : public testing::Test
{
	virtual void SetUp() {}
	virtual void TearDown() {}

};

//Checking InputParameterParser::tokens is a internal state check and cannot
//(without strong justification also shouldn't) be done if
//this member variable is declared private. Although there are ways to get around this
//right now there are no such checks.

//TODO:Change indexing of parameters array variable to enums

TEST_F(InputParameterParserTest, OnlySizeParameterPassed)
{
	int argcMock = 2;
	const char* arg0 = "name_of_program";
	const char* arg1 = "--size=10";
	const char* argvMock[argcMock] = {arg0, arg1};

	InputParameterParser parserInstance(argcMock, argvMock);

	//Check return value of GetParameterIntegerValue()
	ASSERT_EQ(10, parserInstance.GetParameterIntegerValue(parameters[SIZE]));
}

TEST_F(InputParameterParserTest, SizeParameterAndFaultyParameterPassed)
{
	int argcMock = 3;

	const char* arg0 = "name_of_program";
	const char* arg1 = "--size=10";
	//Typo in "steps" parameter
	const char* arg2 = "--stes=100";

	const char* argvMock[argcMock] = {arg0, arg1, arg2};

	InputParameterParser parserInstance(argcMock, argvMock);

	//Check return value of GetParameterIntegerValue() for two passed parameters
	ASSERT_EQ(10, parserInstance.GetParameterIntegerValue(parameters[SIZE]));
	ASSERT_EQ(-1, parserInstance.GetParameterIntegerValue(parameters[STEPS]));
}

TEST_F(InputParameterParserTest, FaultyParameterPassed)
{
	int argcMock = 2;

	const char* arg0 = "name_of_program";

	//Typo in arg
	const char* arg1 = "--print-prety";

	const char* argvMock[argcMock] = {arg0, arg1};

	InputParameterParser parserInstance(argcMock, argvMock);

	//Check return value of GetParameterIntegerValue() for two passed parameters
	ASSERT_EQ(false, parserInstance.IsParameterProvided(parameters[PRINT_PRETTY]));
}

TEST_F(InputParameterParserTest, OnlyRulesParameterPassedFourValues)
{
	int argcMock = 2;

	const char* arg0 = "name_of_program";

	//Values written right after '=' character
	const char* arg1 = "--rules=10,2,440,5";

	const char* argvMock[argcMock] = {arg0, arg1};

	const int noOfExpectedPackElements = 4;
	const int expectedPackElements[noOfExpectedPackElements] = {10, 2, 440, 5};

	InputParameterParser parserInstance(argcMock, argvMock);

	//Get return value of GetParameterIntegerValue() for two passed parameters
	auto returnedParameterPack = parserInstance.GetParameterIntegerPackValue(parameters[RULES]);

	//Check the size of returned parameter pack
	ASSERT_EQ(noOfExpectedPackElements, returnedParameterPack.size());

	//Check values of all parameters in parameter pack
	for (int i = 0; i < noOfExpectedPackElements; ++i)
	{
		ASSERT_EQ(expectedPackElements[i], returnedParameterPack[i]);
	}
}

TEST_F(InputParameterParserTest, OnlyRulesParameterPassedTwoValues)
{
	int argcMock = 2;

	const char* arg0 = "name_of_program";

	//Values given with additional space after '=' character
	const char* arg1 = "--rules=6,7";

	const char* argvMock[argcMock] = {arg0, arg1};

	const int noOfExpectedPackElements = 2;
	const int expectedPackElements[noOfExpectedPackElements] = {6, 7};

	InputParameterParser parserInstance(argcMock, argvMock);

	//Get return value of GetParameterIntegerValue() for two passed parameters
	auto returnedParameterPack = parserInstance.GetParameterIntegerPackValue(parameters[RULES]);

	//Check the size of returned parameter pack
	ASSERT_EQ(noOfExpectedPackElements, returnedParameterPack.size());

	//Check values of all parameters in parameter pack
	for (int i = 0; i < noOfExpectedPackElements; ++i)
	{
		ASSERT_EQ(expectedPackElements[i], returnedParameterPack[i]);
	}
}

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

