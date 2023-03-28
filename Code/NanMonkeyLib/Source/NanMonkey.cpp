#include "pch.h"
#include "NanMonkey/NanMonkey.h"
#include <assert.h>

void NanMonkey::NanAssert(const bool condition, const char* message)
{
	if (true == condition)
	{
		return;
	}
	std::cout << message << std::endl;
	assert(condition);
}

const float NanMonkey::NanClamp(const float value, const float low, const float high)
{
	if (value < low)
	{
		return low;
	}
	if (high < low)
	{
		return high;
	}
	return value;
}

