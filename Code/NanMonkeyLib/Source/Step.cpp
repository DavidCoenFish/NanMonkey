#include "pch.h"
#include "NanMonkey/Step.h"

#include "NanMonkey/Stage.h"
#include "NanMonkey/StepPixel.h"

NanMonkey::Step::Step(const Dimention& dimention, const std::vector<std::shared_ptr<StepPixel>>& data)
	: m_dimention(dimention)
	, m_data(data)
{
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
