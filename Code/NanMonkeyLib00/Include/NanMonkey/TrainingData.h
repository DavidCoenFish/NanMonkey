#pragma once

namespace NanMonkey
{
	class Dimention;
	class Stage;
	class TrainingDataImplementation;

	class TrainingData
	{
	public:
		static std::shared_ptr< TrainingData > Factory(
			const Dimention& inputDimention,
			const Dimention& outputDimention,
			const std::vector< std::pair< std::vector< float >, std::vector< float > > >& trainingData
		);

		TrainingData(
			const Dimention& inputDimention,
			const Dimention& outputDimention,
			const std::vector< std::pair< std::shared_ptr< Stage >, std::shared_ptr< Stage > > >& data
		);

		void Visitor(const std::function<void(const Stage&, const Stage&)>& visitor);

	private:
		std::unique_ptr< TrainingDataImplementation > m_implementation;

	};
}