namespace NanMonkey
{
	class Stage
	{
	public:
		Stage(const Dimention& dimention, const std::vector<float>& data);

	private:
		Dimention m_dimention;
		std::vector<float> m_data;
	};
}