#include "pch.h"
#include "NanMonkey/Stage.h"

#include "NanMonkey/Dimention.h"
#include "NanMonkey/Index.h"

NanMonkey::Stage::Stage(const Dimention& dimention, const std::vector<float>& data)
	: m_dimention(dimention)
	, m_data(data)
{
	return;
}

const bool NanMonkey::Stage::CheckDimention(const Dimention& dimention) const
{
	return (m_dimention == dimention);
}

const float NanMonkey::Stage::GetValue(const Index& index) const
{
	const int offset = m_dimention.CalculateOffset(index);
	if ((0 <= offset) && (offset < (int)m_data.size()))
	{
		return m_data[offset];
	}
	return 0.0f;
}
