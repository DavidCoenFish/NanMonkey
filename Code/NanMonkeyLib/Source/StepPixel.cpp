#include "pch.h"
#include "NanMonkey/StepPixel.h"
#include "NanMonkey/Stage.h"
#include "NanMonkey/NanMonkey.h"

NanMonkey::StepPixel::StepPixel(const std::vector<Reference>& reference)
	: m_referenceArray(reference)
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

