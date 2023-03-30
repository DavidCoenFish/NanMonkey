#include "pch.h"
#include "NanMonkey/TrainingScore.h"

#include "NanMonkey/NanMonkey.h"
#include "NanMonkey/Stage.h"


NanMonkey::TrainingScore::PixelData::PixelData()
: m_sampleCount(0)
, m_sumPositive(0.0f)
, m_sumNegative(0.0f)
, m_targetValid(false)
, m_targetLow(0.0f)
, m_targetHigh(0.0f)
{
	return;
}

void NanMonkey::TrainingScore::PixelData::AddSample(const float target, const float actualResult)
{
	const float delta = actualResult - target;
	m_sampleCount += 1;
	if (0.0f <= delta)
	{
		m_sumPositive += delta;
	}
	else if (delta < 0.0f)
	{
		m_sumNegative += (-delta);
	}

	if(false == m_targetValid)
	{
		m_targetLow = target;
		m_targetHigh = target;
	}
	else
	{
		m_targetValid = true;
		if (target < m_targetLow)
		{
			m_targetLow = target;
		}
		if (m_targetHigh < target)
		{
			m_targetHigh = target;
		}
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

NanMonkey::TrainingScore::TrainingScore(const Dimention& dimention)
	: m_dimention(dimention)
	, m_deltaScoreValid(false)
	, m_deltaScore(0.0f)
{
	const int count = dimention.CalculateLength();
	m_pixelDataArray.resize(count);
	return;
}

void NanMonkey::TrainingScore::GatherScore(const Stage& target, const Stage& actualResult)
{
	NanAssert(target.GetDimention() == m_dimention, "invalid size");
	NanAssert(actualResult.GetDimention() == m_dimention, "invalid size");
	auto pixelIter = m_pixelDataArray.begin();
	Stage::DeltaVisitor(target, actualResult, [&](const float delta){
		pixelIter->AddSample(delta);
		++pixelIter;
	});
	m_deltaScoreValid = false;
}

const float NanMonkey::TrainingScore::GetDeltaScore()
{
	if (false == m_deltaScoreValid)
	{
		m_deltaScoreValid = true;
		m_deltaScore = 0.0f;
		const int count = m_dimention.CalculateLength();
		const float mul = count ? 1.0f / ((float)(count)) : 0.0f;
		for (const auto& pixel : m_pixelDataArray)
		{
			const float deltaScore = pixel.GetScore();
			m_deltaScore += mul * deltaScore;
		}
	}

	return m_deltaScore;
}

