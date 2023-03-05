/*
Network<X,Y,Z>
 int m_seed; //
 int m_generation;
 Vector<Step<X,Y,Z>> m_stepArray;	
*/

class Step;
class State;

class Network
{
public:
#if defined(UNITTEST)
	static const bool UnitTest();
#endif

	friend std::ostream & operator<<(std::ostream & stream, const Network& network);
	friend std::istream& operator>>(std::istream& stream, Network& network);

	static std::shared_ptr<Network> Factory(const int x, const int y, const int z, const int seed, const int stepCount, const float chanceWeight, const float weightRange);
	static std::shared_ptr<Network> Factory(const int x, const int y, const int z, const int seed, const int generation, const std::vector<std::shared_ptr<Step>>& stepArray);

	explicit Network(
		const int x = 0, 
		const int y = 0, 
		const int z = 0, 
		const int seed = 0, 
		const int generation = 0, 
		const std::vector<std::shared_ptr<Step>>& stepArray = std::vector<std::shared_ptr<Step>>()
	);

	std::shared_ptr<State> Evalue(const std::shared_ptr<State>& input) const;

private:
	int m_x; 
	int m_y;
	int m_z;
	int m_seed;
	int m_generation;
	std::vector<std::shared_ptr<Step>> m_stepArray;

};