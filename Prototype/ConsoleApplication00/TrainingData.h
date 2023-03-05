class TrainingInput;

class TrainingData
{
public:
#if defined(UNITTEST)
	static const bool UnitTest();
#endif
	static std::shared_ptr<TrainingData> FactoryFile(const std::string& filePath);

	TrainingData(
		const std::vector< std::shared_ptr< TrainingInput > >& inputArray
		);

private:
	std::vector< std::shared_ptr< TrainingInput > > m_inputArray;

};