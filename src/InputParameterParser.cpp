#include "InputParameterParser.h"

InputParameterParser::InputParameterParser(const int& argc, const char** argv)
{
	//Omit first parameter, which is the name of compiled program
	for (int i = 1; i < argc; ++i)
	{
		tokens.push_back(std::string(argv[i]));
	}
}

//Return bool and the number of token that was used? This would prevent searching the parameter two times
//Or just call proper function when you know at compile time if you would need to extract the value from token
bool InputParameterParser::IsParameterProvided(const InputParameter& parameter) const
{
	//Search for parameter in created tokens
	for (auto& token: tokens)
	{
		//Cut off the token to the size of parameter
		//Compare cut of string to the parameter
		//Save the cut off part, it will be the value of parameter
		std::string cutOffToken = token.substr(0, parameter.parameter.size());
		if (cutOffToken == parameter.parameter)
		{
			//Here could be implementing getting value for specific parameter,
			//but this function checks only if the parameter was found
			return true;	
		}
		else
		{
			continue;
		}
	}
	return false;
}


int InputParameterParser::GetParameterIntegerValue(const InputParameter& parameter) const
{

	//Search for parameter in created tokens
	for (auto& token: tokens)
	{
		//Cut off the token to the size of parameter
		//Compare cut of string to the parameter
		//Save the cut off part, it will be the value of parameter
		std::string cutOffToken = token.substr(0, parameter.parameter.size());
		if (cutOffToken == parameter.parameter)
		{	
			//Get the value of passed parameter from saved token
			std::string valueOfParameter = token.substr(parameter.parameter.size(), std::string::npos);
			int numericParameterValue = std::stoi(valueOfParameter);
			return numericParameterValue;	
		}
		else
		{
			continue;
		}
	}
	//Indicate wrong behaviour with improper, special value of return value?
	//May be minus one, but remember to write handling in case of receiving such value
	return -1;
}

std::vector<int> InputParameterParser::GetParameterIntegerPackValue(const InputParameter& parameter) const
{
	std::vector<int> parameterPack;
	//Search for parameter in created tokens
	for (auto& token: tokens)
	{
		//Cut off the token to the size of parameter
		//Compare cut of string to the parameter
		//Save the cut off part, it will be the value of parameter
		std::string cutOffToken = token.substr(0, parameter.parameter.size());
		if (cutOffToken == parameter.parameter)
		{	
			std::string isolatedParameterPack = token.substr(parameter.parameter.size(), std::string::npos);
			//Find first of numeric char, then find first of space, push back the value to vector, repeat until npos
			int startPosition = 0;
			int endPosition;
			while (endPosition != std::string::npos)
			{
				startPosition = isolatedParameterPack.find_first_of("0123456789", startPosition);
				endPosition = isolatedParameterPack.find_first_of(",", startPosition);
				parameterPack.push_back(std::stoi(isolatedParameterPack.substr(startPosition, endPosition)));
				startPosition = endPosition;
			}
		}
		else
		{
			continue;
		}
	}
	//Indicate wrong behaviour with improper, special value of return value?
	//Size of vector can determine the correctness of loaded values, find that std::stoi returns if string cannot be converted to integer
	return parameterPack;
}
