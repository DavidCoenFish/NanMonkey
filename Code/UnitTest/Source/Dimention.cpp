#include "Dimention.h"

#include "Main.h"
#include "UnitTest.h"

#include "NanMonkey/Dimention.h"
#include "NanMonkey/Index.h"

namespace
{
	const bool SanityCheck()
	{
		bool ok = true;
		const NanMonkey::Dimention dimention(std::vector<int>({2,3,4}));
		ok &= UNIT_TEST_COMPARE(3, dimention.GetCount());
		ok &= UNIT_TEST_COMPARE(2, dimention.GetValue(0));
		ok &= UNIT_TEST_COMPARE(3, dimention.GetValue(1));
		ok &= UNIT_TEST_COMPARE(4, dimention.GetValue(2));
		ok &= UNIT_TEST_COMPARE(24, dimention.CalculateLength());
		return ok;
	}
	const bool RoundTrip()
	{
		bool ok = true;
		const NanMonkey::Dimention dimention(std::vector<int>({2,3,4}));
		{
			const NanMonkey::Index index0(std::vector<int>({1,2,3}));
			const int offset = dimention.CalculateOffset(index0);
			const NanMonkey::Index index1 = dimention.ReverseCalculateOffset(offset);
			ok &= UNIT_TEST_COMPARE(true, index0 == index1);
		}
		{
			const int length = dimention.CalculateLength();
			for (int index = 0; index < length; ++index)
			{
				const auto indexObject = dimention.ReverseCalculateOffset(index);
				const int offset = dimention.CalculateOffset(indexObject);
				ok &= UNIT_TEST_COMPARE(index, offset);
			}
		}

		return ok;
	}
}

const bool Dimention::UnitTest()
{
	UNIT_TEST_HEAD("Dimention");
	bool ok = true;

	ok &= SanityCheck();
	ok &= RoundTrip();

	return ok;
}
