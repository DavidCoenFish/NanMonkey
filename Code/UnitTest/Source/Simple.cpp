#include "Simple.h"

#include "Main.h"
#include "UnitTest.h"

#include "NanMonkey/Dimention.h"
#include "NanMonkey/Random.h"
#include "NanMonkey/Stage.h"
#include "NanMonkey/Tag.h"
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

		std::vector<std::shared_ptr<NanMonkey::TrainingData::Data>> trainingData;
		{
			std::vector<NanMonkey::Tag> tagArray;
			tagArray.push_back(NanMonkey::Tag("a", 1.0f));
			tagArray.push_back(NanMonkey::Tag("b", -1.0f));
			auto pTarget = NanMonkey::Stage::FactoryTag(dimention, tagArray);
			for (int index = 0; index < 8; ++index)
			{
				std::vector<float> data;
				random->GenerateRangeFloatVisitor(dimentionLength, -1.0f, 0.0f, [&](const float value){
					data.push_back(value);
					});
				auto pInput = NanMonkey::Stage::Factory(dimention, data);
				trainingData.push_back(std::make_shared<NanMonkey::TrainingData::Data>(pInput, pTarget));
			}
		}
		{
			std::vector<NanMonkey::Tag> tagArray;
			tagArray.push_back(NanMonkey::Tag("a", -1.0f));
			tagArray.push_back(NanMonkey::Tag("b", 1.0f));
			auto pTarget = NanMonkey::Stage::FactoryTag(dimention, tagArray);
			for (int index = 0; index < 8; ++index)
			{
				std::vector<float> data;
				random->GenerateRangeFloatVisitor(dimentionLength, 0.0f, 1.0f, [&](const float value){
					data.push_back(value);
					});
				auto pInput = NanMonkey::Stage::Factory(dimention, data);
				trainingData.push_back(std::make_shared<NanMonkey::TrainingData::Data>(pInput, pTarget));
			}
		}

		//train a neural network to 
	}

	return ok;
}
