#include "pch.h"
#include "NanMonkey/TrainingData.h"

NanMonkey::TrainingData::Data::Data(const std::shared_ptr<Stage>& input, const std::shared_ptr<Stage>& target)
	: m_input(input)
	, m_target(target)
{
	return;
}

NanMonkey::TrainingData::TrainingData(const std::vector<std::shared_ptr<Data>>& dataArray)
	: m_dataArray(dataArray)
{
	return;
}

void NanMonkey::TrainingData::Visit(const std::function<void(const Stage&,const Stage&)>& visitor)
{
	for (const auto& iter: m_dataArray)
	{
		visitor(iter->GetInput(), iter->GetTarget());
	}
	return;
}
