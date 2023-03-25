namespace NanMonkey
{
	class Index
	{
	public:
		Index(const std::vector<int>& dimention);

		const int GetCount() const;
		const int GetValue(const int index) const;


	private:
		std::vector<int> m_data;
		//bool m_dirty;
		//int m_offset;

	};
}