#pragma once

namespace NanMonkey
{
	class Dimention;
	class Random;

	class Index
	{
	public:
		//static Index Factory(const Dimention& dimention, const int offset);

		Index(const std::vector<int>& data);

		void Mutate(const Dimention& dimention, Random& random, const float mutateEnergyNormalised);

		const int GetCount() const;
		const int GetValue(const int index) const;

		const bool operator==(const Index& rhs) const;
		const bool operator!=(const Index& rhs) const;

	private:
		std::vector<int> m_data;
		//bool m_dirty;
		//int m_offset;

	};
}