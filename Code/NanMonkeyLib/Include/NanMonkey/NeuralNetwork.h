namespace NanMonkey
{
	class Step;
	class Stage;

	class NeuralNetwork
	{
	public:
		// FactoryInsertStep
		//static std::shared_ptr<NeuralNetwork> FactoryScoreMutateNoCortex(Random& random, 

		NeuralNetwork(const std::vector<std::shared<Step>>& stepArray);

		std::shared<Stage> Perform(const Stage& input) const;

	private:
		std::vector<std::shared<Step>> m_stepArray;
	};
}