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

TEST_F(InputParameterParserTest, OnlyHeightParameterPassed)
{
	int argcMock = 2;
	const char* arg0 = "name_of_program";
	const char* arg1 = "--height=10";
	const char* argvMock[argcMock] = {arg0, arg1};

	InputParameterParser parserInstance(argcMock, argvMock);

	//Check return value of GetParameterIntegerValue()
	EXPECT_EQ(10, parserInstance.GetParameterIntegerValue(parameters[HEIGHT]));
}

TEST_F(InputParameterParserTest, OnlyWidthParameterPassed)
{
	int argcMock = 2;
	const char* arg0 = "name_of_program";
	const char* arg1 = "--width=20";
	const char* argvMock[argcMock] = {arg0, arg1};

	InputParameterParser parserInstance(argcMock, argvMock);

	//Check return value of GetParameterIntegerValue()
	EXPECT_EQ(20, parserInstance.GetParameterIntegerValue(parameters[WIDTH]));
}

TEST_F(InputParameterParserTest, HeightParameterAndFaultyParameterPassed)
{
	int argcMock = 3;

	const char* arg0 = "name_of_program";
	const char* arg1 = "--height=10";
	//Typo in "steps" parameter
	const char* arg2 = "--stes=100";

	const char* argvMock[argcMock] = {arg0, arg1, arg2};

	InputParameterParser parserInstance(argcMock, argvMock);

	//Check return value of GetParameterIntegerValue() for two passed parameters
	EXPECT_EQ(10, parserInstance.GetParameterIntegerValue(parameters[HEIGHT]));
	EXPECT_EQ(-1, parserInstance.GetParameterIntegerValue(parameters[STEPS]));
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
	EXPECT_EQ(false, parserInstance.IsParameterProvided(parameters[PRINT_PRETTY]));
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
		EXPECT_EQ(expectedPackElements[i], returnedParameterPack[i]);
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
		EXPECT_EQ(expectedPackElements[i], returnedParameterPack[i]);
	}
}


TEST_F(InputParameterParserTest, RulesWithoutAnythingAfterEqualSign)
{
	int argcMock = 2;

	const char* arg0 = "name_of_program";

	//Values given with additional space after '=' character
	const char* arg1 = "--rules=";

	const char* argvMock[argcMock] = {arg0, arg1};

	const int noOfExpectedPackElements = 0;

	InputParameterParser parserInstance(argcMock, argvMock);

	//Get return value of GetParameterIntegerValue() for two passed parameters
	auto returnedParameterPack = parserInstance.GetParameterIntegerPackValue(parameters[RULES]);

	//Check the size of returned parameter pack
	EXPECT_EQ(noOfExpectedPackElements, returnedParameterPack.size());
}


TEST_F(InputParameterParserTest, RulesWithOnlyOneNumber)
{
	int argcMock = 2;

	const char* arg0 = "name_of_program";

	//Values given with additional space after '=' character
	const char* arg1 = "--rules=6";

	const char* argvMock[argcMock] = {arg0, arg1};

	const int noOfExpectedPackElements = 1;
	const int expectedPackElements[noOfExpectedPackElements] = {6};

	InputParameterParser parserInstance(argcMock, argvMock);

	//Get return value of GetParameterIntegerValue() for two passed parameters
	auto returnedParameterPack = parserInstance.GetParameterIntegerPackValue(parameters[RULES]);

	//Check the size of returned parameter pack
	ASSERT_EQ(noOfExpectedPackElements, returnedParameterPack.size());

	//Check values of all parameters in parameter pack
	for (int i = 0; i < noOfExpectedPackElements; ++i)
	{
		EXPECT_EQ(expectedPackElements[i], returnedParameterPack[i]);
	}
}


TEST_F(InputParameterParserTest, RulesWithOnlyComma)
{
	int argcMock = 2;

	const char* arg0 = "name_of_program";

	//Values given with additional space after '=' character
	const char* arg1 = "--rules=,";

	const char* argvMock[argcMock] = {arg0, arg1};

	const int noOfExpectedPackElements = 0;

	InputParameterParser parserInstance(argcMock, argvMock);

	//Get return value of GetParameterIntegerValue() for two passed parameters
	auto returnedParameterPack = parserInstance.GetParameterIntegerPackValue(parameters[RULES]);

	//Check the size of returned parameter pack
	EXPECT_EQ(noOfExpectedPackElements, returnedParameterPack.size());
}

//int main(int argc, char** argv)
//{
//	::testing::InitGoogleTest(&argc, argv);
//	return RUN_ALL_TESTS();
//}

