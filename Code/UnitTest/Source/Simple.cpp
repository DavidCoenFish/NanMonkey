#include "Simple.h"

#include "Main.h"
#include "UnitTest.h"

#include "NanMonkey/Dimention.h"
#include "NanMonkey/Random.h"
#include "NanMonkey/NeuralNetwork.h"
#include "NanMonkey/Stage.h"
#include "NanMonkey/Tag.h"
#include "NanMonkey/Train.h"
#include "NanMonkey/TrainingData.h"

const bool Simple::UnitTest()
{
	UNIT_TEST_HEAD("Simple");
	bool ok = true;

	if (ok)
	{
		//make some simple training data
		auto random = NanMonkey::Random::FactorySeed(5);
		NanMonkey::Dimention dimention(std::vector<int>({4,4}));
		const int dimentionLength = dimention.CalculateLength();

		std::vector<NanMonkey::Tag> tagArray;
		tagArray.push_back(NanMonkey::Tag("a"));
		tagArray.push_back(NanMonkey::Tag("b"));
		std::vector<std::shared_ptr<NanMonkey::TrainingData::Data>> trainingDataArray;
		{
			std::map<std::string, float> tagValue({{"a", 1.0f}, {"b", -1.0f}});
			auto pTarget = NanMonkey::Stage::FactoryTag(dimention, tagArray, tagValue);

			for (int index = 0; index < 8; ++index)
			{
				std::vector<float> data;
				random->GenerateRangeFloatVisitor(dimentionLength, -1.0f, 0.0f, [&](const float value){
					data.push_back(value);
					});
				auto pInput = NanMonkey::Stage::Factory(dimention, data);
				trainingDataArray.push_back(std::make_shared<NanMonkey::TrainingData::Data>(pInput, pTarget));
			}
		}
		{
			std::map<std::string, float> tagValue({{"a", -1.0f}, {"b", 1.0f}});
			auto pTarget = NanMonkey::Stage::FactoryTag(dimention, tagArray, tagValue);
			for (int index = 0; index < 8; ++index)
			{
				std::vector<float> data;
				random->GenerateRangeFloatVisitor(dimentionLength, 0.0f, 1.0f, [&](const float value){
					data.push_back(value);
					});
				auto pInput = NanMonkey::Stage::Factory(dimention, data);
				trainingDataArray.push_back(std::make_shared<NanMonkey::TrainingData::Data>(pInput, pTarget));
			}
		}

		auto pNeuralNetwork = std::make_shared<NanMonkey::NeuralNetwork>();
		auto pTrainingData = std::make_shared<NanMonkey::TrainingData>(trainingDataArray);
		std::shared_ptr<NanMonkey::TrainingScore> pTrainingScore;

		//train a neural network
		for (int index = 0;index < 256; ++index)
		{
			//add a references, so that during traning, a new candidate is assigned, that the top level NeuralNetwork/score is not cleared
			auto pCurrentNeuralNetwork = pNeuralNetwork;
			auto pCurrentTrainingScore = pTrainingData;

			if (false == NanMonkey::Train(
				pNeuralNetwork, 
				pTrainingScore,
				dimention,
				*pCurrentNeuralNetwork, 
				*pCurrentTrainingScore, 
				*random, 
				[](const std::string& output){
					MESSAGE(output)
				}))
			{
				break;
			}
			ok &= UNIT_TEST_NOT_NULL(pNeuralNetwork.get());
			if (false == ok)
			{
				break;
			}
		}
	}

	return ok;
}
