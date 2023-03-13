#include "Stdafx.h"
#include "Step.h"
#include "State.h"
#include "NanMonkey.h"
#include "Random.h"
#include "UnitTest.h"


#if defined(UNITTEST)
const bool Step::UnitTest()
{
	UNIT_TEST_HEAD("Step");

	bool ok = true;

	if (ok)
	{
		std::stringstream stream;
		{
			//std::fstream stream;
			//stream.open("test.bin", std::ios::out | std::ios::binary);

			auto pStep = Factory(4,3,2);
			pStep->m_weights[0] = std::vector<float>({1.0f, 1.1f, 1.0f, 1.1f, 1.0f, 1.1f, 1.0f, 1.1f, 1.0f, 1.1f, 1.0f, 1.1f});
			pStep->m_weights[11] = std::vector<float>({0.9f, 0.8f, 0.7f, 0.6f, 0.7f, 0.6f, 0.5f, 0.4f, 0.3f, 0.2f, 0.1f, 1.1f, 0.9f, 0.8f, 0.7f, 0.6f, 0.7f, 0.6f, 0.5f, 0.4f, 0.3f, 0.2f, 0.1f, 1.1f});

			stream << *pStep;

			//stream.close();
		}
		//stream.seekg(0, stream.beg);
		{
			//std::fstream stream;
			//stream.open("test.bin", std::ios::in | std::ios::binary);

			auto pStep = Factory(0,0,0);
			stream >> *pStep;

			ok &= UNIT_TEST_COMPARE(4, pStep->m_x);
			ok &= UNIT_TEST_COMPARE(3, pStep->m_y);
			ok &= UNIT_TEST_COMPARE(2, pStep->m_z);
			ok &= UNIT_TEST_COMPARE(0.8f, pStep->m_weights[11][1]);

			//stream.close();
		}
	}

	if (ok)
	{
		auto pStep = Factory(2,2,2);
		ok &= UNIT_TEST_COMPARE(8, (int)pStep->m_weights.size());

		for (int index = 0; index < 8; ++index)
		{
			for (int subIndex = 0; subIndex < 8; ++subIndex)
			{
				pStep->m_weights[index][subIndex] = subIndex * 1.0f;
			}
		}

		auto pStage = State::Factory(2,2,2, std::vector<float>({0, -0.1f, 0.1f, 0,0,0,0,0}));

		auto pOutput = Step::ApplyStep(*pStep, *pStage);

		ok &= UNIT_TEST_NOT_NULL(pOutput.get());

		for (int indexZ = 0; indexZ < 2; ++indexZ)
		{
			for (int indexY = 0; indexY < 2; ++indexY)
			{
				for (int indexX = 0; indexX < 2; ++indexX)
				{
					ok &= UNIT_TEST_COMPARE(0.1f, pOutput->GetValue(indexX, indexY, indexZ));
				}
			}
		}
	}

	return ok;
}
#endif

std::shared_ptr<Step> Step::Factory(const int x, const int y, const int z)
{
	return std::make_shared<Step>(x,y,z);
}

std::shared_ptr<Step> Step::FactoryInvert(const Step& step)
{
	auto pStep = Factory(step.m_x, step.m_y, step.m_z);
	typedef std::vector< float >::const_iterator TConstIter;
	std::vector< TConstIter > iterArray;
	for (TWeightArray::const_iterator iterWeight = step.m_weights.cbegin(); iterWeight != step.m_weights.cend(); ++iterWeight)
	{
		iterArray.push_back(iterWeight->cbegin());
	}

	for (TWeightArray::iterator iterWeight = pStep->m_weights.begin(); iterWeight != pStep->m_weights.end(); ++iterWeight)
	{
		std::vector< float >& arrayDataOutput = (*iterWeight);
		std::vector< TConstIter >::iterator constSource = iterArray.begin();
		for (std::vector< float >::iterator iter = arrayDataOutput.begin(); iter != arrayDataOutput.cend(); ++iter, ++constSource)
		{
			(*iter) = *(*constSource);
			++(*constSource);
		}
	}

	return pStep;
}

