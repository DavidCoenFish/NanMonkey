#include "pch.h"
#include "NanMonkey/Train.h"

#include "NanMonkey/NeuralNetwork.h"
#include "NanMonkey/TrainingData.h"
#include "NanMonkey/TrainingScore.h"
#include "NanMonkey/Random.h"
#include "NanMonkey/Step.h"

namespace 
{
	std::shared_ptr<NanMonkey::TrainingScore> FactoryTrain(const NanMonkey::NeuralNetwork& neuralNetwork, const NanMonkey::TrainingData& trainingData)
	{
		std::shared_ptr<NanMonkey::TrainingScore> pResult;

		trainingData.Visit([&](const NanMonkey::Stage& input,const NanMonkey::Stage& target){
			if (nullptr == pResult)
			{
				pResult = std::make_shared<NanMonkey::TrainingScore>(target.GetDimention());
			}
			auto actualResult = neuralNetwork.Perform(input);
			pResult->GatherScore(target, *actualResult);
			});

		return pResult;
	}

	std::shared_ptr<NanMonkey::NeuralNetwork> FactoryNeuralNetworkSeed(const NanMonkey::Dimention& score)
	{
		//make a copy step
		std::vector<std::shared_ptr<NanMonkey::Step>> stepArray;
		stepArray.push_back(NanMonkey::Step::FactoryCopyStep(score.GetDimention()));

		return std::make_shared<NanMonkey::NeuralNetwork>(stepArray);
	}

	std::shared_ptr<NanMonkey::NeuralNetwork> FactoryNeuralNetworkPerturb(const NanMonkey::NeuralNetwork& neuralNetwork, const NanMonkey::TrainingScore& score, const NanMonkey::Random& random, const float weight)
	{
		return nullptr;
	}
}

const bool NanMonkey::Train(
	std::shared_ptr<NeuralNetwork>& outNeuralNetwork,
	std::shared_ptr<TrainingScore>& inOutScore,
	const NeuralNetwork& neuralNetwork, 
	const TrainingData& trainingData, 
	Random& random, 
	const std::function<void(const std::string&)>& log,
	const int attemptMax
	)
{
	inOutScore = inOutScore ? inOutScore : FactoryTrain(neuralNetwork, trainingData);
	if (nullptr == inOutScore)
	{
		return false;
	}

	const float bestDeltaScore = inOutScore->GetDeltaScore();
	if (0.0f == bestDeltaScore)
	{
		if(log) log("average delta score is zero, training done");
		return false;
	}

	const int stepCount = neuralNetwork.GetStepCount();
	if (0 == stepCount)
	{
		if(log) log("seed NeuralNetwork");
		outNeuralNetwork = FactoryNeuralNetworkSeed(*inOutScore);
		inOutScore = nullptr;
		return true;
	}

	//make a small changes, and if one is better, return; make more and more drastic changes till we give up

	int countDown = 3;
	for (int index = 0; index < attemptMax; ++index)
	{
		const float weight = ((float)(index + 1)) / ((float)(attemptMax));
		auto pCandidate = FactoryNeuralNetworkPerturb(neuralNetwork, *inOutScore, random, weight);
		auto pCandidateScore = FactoryTrain(*pCandidate, trainingData);
		const float candidateScore = inOutScore->GetDeltaScore();
		if (candidateScore < bestDeltaScore)
		{
			outNeuralNetwork = pCandidate;
			inOutScore = pCandidateScore;
			countDown -= 1;
			if (countDown <= 0)
			{
				if(log) log("select small change");
				return true;
			}
		}
	}

	//
	//for (int index = 0; index < attemptMax; ++index)
	//{
	//}

	return false;
}
