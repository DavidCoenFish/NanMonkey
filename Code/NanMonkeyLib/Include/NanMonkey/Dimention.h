namespace NanMonkey
{
	class Index;

	class Dimention
	{
	public:
		Dimention(const std::vector<int>& dimention);
		const int GetCount() const;
		const int GetValue(const int index) const;

		const int CalculateLength() const;
		const int CalculateOffset(const Index& index) const;

	private:
		std::vector<int> m_data;
	};
}