std::shared_ptr<Step> Step::FactoryClone(const Step& step)
{
	auto pStep = Factory(step.m_x, step.m_y, step.m_z);
	TWeightArray::iterator outputIterWeight = pStep->m_weights.begin();
	for (TWeightArray::const_iterator iterWeight = step.m_weights.cbegin(); iterWeight != step.m_weights.cend(); ++iterWeight, ++outputIterWeight)
	{
		const std::vector< float >& arrayData = (*iterWeight);
		std::vector< float >& arrayDataOutput = (*outputIterWeight);
		std::vector< float >::iterator iterOutput = arrayDataOutput.begin();
		for (std::vector< float >::const_iterator iter = arrayData.cbegin(); iter != arrayData.cend(); ++iter, ++iterOutput)
		{
			(*iterOutput) = (*iter);
		}
	}

	return pStep;
}

std::ostream & operator<<(std::ostream & stream, const std::vector<std::shared_ptr<Step>>& stepArray)
{
	size_t size = stepArray.size();
	STREAM_POD_WRITE(stream, size);
	//stream << stepArray.size();
	for (auto iter : stepArray)
	{
		stream << (*iter);
	}

	return stream;
}

std::ostream & operator<<(std::ostream & stream, const Step& step)
{
	//stream << step.m_x
	//	<< step.m_y
	//	<< step.m_z;
	STREAM_POD_WRITE(stream, step.m_x);
	STREAM_POD_WRITE(stream, step.m_y);
	STREAM_POD_WRITE(stream, step.m_z);

	for (auto& iter : step.m_weights)
	{
		for (auto& subIter : iter)
		{
			//stream << subIter;
			STREAM_POD_WRITE(stream, subIter);
		}
	}

	return stream;
}
std::istream& operator>>(std::istream& stream, std::vector<std::shared_ptr<Step>>& stepArray)
{
	size_t size = 0;
	STREAM_POD_READ(stream, size);
	stepArray.clear();
	for (size_t index = 0; index < size; ++index)
	{
		auto pStep = std::make_shared< Step >(0,0,0);
		stream >> (*pStep);
		stepArray.push_back(pStep);
	}
	return stream;
}

std::istream& operator>>(std::istream& stream, Step& step)
{
	//stream >> step.m_x
	//	>> step.m_y
	//	>> step.m_z;
	STREAM_POD_READ(stream, step.m_x);
	STREAM_POD_READ(stream, step.m_y);
	STREAM_POD_READ(stream, step.m_z);
	step.ResizeWeights();
	for (auto& iter : step.m_weights)
	{
		for (auto& subIter : iter)
		{
			//stream >> subIter;
			STREAM_POD_READ(stream, subIter);
		}
	}
	return stream;
}

Step::Step(const int x, const int y, const int z)
	: m_x(x)
	, m_y(y)
	, m_z(z)
{
	ASSERT(0 <= x, "invalid param");
	ASSERT(0 <= y, "invalid param");
	ASSERT(0 <= z, "invalid param");

	ResizeWeights();
}

std::shared_ptr<State> Step::ApplyStep(const Step& step, const State& input)
{
	std::vector< float > data;
	const int size = NanMonkey::GetSize(step.m_x, step.m_y, step.m_z);
	data.resize(size, 0.0f);
	std::vector< float >::iterator dest = data.begin();
	for (TWeightArray::const_iterator iter = step.m_weights.cbegin(); iter != step.m_weights.cend(); ++iter)
	{
		(*dest) = State::CalculateWeightValue(input, *iter);
		++dest;
	}

	return State::Factory(step.m_x, step.m_y, step.m_z, data);
}

void Step::PerturbStep(Step& step, Random& random, const float chanceOfModificationOfWeight, const float plusMinusMaxChangeWeight)
{
	for (TWeightArray::iterator iterWeight = step.m_weights.begin(); iterWeight != step.m_weights.end(); ++iterWeight)
	{
		std::vector< float >& arrayData = (*iterWeight);
		for (std::vector< float >::iterator iter = arrayData.begin(); iter != arrayData.end(); ++iter)
		{
			if (false == random.TestPassFail(chanceOfModificationOfWeight))
			{
				continue;
			}
			(*iter) += random.GetPlusMinus(plusMinusMaxChangeWeight);
		}
	}
	return;
}

void Step::ResizeWeights()
{
	const int size = NanMonkey::GetSize(m_x, m_y, m_z);
	m_weights.resize(size);
	for (int index = 0; index < size; ++index)
	{
		//m_weights[index] = std::make_shared< std::vector< float > >(size, 0.0f);
		m_weights[index].resize(size, 0.0f);
	}
}
