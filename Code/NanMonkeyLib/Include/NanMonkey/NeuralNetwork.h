#pragma once

namespace NanMonkey
{
	class Step;
	class Stage;
	class TrainingScore;
	class Random;

	class NeuralNetwork
	{
	public:
		// FactoryInsertStep
		//static std::shared_ptr<NeuralNetwork> FactoryScoreMutateNoCortex(Random& random, 

		static std::shared_ptr<NeuralNetwork> FactorySeed(const TrainingScore& score);
		static std::shared_ptr<NeuralNetwork> FactoryPerturb(const NeuralNetwork& neuralNetwork, const TrainingScore& score, const Random& random, const float weight);

		//NeuralNetwork(const NeuralNetwork& rhs);
		NeuralNetwork(const std::vector<std::shared_ptr<Step>>& stepArray = std::vector<std::shared_ptr<Step>>());

		std::shared_ptr<Stage> Perform(const Stage& input) const;
		const int GetStepCount() const;
	private:
		std::vector<std::shared_ptr<Step>> m_stepArray;

	};
}