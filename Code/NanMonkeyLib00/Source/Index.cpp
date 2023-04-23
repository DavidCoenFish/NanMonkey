#include "pch.h"
#include "NanMonkey/Index.h"
#include "NanMonkey/Dimention.h"


NanMonkey::Index::Index(const std::vector<int>& data)
	: m_data(data)
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

const bool NanMonkey::Index::operator==(const Index& rhs) const
{
	if (m_data.size() != rhs.m_data.size())
	{
		return false;
	}
	auto lhsIter = m_data.cbegin();
	auto rhsIter = rhs.m_data.cbegin();
	while ((lhsIter != m_data.end()) && (rhsIter != rhs.m_data.end()))
	{
		if ((*lhsIter) != (*rhsIter))
		{
			return false; 
		}
		lhsIter++;
		rhsIter++;
	}
	return true;
}

const bool NanMonkey::Index::operator!=(const Index& rhs) const
{
	return !(this->operator==(rhs));
}

