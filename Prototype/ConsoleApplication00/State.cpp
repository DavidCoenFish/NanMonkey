#include "Stdafx.h"
#include "State.h"
#include "NanMonkey.h"
#include "Macro.h"
#include "UnitTest.h"

#if defined(UNITTEST)
const bool State::UnitTest()
{
	UNIT_TEST_HEAD("State");
	bool ok = true;

	if (ok)
	{
		std::stringstream stream;
		{
			auto pState = Factory(4,3,2, {
				1.0f, 2.0f, 3.0f, 4.0f, 1.1f, 2.1f, 3.1f, 4.1f, 1.2f, 2.2f, 3.2f, 4.2f, 
				1.3f, 2.3f, 3.3f, 4.3f, 1.4f, 2.4f, 3.4f, 4.4f, 1.5f, 2.5f, 3.5f, 4.5f
				});
			stream << *pState;

		}
		{
			auto pState = Factory(0,0,0);
			stream >> *pState;

			ok &= UNIT_TEST_COMPARE(4, pState->m_x);
			ok &= UNIT_TEST_COMPARE(3, pState->m_y);
			ok &= UNIT_TEST_COMPARE(2, pState->m_z);
			ok &= UNIT_TEST_COMPARE(2.3f, pState->m_data[13]);
		}
	}

	return ok;
}
#endif

std::shared_ptr<State> State::Factory(const int x, const int y, const int z, const std::vector< float >& dataOrEmpty)
{
	auto pState = std::make_shared< State >( x, y, z);
	if (0 != dataOrEmpty.size())
	{
		ASSERT(dataOrEmpty.size() == pState->m_data.size(), "invalid state");
		pState->m_data = dataOrEmpty;
	}
	return pState;
}

std::ostream & operator<<(std::ostream & stream, const State& state)
{
	STREAM_POD_WRITE(stream, state.m_x);
	STREAM_POD_WRITE(stream, state.m_y);
	STREAM_POD_WRITE(stream, state.m_z);

	for (auto& iter : state.m_data)
	{
		//stream << subIter;
		STREAM_POD_WRITE(stream, iter);
	}
	return stream;
}

std::istream& operator>>(std::istream& stream, State& state)
{
	STREAM_POD_READ(stream, state.m_x);
	STREAM_POD_READ(stream, state.m_y);
	STREAM_POD_READ(stream, state.m_z);
	state.ResizeData();
	for (auto& iter : state.m_data)
	{
		STREAM_POD_READ(stream, iter);
	}
	return stream;
}

State::State(const int x, const int y, const int z)
	: m_x(x)
	, m_y(y)
	, m_z(z)
	, m_data()
{
	ASSERT(0 <= x, "invalid param");
	ASSERT(0 <= y, "invalid param");
	ASSERT(0 <= z, "invalid param");

	ResizeData();
}

const float State::CalculateWeightValue(const State& state, const std::vector< float >& weights)
{
	const int size = NanMonkey::GetSize(state.m_x, state.m_y, state.m_z);
	ASSERT(size == weights.size(), "invalid param");

	float result = 0.0f;
	for (std::vector< float >::const_iterator iterWeight = weights.cbegin(), iterState = state.m_data.cbegin(); iterWeight != weights.cend(); ++iterWeight, ++iterState)
	{
		result += ((*iterState) * (*iterWeight));
	}

	result = NanMonkey::Clamp(result);
	return result;
}


const float State::CalculateDeltaScore(const State& left, const State& right)
{
	ASSERT(left.m_x == right.m_x, "invalid param");
	ASSERT(left.m_y == right.m_y, "invalid param");
	ASSERT(left.m_z == right.m_z, "invalid param");
	ASSERT(left.m_data.size() == right.m_data.size(), "invalid param");

	float score = 0.0f;
	for (std::vector< float >::const_iterator iterLeft = left.m_data.cbegin(), iterRight = right.m_data.cbegin(); iterLeft != left.m_data.cend(); ++iterLeft, ++iterRight)
	{
		score += abs(iterLeft - iterRight);
	}
	return score;
}

//void State::SetFromFilePng(State& state, const std::string& filePath, const int zIndex)
//{
//}

void State::ResizeData()
{
	const int size = NanMonkey::GetSize(m_x, m_y, m_z);
	m_data.resize(size, 0.0f);
}
