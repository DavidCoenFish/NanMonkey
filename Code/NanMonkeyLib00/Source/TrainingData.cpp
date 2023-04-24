#include "pch.h"
#include "NanMonkey/TrainingData.h"
#include "NanMonkey/Dimention.h"
#include "NanMonkey/Stage.h"

namespace NanMonkey
{
	class TrainingDataImplementation
	{
	public:
		TrainingDataImplementation(
			const Dimention& inputDimention,
			const Dimention& outputDimention,
			const std::vector< std::pair< std::shared_ptr< Stage >, std::shared_ptr< Stage > > >& data
			)
			: m_inputDimention(inputDimention)
			, m_outputDimention(outputDimention)
			, m_data(data)
		{
			return;
		}

		void Visitor(const std::function<void(const Stage&, const Stage&)>& visitor)
		{
			for(const auto& iter : m_data)
			{
				visitor(*iter.first, *iter.second);
			}
		}

	private:
		Dimention m_inputDimention;
		Dimention m_outputDimention;
		std::vector< std::pair< std::shared_ptr< Stage >, std::shared_ptr< Stage > > > m_data;

	};
}

std::shared_ptr< NanMonkey::TrainingData > NanMonkey::TrainingData::Factory(
	const Dimention& inputDimention,
	const Dimention& outputDimention,
	const std::vector< std::pair< std::vector< float >, std::vector< float > > >& trainingData
	)
{
	std::vector< std::pair< std::shared_ptr< Stage >, std::shared_ptr< Stage > > > data;
	for (const auto& iter : trainingData)
	{
		auto pStageInput = Stage::Factory(inputDimention, iter.first);
		auto pStageOutput = Stage::Factory(outputDimention, iter.second);
		std::pair< std::shared_ptr< Stage >, std::shared_ptr< Stage > > pair(pStageInput, pStageOutput);
		data.push_back(pair);
	}

	return std::make_shared<TrainingData>(inputDimention, outputDimention, data);
}

NanMonkey::TrainingData::TrainingData(
	const Dimention& inputDimention,
	const Dimention& outputDimention,
	const std::vector< std::pair< std::shared_ptr< Stage >, std::shared_ptr< Stage > > >& data
	)
{
	m_implementation = std::make_unique<TrainingDataImplementation>(inputDimention, outputDimention, data);
	return;
}

void NanMonkey::TrainingData::Visitor(const std::function<void(const Stage&, const Stage&)>& visitor)
{
	m_implementation->Visitor(visitor);
	return;
}
