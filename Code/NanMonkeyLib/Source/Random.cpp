#include "pch.h"
#include "NanMonkey/Random.h"

std::shared_ptr<NanMonkey::Random> NanMonkey::Random::Factory()
{
	return std::make_shared< Random >( 0 );
}

std::shared_ptr<NanMonkey::Random> NanMonkey::Random::FactorySeed(const int seed)
{
	return std::make_shared< Random >( seed );
}

NanMonkey::Random::Random(const int seed)
	: m_seed(seed)
	, m_random(seed)
	, m_distributionMinusOnePlusOne(-1.0f, 1.0f)
	, m_distributionZeroPlusOne(0.0f, 1.0f)
{
	return;
}

const bool NanMonkey::Random::TestPassFail(const float threashold)
{
	return (m_distributionZeroPlusOne(m_random) < threashold);
}

const float NanMonkey::Random::GetPlusFloat(const float scale)
{
	return (m_distributionZeroPlusOne(m_random) * scale);
}

const float NanMonkey::Random::GetPlusMinusFloat(const float radius)
{
	return (radius * m_distributionMinusOnePlusOne(m_random));
}

void NanMonkey::Random::GenerateRangeFloatVisitor(const int count, const float low, const float high, const std::function<void(const float)>& visitor)
{
	const float mid = (low + high) * 0.5f;
	const float radius = (high - low) * 0.5f;
	for (int index = 0; index < count; ++index)
	{
		const float value = mid + GetPlusMinusFloat(radius);
		visitor(value);
	}
	return;
}
