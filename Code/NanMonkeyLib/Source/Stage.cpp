#include "pch.h"
#include "NanMonkey/Stage.h"

#include "NanMonkey/Dimention.h"
#include "NanMonkey/Index.h"
#include "NanMonkey/NanMonkey.h"
#include "NanMonkey/Tag.h"

std::shared_ptr<NanMonkey::Stage> NanMonkey::Stage::FactoryTag(const Dimention& dimention, const std::vector<Tag>& tag, const std::map<std::string, float>& tagValue)
{
	const int count = dimention.CalculateLength();
	std::vector<float> data(count, 0.0f);
	int index = 0;
	auto iter = tag.cbegin();
	while ((index < count) && (iter != tag.cend()))
	{
		auto found = tagValue.find(iter->GetName());
		float value = 0.0f;
		if (found != tagValue.end())
		{
			value = found->second;
		}
		data[index] = value;
		++index;
		++iter;
	}
	auto pResult = std::make_shared< Stage >(dimention, data);
	return pResult;
}

std::shared_ptr<NanMonkey::Stage> NanMonkey::Stage::Factory(const Dimention& dimention, const std::vector<float>& data)
{
	auto pResult = std::make_shared< Stage >(dimention, data);
	return pResult;
}

NanMonkey::Stage::Stage(const Stage& rhs)
	: m_dimention(rhs.m_dimention)
	, m_data(rhs.m_data)
{
	return;
}

NanMonkey::Stage::Stage(const Dimention& dimention, const std::vector<float>& data)
	: m_dimention(dimention)
	, m_data(data)
{
	return;
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

void NanMonkey::Stage::Visitor(const Stage& target, const std::function<void(const float)>& visitor)
{
	auto targetIter = target.m_data.cbegin();
	while (targetIter != target.m_data.cend())
	{
		visitor((*targetIter));
		++targetIter;
	}
	return;
}

//void NanMonkey::Stage::GatherDelta(std::vector<float>& delta, const Stage& target, const Stage& actualResult)
void NanMonkey::Stage::DeltaVisitor(const Stage& target, const Stage& actualResult, const std::function<void(const float, const float)>& visitor)
{
	NanAssert(target.m_dimention == actualResult.m_dimention, "invaild size");
	//const int count = target.m_dimention.CalculateLength();
	//delta.resize(count);
	auto targetIter = target.m_data.cbegin();
	auto actualResultIter = actualResult.m_data.cbegin();
	while ((targetIter != target.m_data.cend()) && (actualResultIter != actualResult.m_data.cend()))
	{
		visitor((*targetIter), (*actualResultIter));
		++targetIter;
		++actualResultIter;
	}
	return;
}

