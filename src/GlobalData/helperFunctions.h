#pragma once
#include <stdlib.h>
#include <vector>
#include <string>
#include "../ExternalData/Logger.h"

static bool outOfHundred(int odds)
{
	return  rand() % 101 <= odds;
}

//TODO: Improve randomness
//Random Number between 0 and Max
static int randomNumber(int max)
{
	return (rand() % max);
}

static std::vector<std::string> splitString(std::string input, char delimeter)
{
	std::vector<std::string> values;

	std::string nextValue;

	for (char c : input)
	{
		if (c != delimeter)
			nextValue += c;
		else
		{
			values.push_back(nextValue);
			nextValue = "";
		}
	}

	if (nextValue.size() > 0)
		values.push_back(nextValue);

	return values;
}