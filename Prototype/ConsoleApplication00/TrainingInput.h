class State;

class TrainingInput
{
public:
#if defined(UNITTEST)
	static const bool UnitTest();
#endif
	//static std::shared_ptr< TrainingInput > 

	TrainingInput(
		const std::shared_ptr< State >& input,
		const std::shared_ptr< State >& target
		);

private:
	std::shared_ptr< State > m_input;
	std::shared_ptr< State > m_target;

};