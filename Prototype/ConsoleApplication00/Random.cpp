#include "Stdafx.h"
#include "Random.h"
#include "Macro.h"
#include "UnitTest.h"

#if defined(UNITTEST)
const bool Random::UnitTest()
{
	UNIT_TEST_HEAD("Random");

	bool ok = true;

	if (ok)
	{
		auto pRandom0 = FactorySeed(42);
		auto pRandom1 = FactorySeed(42);
		for (int index = 0; index < 100; ++index)
		{
			ok &= UNIT_TEST_COMPARE(pRandom0->GetPlusMinus(2.0f), pRandom1->GetPlusMinus(2.0f));
		}
	}

	return ok;
}
#endif

std::shared_ptr<Random> Random::Factory()
{
	return std::make_shared< Random >( 0 );
}

std::shared_ptr<Random> Random::FactorySeed(const int seed)
{
	return std::make_shared< Random >( seed );
}

Random::Random(const int seed)
	: m_seed(seed)
	, m_random(seed)
	, m_distributionMinusOnePlusOne(-1.0f, 1.0f)
	, m_distributionZeroPlusOne(0.0f, 1.0f)
{
	return;
}

const bool Random::TestPassFail(const float threashold)
{
	return (m_distributionZeroPlusOne(m_random) < threashold);
}

const float Random::GetPlusMinus(const float radius)
{
	return (radius * m_distributionMinusOnePlusOne(m_random));
}
