#include "pch.h"
#include "NanMonkey/StepPixel.h"
#include "NanMonkey/Stage.h"
#include "NanMonkey/NanMonkey.h"

std::shared_ptr<NanMonkey::StepPixel> NanMonkey::StepPixel::FactoryCopy(const StepPixel& stepPixel)
{
	return std::make_shared<StepPixel>(stepPixel.m_locked, stepPixel.m_referenceArray);
}

NanMonkey::StepPixel::Reference::Reference(const float weight, const Index& index)
	: m_weight(weight)
	, m_index(index)
{
	return;
}


NanMonkey::StepPixel::StepPixel(const bool locked, const std::vector<Reference>& reference)
	: m_locked(locked)
	, m_referenceArray(reference)
	//, m_scoreSumPositive(0.0f)
	//, m_scoreSumNegative(0.0f)
{
	return;
}

const float NanMonkey::StepPixel::EvaluePixel(const Dimention& dimention, const Stage& input) const
{
	float result = 0.0f;
	for(const auto& reference : m_referenceArray)
	{
		result += (input.GetValue(reference.GetIndex()) * reference.GetWeight());
	}

	result = NanClamp(result, -1.0f, 1.0f);

	return result;
}

//void NanMonkey::StepPixel::ClearScore()
//{
//	m_scoreSumPositive = 0.0f;
//	m_scoreSumNegative = 0.0f;
//}

//void NanMonkey::StepPixel::AddScore(const float score)
//{
//	if (0.0f < score)
//	{
//		m_scoreSumPositive += score;
//	}
//	if (score < 0.0f)
//	{
//		m_scoreSumNegative += score;
//	}
//}
//
//const float NanMonkey::StepPixel::GetScore() const
//{
//	return m_scoreSumPositive - m_scoreSumNegative;
//}
