#include "pch.h"
#include "NanMonkey/Step.h"

#include "NanMonkey/NanMonkey.h"
#include "NanMonkey/Stage.h"
#include "NanMonkey/StepPixel.h"
#include "NanMonkey/Random.h"

std::shared_ptr<NanMonkey::Step> NanMonkey::Step::FactoryCopyStepWeight(const Dimention& dimention, const std::vector<float>& weight)
{
	const int length = dimention.CalculateLength();
	NanAssert(length == (int)weight.size(), "invalid state");
	std::vector<std::shared_ptr<StepPixel>> data(length);
	for (int index = 0; index < length; ++index)
	{
		const auto indexObject = dimention.ReverseCalculateOffset(index);
		const float pixelWeight = weight[index];
		std::vector<StepPixel::Reference> referenceAray;
		bool locked = true;
		if (0 != pixelWeight)
		{
			referenceAray.push_back(StepPixel::Reference(pixelWeight, indexObject));
			locked = false;
		}
		data[index] = std::make_shared<StepPixel>(locked, referenceAray);
	}

	return std::make_shared<Step>(dimention, data);
}

std::shared_ptr<NanMonkey::Step> NanMonkey::Step::FactoryCopyRandom(const Dimention& dimention, Random& random, const float mutateEnergyNormalised)
{
	const int length = dimention.CalculateLength();
	std::vector<std::shared_ptr<StepPixel>> data(length);
	for (int index = 0; index < length; ++index)
	{
		const auto indexObject = dimention.ReverseCalculateOffset(index);
		std::vector<StepPixel::Reference> referenceAray;
		referenceAray.push_back(StepPixel::Reference(random.GetPlusMinusFloat(1.0f), indexObject));
		auto pStepPixel = std::make_shared<StepPixel>(false, referenceAray);
		pStepPixel->Mutate(dimention, random, mutateEnergyNormalised);
		data[index] = pStepPixel;
	}

	return std::make_shared<Step>(dimention, data);
}

std::shared_ptr<NanMonkey::Step> NanMonkey::Step::FactoryCopy(const Step& step)
{
	const Dimention dimention = step.GetDimention();
	std::vector<std::shared_ptr<StepPixel>> data;
	for (const auto& pStepPixel : step.m_data)
	{
		data.push_back(StepPixel::FactoryCopy(*pStepPixel));
	}

	return std::make_shared<Step>(dimention, data);
}

NanMonkey::Step::Step(const Dimention& dimention, const std::vector<std::shared_ptr<StepPixel>>& data)
	: m_dimention(dimention)
	, m_data(data)
{
	NanAssert(m_data.size() == m_dimention.CalculateLength(), "bad param");
	return;
}

std::shared_ptr<NanMonkey::Stage> NanMonkey::Step::Perform(const Stage& input) const
{
	if (false == (input.GetDimention() == m_dimention))
	{
		return nullptr;
	}

	const int length = m_dimention.CalculateLength();
	std::vector<float> data(length);
	std::vector<float>::iterator dataIter = data.begin();
	std::vector<std::shared_ptr<StepPixel>>::const_iterator pixelIter = m_data.cbegin();
	//for(auto& iter : m_data)

	for (;dataIter != data.end() && pixelIter != m_data.cend(); ++dataIter, ++pixelIter)
	{
		(*dataIter) = (*pixelIter)->EvaluePixel(m_dimention, input);
	}

	return std::make_shared<Stage>(m_dimention, data);
}

std::shared_ptr<NanMonkey::StepPixel> NanMonkey::Step::GetStepPixel(const int offset) const
{
	if ((0 <= offset) && (offset < (int)m_data.size()))
	{
		return m_data[offset];
	}
	return nullptr;
}

