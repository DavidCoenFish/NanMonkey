#pragma once

namespace NanMonkey
{
	class Step;
	class Stage;

	class NeuralNetwork
	{
	public:
		// FactoryInsertStep
		//static std::shared_ptr<NeuralNetwork> FactoryScoreMutateNoCortex(Random& random, 

		NeuralNetwork(const std::vector<std::shared_ptr<Step>>& stepArray = std::vector<std::shared_ptr<Step>>());

		std::shared_ptr<Stage> Perform(const Stage& input) const;

	private:
		std::vector<std::shared_ptr<Step>> m_stepArray;

	};
}