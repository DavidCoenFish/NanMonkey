#include "pch.h"
#include "NanMonkey/Index.h"

NanMonkey::Index::Index(const std::vector<int>& dimention)
	: m_data(dimention)
{
	return;
}

const int NanMonkey::Index::GetCount() const
{
	return (int)m_data.size();
}

const int NanMonkey::Index::GetValue(const int index) const
{
	if ((0 <= index) && (index < (int)m_data.size()))
	{
		return m_data[index];
	}
	return 0;
}

