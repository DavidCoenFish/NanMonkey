#include "Stdafx.h"
#include "NanMonkey.h"
#include "UnitTest.h"


#if defined(UNITTEST)
const bool NanMonkey::UnitTest()
{
	UNIT_TEST_HEAD("NanMonkey");

	bool ok = true;
	if (ok)//ByteToFloat
	{
		ok &= UNIT_TEST_COMPARE(0.0f, ByteToFloat(0));
		ok &= UNIT_TEST_COMPARE(1.0f, ByteToFloat(255));
		ok &= UNIT_TEST_COMPARE(0.501960814f, ByteToFloat(128));

	}
	return ok;
}
#endif

const int NanMonkey::GetSize(const int x, const int y, const int z)
{
	ASSERT(0 <= x, "invalid param");
	ASSERT(0 <= y, "invalid param");
	ASSERT(0 <= z, "invalid param");

	return (x * y * z);
}

const int NanMonkey::GetOffset(const int x, const int y, const int z, const int indexX, const int indexY, const int indexZ)
{
	ASSERT((0 <= indexX) && (indexX < x), "invalid param");
	ASSERT((0 <= indexY) && (indexY < y), "invalid param");
	ASSERT((0 <= indexZ) && (indexZ < z), "invalid param");

	int offset = indexX + (indexY * x) + (indexZ * x * y);
	return offset;
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

const float NanMonkey::ByteToNormalisedFloat(const unsigned char value)
{
	const float result = (((((float)value) / 255.0f) * 2.0f) - 1.0f);
	return result;
}

const float NanMonkey::ByteToFloat(const unsigned char value)
{
	const float result = ((float)value) / 255.0f;
	return result;
}

