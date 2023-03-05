#include "Stdafx.h"
#include "Network.h"
#include "State.h"
#include "Step.h"
#include "NanMonkey.h"
#include "Random.h"
#include "Macro.h"
#include "UnitTest.h"

#if defined(UNITTEST)
const bool Network::UnitTest()
{
	UNIT_TEST_HEAD("Network");
	bool ok = true;

	if (ok)
	{
		std::stringstream stream;
		{
			auto pNetwork = Factory(4,3,2);
			stream << *pNetwork;
		}
		{
			auto pNetwork = std::make_shared< Network>();
			stream >> *pNetwork;

			ok &= UNIT_TEST_COMPARE(4, pNetwork->m_x);
			ok &= UNIT_TEST_COMPARE(3, pNetwork->m_y);
			ok &= UNIT_TEST_COMPARE(2, pNetwork->m_z);
			//ok &= UNIT_TEST_COMPARE((size_t)2, pNetwork->m_stepArray.size());
		}
	}


	return ok;
}
#endif

//std::shared_ptr<Network> Network::Factory(const int x, const int y, const int z, const int seed, const int stepCount, const float chanceWeight, const float weightRange)
//{
//	std::vector<std::shared_ptr<Step>> stepArray;
//	auto pRandom = Random::FactorySeed(seed);
//	for (int index = 0; index < stepCount; ++index)
//	{
//		auto pStep = Step::Factory(x, y, z);
//		Step::PerturbStep(*pStep, *pRandom, chanceWeight, weightRange);
//		stepArray.push_back(pStep);
//	}
//
//	return std::make_shared<Network> (x, y, z, seed, 0, stepArray);
//}

std::shared_ptr<Network> Network::Factory(const int x, const int y, const int z, const std::vector<std::shared_ptr<Step>>& stepArray)
{
	return std::make_shared<Network> (x, y, z, stepArray);
}

std::ostream & operator<<(std::ostream & stream, const Network& network)
{
	STREAM_POD_WRITE(stream, network.m_x);
	STREAM_POD_WRITE(stream, network.m_y);
	STREAM_POD_WRITE(stream, network.m_z);
	stream << network.m_stepArray;
	return stream;
}

std::istream& operator>>(std::istream& stream, Network& network)
{
	STREAM_POD_READ(stream, network.m_x);
	STREAM_POD_READ(stream, network.m_y);
	STREAM_POD_READ(stream, network.m_z);
	stream >> network.m_stepArray;
	return stream;
}

Network::Network(const int x, const int y, const int z, const std::vector<std::shared_ptr<Step>>& stepArray)
	: m_x(x)
	, m_y(y)
	, m_z(z)
	, m_stepArray(stepArray)
{
	return;
}

std::shared_ptr<State> Network::Evalue(const std::shared_ptr<State>& input) const
{
	std::shared_ptr<State> pResult;
	std::shared_ptr<State> pTrace = input;
	for (std::vector<std::shared_ptr<Step>>::const_iterator iter = m_stepArray.cbegin(); iter != m_stepArray.end(); ++iter)
	{
		pResult = Step::ApplyStep(*(*iter), *pTrace);
		pTrace = pResult;
	}
	return pResult;
}
