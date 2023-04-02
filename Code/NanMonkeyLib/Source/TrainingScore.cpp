#include "pch.h"
#include "NanMonkey/TrainingScore.h"

#include "NanMonkey/NanMonkey.h"
#include "NanMonkey/NeuralNetwork.h"
#include "NanMonkey/Stage.h"
#include "NanMonkey/TrainingData.h"

NanMonkey::TrainingScore::PixelData::PixelData()
: m_sampleCount(0)
, m_sumPositive(0.0f)
, m_sumNegative(0.0f)
{
	return;
}

void NanMonkey::TrainingScore::PixelData::AddSample(const float delta)
{
	m_sampleCount += 1;
	if (0.0f <= delta)
	{
		m_sumPositive += delta;
	}
	else if (delta < 0.0f)
	{
		m_sumNegative += (-delta);
	}

	return;
}

const float NanMonkey::TrainingScore::PixelData::GetAverage() const
{
	if (0 == m_sampleCount)
	{
		return 0.0f;
	}
	return (m_sumPositive - m_sumNegative) / ((float)(m_sampleCount));
}

const float NanMonkey::TrainingScore::PixelData::GetScore() const
{
	return (m_sumPositive + m_sumNegative);
}

NanMonkey::TrainingScore::TargetData::TargetData()
	: m_targetValid(false)
	, m_targetLow(0.0f)
	, m_targetHigh(0.0f)
{
	return;
}

void NanMonkey::TrainingScore::TargetData::AddSample(const float target)
{
	if(false == m_targetValid)
	{
		m_targetValid = true;
		m_targetLow = target;
		m_targetHigh = target;
	}
	else
	{
		if (target < m_targetLow)
		{
			m_targetLow = target;
		}
		if (m_targetHigh < target)
		{
			m_targetHigh = target;
		}
	}
}

void NanMonkey::TrainingScore::TargetData::Visit(const std::function<void(const bool, const float, const float)>& visitor) const
{
	visitor(m_targetValid, m_targetLow, m_targetHigh);
}

std::shared_ptr<NanMonkey::TrainingScore> NanMonkey::TrainingScore::Factory(const Dimention& dimention, const NeuralNetwork& neuralNetwork, const TrainingData& trainingData)
{
	const int length = dimention.CalculateLength();
	std::vector<PixelData> pixelDataArray(length);
	std::vector<TargetData> targetDataArray(length);
	{
		trainingData.Visit([&](const NanMonkey::Stage& input,const NanMonkey::Stage& target){
			auto actualResult = neuralNetwork.Perform(input);

			auto pixelIter = pixelDataArray.begin();
			Stage::DeltaVisitor(target, *actualResult, [&](const float target, const float actual){
				pixelIter->AddSample(actual - target);
				++pixelIter;
				});

			auto tagetIter = targetDataArray.begin();
			Stage::Visitor(target, [&](const float value){
				tagetIter->AddSample(value);
				++tagetIter;
			});
		});
	}

	auto pResult = std::make_shared<TrainingScore>(dimention, pixelDataArray, targetDataArray);
	return pResult;

}

NanMonkey::TrainingScore::TrainingScore(const Dimention& dimention, const std::vector<PixelData>& pixelDataArray, const std::vector<TargetData>& targetDataArray)
	: m_dimention(dimention)
	, m_pixelDataArray(pixelDataArray)
	, m_targetDataArray(targetDataArray)
	, m_deltaScoreValid(false)
	, m_deltaScore(0.0f)
{
	return;
}

//void NanMonkey::TrainingScore::GatherScore(const Stage& target, const Stage& actualResult)
//{
//	auto pixelIter = m_pixelDataArray.begin();
//	Stage::DeltaVisitor(target, actualResult, [&](const float targetValue, const float actualValue){
//		pixelIter->AddSample(actualValue - targetValue);
//		++pixelIter;
//	});
//}

const float NanMonkey::TrainingScore::GetDeltaScore()
{
	if (false == m_deltaScoreValid)
	{
		m_deltaScoreValid = true;
		m_deltaScore = 0.0f;

		for(const auto& pixelData: m_pixelDataArray)
		{
			m_deltaScore += pixelData.GetScore();
		}
	}

	return m_deltaScore;
}

void NanMonkey::TrainingScore::VisitPixelScore(const std::function<void(const int, const float)>& visitor) const
{
	int trace = 0;
	for(const auto& pixelData: m_pixelDataArray)
	{
		//m_dimention.ReverseCalculateOffset(trace)
		visitor(trace, pixelData.GetScore());
		trace += 1;
	}
}

void NanMonkey::TrainingScore::VisitTargetData(const std::function<void(const bool, const float, const float)>& visitor) const
{
	for(const auto& targetData: m_targetDataArray)
	{
		targetData.Visit(visitor);
	}
}


