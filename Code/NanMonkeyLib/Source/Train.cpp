#include "pch.h"
#include "NanMonkey/Train.h"

#include "NanMonkey/NeuralNetwork.h"
#include "NanMonkey/TrainingData.h"
#include "NanMonkey/TrainingScore.h"
#include "NanMonkey/Random.h"
#include "NanMonkey/Step.h"

namespace 
{
	//std::shared_ptr<NanMonkey::TrainingScore> FactoryTrain(const NanMonkey::NeuralNetwork& neuralNetwork, const NanMonkey::TrainingData& trainingData)

	std::shared_ptr<NanMonkey::NeuralNetwork> FactoryNeuralNetworkSeed(const NanMonkey::Dimention& dimention, const std::vector<float>& weight)
	{
		//make a copy step
		std::vector<std::shared_ptr<NanMonkey::Step>> stepArray;
		stepArray.push_back(NanMonkey::Step::FactoryCopyStepWeight(dimention, weight));

		return std::make_shared<NanMonkey::NeuralNetwork>(stepArray);
	}

	//std::shared_ptr<NanMonkey::NeuralNetwork> FactoryNeuralNetworkPerturb(const NanMonkey::NeuralNetwork& neuralNetwork, const NanMonkey::TrainingScore& score, NanMonkey::Random& random, const float mutateEnergyNormalised)
	//{
	//}


	//	// types of changes [change link weight, remove link, add link, add step]
	//	const int count = std::max(1, (int)((mutateEnergyNormalised * mutateEnergyNormalised) * 128));
	//	for (int index = 0; index < count; ++index)
	//	{
	//		const float rand = random.GetPlusMinusFloat(1.0f);
	//		const int choice = std::min((int)((rand * rand) * 4), 3);
	//		switch(choice)
	//		{
	//		default:
	//			break;
	//		case 0:

	//			break;
	//		}


	//	}

	//	return nullptr;
	//}
}

const bool NanMonkey::Train(
	std::shared_ptr<NeuralNetwork>& outNeuralNetwork,
	std::shared_ptr<TrainingScore>& inOutScore,
	const Dimention& dimention,
	const NeuralNetwork& neuralNetwork, 
	const TrainingData& trainingData, 
	Random& random, 
	const std::function<void(const std::string&)>& log,
	const int attemptMax
	)
{
	inOutScore = inOutScore ? inOutScore : TrainingScore::Factory(dimention, neuralNetwork, trainingData);
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
		std::vector<float> weightArray;
		inOutScore->VisitTargetRange([&](const bool valid, const float low, const float high){
			float weight = 0.0f;
			if (valid)
			{
				if ((0.0f != low) || (0.0f != high))
				{
					weight = std::max(abs(low), abs(high));
					if (high <= 0.0f)
					{
						weight = -weight;
					}
				}
			}
			weightArray.push_back(weight);
			});
		outNeuralNetwork = FactoryNeuralNetworkSeed(dimention, weightArray);
		inOutScore = nullptr;
		return true;
	}

	//make a small changes, and if one is better, return; make more and more drastic changes till we give up

	int countDown = 3;
	for (int index = 0; index < attemptMax; ++index)
	{
		const float mutateEnergyNormalised = ((float)(index + 1)) / ((float)(attemptMax));
		//auto pCandidate = FactoryNeuralNetworkPerturb(neuralNetwork, *inOutScore, random, mutateEnergyNormalised);
		auto pCandidate = NeuralNetwork::FactoryPerturb(neuralNetwork, *inOutScore, random, mutateEnergyNormalised);
		auto pCandidateScore = TrainingScore::Factory(dimention, *pCandidate, trainingData);
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
