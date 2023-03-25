#include "pch.h"
#include "NanMonkey/NeuralNetwork.h"
#include "NanMonkey/Step.h"

NanMonkey::NeuralNetwork::NeuralNetwork(const std::vector<std::shared_ptr<Step>>& stepArray)
	: m_stepArray(stepArray)
{
	return;
}

std::shared_ptr<NanMonkey::Stage> NanMonkey::NeuralNetwork::Perform(const Stage& input) const
{
	const Stage* pStage = &input;
	std::shared_ptr<NanMonkey::Stage> pRef;
	for (const auto& iter : m_stepArray)
	{
		pRef = iter->Perform(*pStage);
		pStage = pRef.get();
		if (nullptr == pStage)
		{
			break;
		}
	}
	return pRef;
}


