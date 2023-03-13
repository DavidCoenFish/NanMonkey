class TrainingInput;

class TrainingData
{
public:
#if defined(UNITTEST)
	static const bool UnitTest();
#endif
	static std::shared_ptr<TrainingData> FactoryImageGreyscale(
		const std::string& configPath,
		const std::string& subPath,
		const int x, 
		const int y, 
		const int z, 
		const std::map< std::string, float> baseTargetMap
	);

	TrainingData(
		const std::vector< std::shared_ptr< TrainingInput > >& inputArray
		);

private:
	std::vector< std::shared_ptr< TrainingInput > > m_inputArray;

};