#include "pch.h"
#include "NanMonkey/Train.h"

#include "NanMonkey/NeuralNetwork.h"
#include "NanMonkey/TrainingData.h"
#include "NanMonkey/TrainingScore.h"
#include "NanMonkey/Random.h"

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
}

const bool NanMonkey::Train(
	std::shared_ptr<NanMonkey::NeuralNetwork>& outNeuralNetwork,
	std::shared_ptr<NanMonkey::TrainingScore>& inOutScore,
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
		if(log) log("average delta score is zero, training done");
		//outNeuralNetwork = std::make_shared<NanMonkey::NeuralNetwork>(neuralNetwork);
		//outNeuralNetwork->InsertCopyStep(0);
		//outNeuralNetwork->EnforceScoreStep(0, 1.0f, *inOutScore);
		outNeuralNetwork = NanMonkey::NeuralNetwork::FactorySeed(*inOutScore);
		inOutScore = nullptr;
		return true;
	}

	int countDown = 3;
	//pResult->EnforceScoreStep(stepCount - 1, 1.0f / ((float)(stepCount + 1)), *inOutScore);
	//make a few small changes, and if one is better, return; make more and more drastic changes till we give up
	for (int index = 0; index < attemptMax; ++index)
	{
		//auto pCandidate = std::make_shared<NanMonkey::NeuralNetwork>(*pResult);
		const float weight = ((float)(index + 1)) / ((float)(attemptMax));
		auto pCandidate = NanMonkey::NeuralNetwork::FactoryPerturb(neuralNetwork, *inOutScore, random, weight);
		auto pCandidateScore = FactoryTrain(*pCandidate, trainingData);
		const float candidateScore = inOutScore->GetDeltaScore();
		if (candidateScore < bestDeltaScore)
		{
			outNeuralNetwork = pCandidate;
			inOutScore = pCandidateScore;
			countDown -= 1;
			if (countDown <= 0)
			{
				return true;
			}
		}
	}

	return false;
}
