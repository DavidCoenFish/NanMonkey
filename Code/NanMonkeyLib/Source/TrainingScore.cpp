#include "pch.h"
#include "NanMonkey/TrainingScore.h"

#include "NanMonkey/NanMonkey.h"
#include "NanMonkey/Stage.h"


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
		m_sumNegative += delta;
	}
	return;
}

NanMonkey::TrainingScore::TrainingScore(const Dimention& dimention)
	: m_dimention(dimention)
{
	const int count = dimention.CalculateLength();
	m_pixelDataArray.resize(count);
	return;
}

void NanMonkey::TrainingScore::GatherScore(const Stage& target, const Stage& actualResult)
{
	NanAssert(target.CheckDimention(m_dimention), "invalid size");
	NanAssert(actualResult.CheckDimention(m_dimention), "invalid size");
	auto pixelIter = m_pixelDataArray.begin();
	Stage::DeltaVisitor(target, actualResult, [&](const float delta){
		pixelIter->AddSample(delta);
		++pixelIter;
	});
}
