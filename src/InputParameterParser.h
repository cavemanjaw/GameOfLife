#ifndef INPUT_PARAMETER_PARSER
#define INPUT_PARAMETER_PARSER

#include <string>
#include <vector>
#include <array>
#include <assert.h>

#define NUMBER_OF_PARAMETERS 9

//There is not use of this enum right now
enum ParameterCharacter
{
	BOOL,
	INTEGER,
	INTEGER_PACK
};

struct InputParameter
{
	std::string parameter;
	ParameterCharacter paramCharacter;
};

//Note that the parameters must be in the same order as the elements in parameters std::array
enum ParameterType
{
	STEPS = 0,
	HEIGHT = 1,
	WIDTH = 2,
	PRINT_PRETTY = 3,
	STORE_RESULTS = 4,
	PRINT_STATUS = 5,
	RULES = 6,
	EXPLORE_RESULTS = 7,
	HELP = 8,
	NO_OF_PARAMETER_TYPES = 9
};

//Parse first parameter and apply
//Strings cannot be constexpr? They do allocation, so we won't be able to calculate the position of
//'=' character in compile time
const std::array<InputParameter, NUMBER_OF_PARAMETERS> parameters =
	{{
			{"--steps=", INTEGER},
			{"--height=", INTEGER},
			{"--width=", INTEGER},
			{"--print-pretty", BOOL},
			{"--store-results", BOOL},
			{"--print-status", BOOL},
			{"--rules=", INTEGER_PACK},
			{"--explore-results", BOOL},
			{"--help", BOOL}
	}};

static_assert(NUMBER_OF_PARAMETERS == NO_OF_PARAMETER_TYPES,
		      //&& NUMBER_OF_PARAMETERS == parameters.size(), //TODO: parameters cannot be constexpr, so we cannot check this
			  //at the compile time, parameters hold std::string which cannot be constexpr
			  "Number of parameters in parameters variable have to match ParameterType enum items!");

class InputParameterParser
{
public:
	//Call this functions with parameters[ParameterType]
	InputParameterParser(const int& argc, const char** argv);
	bool IsParameterProvided(const InputParameter& parameter) const;
	int GetParameterIntegerValue(const InputParameter& parameter) const;
	std::vector<int> GetParameterIntegerPackValue(const InputParameter& parameter) const;
protected:
private:
	std::vector<std::string> tokens;
};

//Wrap this into a class or something
//void ParseParameters( //What arguments, where should it be declared and called?

#endif
