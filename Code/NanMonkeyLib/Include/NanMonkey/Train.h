#pragma once

namespace NanMonkey
{
	class Dimention;
	class NeuralNetwork;
	class TrainingData;
	class TrainingScore;
	class Random;

	const bool Train(
		std::shared_ptr<NeuralNetwork>& outNeuralNetwork,
		std::shared_ptr<TrainingScore>& inOutScore,
		const Dimention& dimention,
		const NeuralNetwork& neuralNetwork, 
		const TrainingData& trainingData, 
		Random& random, 
		const std::function<void(const std::string&)>& log,
		const int attemptMax = 1024
		);

}