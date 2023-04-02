#include "pch.h"
#include "NanMonkey/Train.h"

#include "NanMonkey/NanMonkey.h"
#include "NanMonkey/NeuralNetwork.h"
#include "NanMonkey/TrainingData.h"
#include "NanMonkey/TrainingScore.h"
#include "NanMonkey/Random.h"
#include "NanMonkey/Step.h"
#include "NanMonkey/StepPixel.h"

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

	const bool SortScoreData(const std::pair<float, int>& lhs, std::pair<float, int>&rhs)
	{
		return (rhs.first < lhs.first);
	}

	void SelectPixelStepRecurse(std::shared_ptr<NanMonkey::StepPixel>& pOutStepPixel, int& outPixelIndex, int& outStepIndex, NanMonkey::Random& random, const std::vector<std::shared_ptr<NanMonkey::Step>>& stepArray, const NanMonkey::Dimention& dimention, const int pixelOffset, const int stepIndex, const float bias)
	{
		auto pStepPixel = stepArray[stepIndex]->GetStepPixel(pixelOffset);
		if ((false == pStepPixel->GetLocked()) && random.TestPassFail(bias))
		{
			pOutStepPixel = pStepPixel;
			outStepIndex = stepIndex;
			outPixelIndex = pixelOffset;
			return;
		}
		if (0 < stepIndex)
		{
			for (auto& reference : pStepPixel->GetReferenceArray())
			{
				const int childPixelOffset = dimention.CalculateOffset(reference.GetIndex());
				SelectPixelStepRecurse(pOutStepPixel, outPixelIndex, outStepIndex, random, stepArray, dimention, childPixelOffset, stepIndex - 1, bias); 
				if (nullptr != pOutStepPixel)
				{
					return;
				}
			}
		}
	}

	void SelectPixelStep(std::shared_ptr<NanMonkey::StepPixel>& pStepPixel, int& pixelIndex, int& stepIndex, NanMonkey::Random& random, const std::vector<std::shared_ptr<NanMonkey::Step>>& stepArray, const NanMonkey::Dimention& dimention, const int pixelOffset)
	{
		const int stepCount = (int)stepArray.size();
		if (1 == stepCount)
		{
			pStepPixel = stepArray.back()->GetStepPixel(pixelOffset);
			stepIndex = stepCount - 1;
			pixelIndex = pixelOffset;
			return;
		}

		float bias = 1.0f / (float)(stepCount + 1);
		for (int index = 0; index < 2; ++index)
		{
			SelectPixelStepRecurse(pStepPixel, pixelIndex, stepIndex, random, stepArray, dimention, pixelOffset, stepCount - 1, bias);
			if (nullptr != pStepPixel)
			{
				break;
			}
			//do another pass and use the first found, ie, bias of 1.0f
			bias = 1.0f;
		}
		return;
	}

	void ChangeLinkWeight(std::vector<std::shared_ptr<NanMonkey::Step>>& stepArray, NanMonkey::Random& random, const NanMonkey::Dimention& dimention, const int startPixelOffset, const float mutateEnergyNormalised)
	{
		std::shared_ptr<NanMonkey::StepPixel> pStepPixel;
		int pixelIndex = 0;
		int stepIndex = 0;
		SelectPixelStep(pStepPixel, pixelIndex, stepIndex, random, stepArray, dimention, startPixelOffset);
		if (nullptr == pStepPixel)
		{
			NanMonkey::NanAssert(false, "invalid state");
			return;
		}
		auto& referenceArray = pStepPixel->GetReferenceArray();
		const auto size = referenceArray.size();
		if (0 != size)
		{
			const int index = random.GetIndex(referenceArray.size());
			referenceArray[index].ModifyWeight(random.GetPlusMinusFloat(1.0f - mutateEnergyNormalised));
		}
		return;
	}

	void ChangeAddLink(std::vector<std::shared_ptr<NanMonkey::Step>>& stepArray, NanMonkey::Random& random, const NanMonkey::Dimention& dimention, const int startPixelOffset, const float mutateEnergyNormalised)
	{
		std::shared_ptr<NanMonkey::StepPixel> pStepPixel;
		int pixelIndex = 0;
		int stepIndex = 0;
		SelectPixelStep(pStepPixel, pixelIndex, stepIndex, random, stepArray, dimention, startPixelOffset);
		if (nullptr == pStepPixel)
		{
			NanMonkey::NanAssert(false, "invalid state");
			return;
		}
		pStepPixel->MutateAdd(dimention, dimention.ReverseCalculateOffset(pixelIndex), random, mutateEnergyNormalised);
		return;
	}

	void ChangeMutate(std::vector<std::shared_ptr<NanMonkey::Step>>& stepArray, NanMonkey::Random& random, const NanMonkey::Dimention& dimention, const int startPixelOffset, const float mutateEnergyNormalised)
	{
		std::shared_ptr<NanMonkey::StepPixel> pStepPixel;
		int pixelIndex = 0;
		int stepIndex = 0;
		SelectPixelStep(pStepPixel, pixelIndex, stepIndex, random, stepArray, dimention, startPixelOffset);
		if (nullptr == pStepPixel)
		{
			NanMonkey::NanAssert(false, "invalid state");
			return;
		}
		pStepPixel->Mutate(dimention, random, mutateEnergyNormalised);
		return;
	}

	void ChangeRemoveLink(std::vector<std::shared_ptr<NanMonkey::Step>>& stepArray, NanMonkey::Random& random, const NanMonkey::Dimention& dimention, const int startPixelOffset, const float mutateEnergyNormalised)
	{
		std::shared_ptr<NanMonkey::StepPixel> pStepPixel;
		int pixelIndex = 0;
		int stepIndex = 0;
		SelectPixelStep(pStepPixel, pixelIndex, stepIndex, random, stepArray, dimention, startPixelOffset);
		if (nullptr == pStepPixel)
		{
			NanMonkey::NanAssert(false, "invalid state");
			return;
		}
		auto& referenceArray = pStepPixel->GetReferenceArray();
		if (0 < referenceArray.size())
		{
			const int index = random.GetIndex(referenceArray.size());
			referenceArray.erase(referenceArray.begin() + index);
		}
		return;
	}

	void ChangeAddStep(std::vector<std::shared_ptr<NanMonkey::Step>>& stepArray, NanMonkey::Random& random, const NanMonkey::Dimention& dimention, const int startPixelOffset, const float mutateEnergyNormalised)
	{
		std::shared_ptr<NanMonkey::StepPixel> pStepPixel;
		int pixelIndex = 0;
		int stepIndex = 0;
		SelectPixelStep(pStepPixel, pixelIndex, stepIndex, random, stepArray, dimention, startPixelOffset);
		if (nullptr == pStepPixel)
		{
			NanMonkey::NanAssert(false, "invalid state");
			return;
		}

		auto pNewStep = NanMonkey::Step::FactoryCopyRandom(dimention, random, mutateEnergyNormalised);
		stepArray.insert(stepArray.begin() + stepIndex, pNewStep);
		return;
	}


	std::shared_ptr<NanMonkey::NeuralNetwork> FactoryNeuralNetworkPerturb(const NanMonkey::NeuralNetwork& neuralNetwork, const NanMonkey::TrainingScore& score, NanMonkey::Random& random, const float mutateEnergyNormalised)
	{
		const NanMonkey::Dimention& dimention = score.GetDimention();

		//get the sorted array of divergent pixels
		std::vector<std::pair<float, int>> scoreData;
		score.VisitPixelScore([&](const int offset, const float score){
			if (0.0f < score)
			{
				scoreData.push_back(std::pair<float, int>(score, offset));
			}
			});
		std::sort(scoreData.begin(), scoreData.end(), SortScoreData);
		int scoreDataIndex = 0;
		const int scoreDataCount = (int)(scoreData.size());

		std::vector<std::shared_ptr<NanMonkey::Step>> stepCopy = neuralNetwork.MakeStepCopy();

		if (0 < scoreDataCount)
		{
			const int count = std::max(1, (int)((mutateEnergyNormalised * mutateEnergyNormalised) * 128));
			//const int count = std::max(1, (int)(mutateEnergyNormalised * 256));
			for (int index = 0; index < count; ++index)
			{
				//select a pixel to start from
				for(;;)
				{
					//bias on piels at start of list, and wrap
					const float chance = (float)(scoreDataCount - scoreDataIndex) / (float)(scoreDataCount + scoreDataCount);
					if (random.TestPassFail(chance))
					{
						break;
					}
					scoreDataIndex = (scoreDataIndex + 1) % scoreDataCount;
				}
				const int targetPixelOffset = scoreData[scoreDataIndex].second;

				// types of changes [change link weight, remove link, add link, add step]
				const float rand = random.GetPlusFloat(1.0f);
				const int choice = std::min((int)((rand * rand) * 5), 4);
				switch(choice)
				{
				default:
					break;
				case 0:
					ChangeLinkWeight(stepCopy, random, dimention, targetPixelOffset, mutateEnergyNormalised);
					break;
				case 1:
					ChangeAddLink(stepCopy, random, dimention, targetPixelOffset, mutateEnergyNormalised);
					break;
				case 2:
					ChangeMutate(stepCopy, random, dimention, targetPixelOffset, mutateEnergyNormalised);
					break;
				case 3:
					ChangeRemoveLink(stepCopy, random, dimention, targetPixelOffset, mutateEnergyNormalised);
					break;
				case 4:
					ChangeAddStep(stepCopy, random, dimention, targetPixelOffset, mutateEnergyNormalised);
					break;
				}
			}
		}

		//move cleanup till after NeuralNetwork is selected as new candidate
		////reduce number of steps
		//AttemptReduceStep(stepCopy);

		return std::make_shared<NanMonkey::NeuralNetwork>(stepCopy);
	}

	std::shared_ptr<NanMonkey::NeuralNetwork> OptimiseNeuralNetwork(const std::shared_ptr<NanMonkey::NeuralNetwork>& pNeuralNetwork)
	{
		//todo
		return pNeuralNetwork;
	}
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

	float bestDeltaScore = inOutScore->GetDeltaScore();
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
		inOutScore->VisitTargetData([&](const bool valid, const float low, const float high){
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
		auto pCandidate = FactoryNeuralNetworkPerturb(neuralNetwork, *inOutScore, random, mutateEnergyNormalised);
		auto pCandidateScore = TrainingScore::Factory(dimention, *pCandidate, trainingData);
		const float candidateScore = pCandidateScore->GetDeltaScore();
		if (candidateScore < bestDeltaScore)
		{
			bestDeltaScore = candidateScore;
			outNeuralNetwork = pCandidate;
			inOutScore = pCandidateScore;
			countDown -= 1;
			if (countDown <= 0)
			{
				outNeuralNetwork = OptimiseNeuralNetwork(outNeuralNetwork);
				if(log) log(std::string("select small change ") + std::to_string(outNeuralNetwork->GetStepCount()) + std::string(" ") + std::to_string(candidateScore));
				return true;
			}
		}
	}


	if(log) log(std::string("no improvements found with small changes ") + std::to_string(outNeuralNetwork->GetStepCount()));

	return false;
}
