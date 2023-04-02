#include "pch.h"
#include "NanMonkey/StepPixel.h"
#include "NanMonkey/Stage.h"
#include "NanMonkey/NanMonkey.h"
#include "NanMonkey/Random.h"

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

void NanMonkey::StepPixel::Reference::ModifyWeight(const float delta)
{
	m_weight += delta;
}

NanMonkey::StepPixel::StepPixel(const bool locked, const std::vector<Reference>& reference)
	: m_locked(locked)
	, m_referenceArray(reference)
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

void NanMonkey::StepPixel::MutateAdd(const Dimention& dimention, const Index& pixelIndex, Random& random, const float mutateEnergyNormalised)
{
	if (true == m_locked)
	{
		return;
	}

	//gather a set of offset of existing renderences
	std::set<int> usedOffsets;
	std::vector<Reference> referenceArray;
	for(const auto& reference : m_referenceArray)
	{
		Index index = reference.GetIndex();
		const int offset = dimention.CalculateOffset(index);
		if (usedOffsets.find(offset) != usedOffsets.end())
		{
			continue;
		}

		const float newWeight = reference.GetWeight();
		referenceArray.push_back(StepPixel::Reference(newWeight, index));
		usedOffsets.insert(offset);
	}

	//now add a new reference, if the offset is not already in use
	{
		//pixelIndex
		Index index(pixelIndex);
		index.Mutate(dimention, random, mutateEnergyNormalised);
		const int offset = dimention.CalculateOffset(index);
		if (usedOffsets.find(offset) != usedOffsets.end())
		{
			return;
		}
		const float newWeight = random.GetPlusMinusFloat(mutateEnergyNormalised);
		referenceArray.push_back(StepPixel::Reference(newWeight, index));
	}

	m_referenceArray = referenceArray;
}

void NanMonkey::StepPixel::Mutate(const Dimention& dimention, Random& random, const float mutateEnergyNormalised)
{
	if (true == m_locked)
	{
		return;
	}

	std::set<int> usedOffsets;
	std::vector<Reference> referenceArray;
	for(const auto& reference : m_referenceArray)
	{
		Index index = reference.GetIndex();
		index.Mutate(dimention, random, mutateEnergyNormalised);
		const int offset = dimention.CalculateOffset(index);
		if (usedOffsets.find(offset) != usedOffsets.end())
		{
			continue;
		}

		const float newWeight = reference.GetWeight() + random.GetPlusMinusFloat(mutateEnergyNormalised);
		referenceArray.push_back(StepPixel::Reference(newWeight, index));
		usedOffsets.insert(offset);
	}
	m_referenceArray = referenceArray;
}
