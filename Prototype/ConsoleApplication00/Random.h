class Random
{
public:
	static std::shared_ptr<Random> Factory();
	static std::shared_ptr<Random> FactorySeed(const int seed);

	Random(const int seed);
	const bool TestPassFail(const float threashold = 0.5f);
	const float GetPlusMinus(const float radius);

#if defined(UNITTEST)
	static const bool UnitTest();
#endif

private:
	typedef std::mt19937 TRandom;

	int m_seed;
	TRandom m_random;

	std::uniform_real_distribution<float> m_distributionMinusOnePlusOne;
	std::uniform_real_distribution<float> m_distributionZeroPlusOne;
	//std::uniform_int_distribution<uint32_t> uint_dist10(0,10)
	//std::normal_distribution<float> m_normalDistribution;

};