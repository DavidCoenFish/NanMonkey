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
