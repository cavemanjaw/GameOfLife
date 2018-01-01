#ifndef INPUT_PARAMETER_PARSER
#define INPUT_PARAMETER_PARSER

#include <string>
#include <vector>
#include <array>

#define NUMBER_OF_PARAMETERS 6

enum ParameterType
{
	BOOL,
	INTEGER,
	INTEGER_PACK
};

struct InputParameter
{
	std::string parameter;
	ParameterType type;
};

//Parse first parameter and apply
//Strings cannot be constexpr? They do allocation, so we won't be able to calculate the position of '=' character in compile time
const std::array<InputParameter, NUMBER_OF_PARAMETERS> parameters =
	{{
			{"--steps=", INTEGER},
			{"--size=", INTEGER},
			{"--print-pretty", BOOL},
			{"--store-results", BOOL},
			{"--print-status", BOOL},
			{"--rules=", INTEGER_PACK}
	}};

class InputParameterParser
{
public:
	InputParameterParser(const int& argc, const char** argv);
	bool IsParameterProvided(const InputParameter& parameter);
	int GetParameterIntegerValue(const InputParameter& parameter);
	std::vector<int> GetParameterIntegerPackValue(const InputParameter& parameter);
protected:
private:
	std::vector<std::string> tokens;
};

//Wrap this into a class or something
//void ParseParameters( //What arguments, where should it be declared and called?

#endif
