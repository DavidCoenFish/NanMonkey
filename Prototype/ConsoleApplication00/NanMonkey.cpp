#include "Stdafx.h"
#include "NanMonkey.h"

const int NanMonkey::GetSize(const int x, const int y, const int z)
{
	ASSERT(0 <= x, "invalid param");
	ASSERT(0 <= y, "invalid param");
	ASSERT(0 <= z, "invalid param");

	return (x * y * z);
}

const float NanMonkey::Clamp(const float input, const float lowInclusive, const float hightInclusive)
{
	//todo: assert on nan input
	if (input < lowInclusive)
	{
		return lowInclusive;
	}
	if (hightInclusive < input)
	{
		return hightInclusive;
	}
	return input;
}
