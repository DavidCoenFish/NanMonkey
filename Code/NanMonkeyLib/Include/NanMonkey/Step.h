namespace NanMonkey
{
	class Step
	{
	public:
		static FactoryMutate(Random& random, const Index& index, 

		Step(const Dimention& dimention, const std::vector<std::shared_ptr<StagePixel>>& data);

		std::shared<Stage> Perform(const Stage& input) const;

		//visit pixel? getPixel? tweak pixel 

	private:
		Dimention m_dimention;
		std::vector<std::shared_ptr<StagePixel>> m_data;
	};
}