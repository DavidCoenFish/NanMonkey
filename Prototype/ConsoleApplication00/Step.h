/*
Step<X,Y,Z>
 Array<float,X * Y * Z> m_valueArray;
 Array<float,X * Y * Z> m_inputWeight;

*/

class State;
class Random;

class Step
{
public:
#if defined(UNITTEST)
	static const bool UnitTest();
#endif

	static std::shared_ptr<Step> Factory(const int x, const int y, const int z);
	//produce a new step which is the invert operation of weights, to reverse the given step
	static std::shared_ptr<Step> FactoryInvert(const Step& step);
	static std::shared_ptr<Step> FactoryClone(const Step& step);

	friend std::ostream & operator<<(std::ostream & stream, const std::vector<std::shared_ptr<Step>>& stepArray);
	friend std::ostream & operator<<(std::ostream & stream, const Step& step);
	friend std::istream& operator>>(std::istream& stream, std::vector<std::shared_ptr<Step>>& stepArray);
	friend std::istream& operator>>(std::istream& stream, Step& step);

	explicit Step(const int x = 0, const int y = 0, const int z = 0);

	static std::shared_ptr<State> ApplyStep(const Step& step, const State& input);
	static void PerturbStep(Step& step, Random& random, const float chanceOfModificationOfWeight = 0.1f, const float plusMinusMaxChangeWeight = 1.0f);

private:
	void ResizeWeights();

private:
	int m_x;
	int m_y;
	int m_z;
	//for each stage data point, we have the weight of each data point of the previous stage
	//typedef std::vector< std::shared_ptr<std::vector< float > > > TWeightArray;
	typedef std::vector< std::vector< float > > TWeightArray;
	TWeightArray  m_weights;

};