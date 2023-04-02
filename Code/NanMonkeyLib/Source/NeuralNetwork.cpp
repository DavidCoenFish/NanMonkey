#include "pch.h"
#include "NanMonkey/NeuralNetwork.h"
#include "NanMonkey/Stage.h"
#include "NanMonkey/Step.h"

//std::shared_ptr<NanMonkey::NeuralNetwork> NanMonkey::NeuralNetwork::FactorySeed(const TrainingScore& score)
//{
//
//}
//

//static std::shared_ptr<NeuralNetwork> FactoryPerturb(const NeuralNetwork& neuralNetwork, const TrainingScore& score, const Random& random, const float mutateStrengthNormalised);
//std::shared_ptr<NanMonkey::NeuralNetwork> NanMonkey::NeuralNetwork::FactoryPerturb(const NeuralNetwork& neuralNetwork, const TrainingScore& score, const Random& random, const float mutateStrengthNormalised)
	//get a sorted array of the worst pixels from TrainingScore
	//mutations [change weight, change reference, add link, remove link, add step]
	//merge step, it there is a step without locked pixels and under max links

//
//NanMonkey::NeuralNetwork::NeuralNetwork(const NeuralNetwork& rhs)
//	: m_stepArray(rhs.m_stepArray)
//{
//	return;
//}

//std::shared_ptr<NanMonkey::NeuralNetwork> NanMonkey::NeuralNetwork::FactoryClone(const NeuralNetwork& neuralNetwork)
//{
//
//}

NanMonkey::NeuralNetwork::NeuralNetwork(const std::vector<std::shared_ptr<Step>>& stepArray)
	: m_stepArray(stepArray)
{
	return;
}

/*
did consider passing in a std::shared_ptr<Stage>& input, but then training data needed to expose input as shared_ptr
*/
std::shared_ptr<NanMonkey::Stage> NanMonkey::NeuralNetwork::Perform(const Stage& input) const
{
	if (0 == m_stepArray.size())
	{
		return std::make_shared<Stage>(input);
	}

	const Stage* pTrace = &input;
	std::shared_ptr<NanMonkey::Stage> pRef = nullptr;
	for (const auto& iter : m_stepArray)
	{
		pRef = iter->Perform(*pTrace);
		pTrace = pRef.get();
		if (nullptr == pTrace)
		{
			break;
		}
	}
	return pRef;
}

const int NanMonkey::NeuralNetwork::GetStepCount() const
{
	return (int)m_stepArray.size();
}

std::vector<std::shared_ptr<NanMonkey::Step>> NanMonkey::NeuralNetwork::MakeStepCopy() const
{
	std::vector<std::shared_ptr<Step>> stepArrayCopy;
	for (const auto& step : m_stepArray)
	{
		stepArrayCopy.push_back(Step::FactoryCopy(*step));
	}
	return stepArrayCopy;
}

//void NanMonkey::NeuralNetwork::ClearScore()
//{
//	for (auto& iter : m_stepArray)
//	{
//		iter->ClearScore();
//	}
//}


