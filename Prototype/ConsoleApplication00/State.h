/*
State<X,Y,Z>
 Array<float,X * Y * Z> m_valueArray;

*/

class Step;

class State
{
public:
#if defined(UNITTEST)
	static const bool UnitTest();
#endif

	static std::vector< float > TagMapToData(const int x, const int y, const int z, const std::map<std::string, float>& tagMap);
	static std::vector< float > PngGreyscaleToData(const int x, const int y, const int z, const std::string& filePath);

	static std::shared_ptr<State> Factory(const int x, const int y, const int z, const std::vector< float >& dataOrEmpty = std::vector< float >());

	friend std::ostream & operator<<(std::ostream & stream, const State& state);
	friend std::istream& operator>>(std::istream& stream, State& state);

	explicit State(const int x, const int y, const int z);

	//void Visit(const std::function<void(const int, const float)>& visitor) const;

	static const float CalculateWeightValue(const State& state, const std::vector< float >& weights);
	static const float CalculateDeltaScore(const State& left, const State& right);
	//static void SetFromFilePng(State& state, const std::string& filePath, const int zIndex);

	const float GetValue(const int indexX, const int indexY, const int indexZ) const;

private:
	void ResizeData();

private:
	int m_x;
	int m_y;
	int m_z;
	std::vector< float > m_data;

};