#include "pch.h"
#include "NanMonkey/Dimention.h"

#include "NanMonkey/Index.h"
#include "NanMonkey/NanMonkey.h"

NanMonkey::Dimention::Dimention(const std::vector<int>& dimention)
	: m_data(dimention)
{
	return;
}

const int NanMonkey::Dimention::GetCount() const
{
	return (int)m_data.size();
}

const int NanMonkey::Dimention::GetValue(const int index) const
{
	if ((0 <= index) && (index < (int)m_data.size()))
	{
		return m_data[index];
	}
	return 0;
}

const int NanMonkey::Dimention::CalculateLength() const
{
	int length = 1;
	for (const auto iter : m_data)
	{
		length *= iter;
	}
	return length;
}

const int NanMonkey::Dimention::CalculateOffset(const Index& index) const
{
	//x0 + (y0 * x) + (z0 * x * y)
	const int count = index.GetCount();
	NanAssert((int)m_data.size() == count, "data missmatch");
	int step = 1;
	int result = 0;
	for (int trace = 0; trace < count; ++trace)
	{
		result += (index.GetValue(trace) * step);
		step *= m_data[trace];
	}
	return result;
}

const NanMonkey::Index NanMonkey::Dimention::ReverseCalculateOffset(const int offset) const
{
	const int length = CalculateLength();
	NanAssert((0 <= offset) && (offset < length), "invalid param");

	const int count = GetCount();
	std::vector<int> data(count, 0);
	int trace = offset;
	for (int index = 0; index < count; ++index)
	{
		//int step = 1;
		//for (int subIndex = 0; subIndex < count - 1; ++subIndex)
		//{
		//	step *= m_data[subIndex];
		//}
		//const int targetIndex = count - 1 - index;
		//data[targetIndex] = trace / step;
		//trace = trace % step;
		const int div = m_data[index];
		data[index] = trace % div;
		trace = trace / div;
	}
	return Index(data);
}

const bool NanMonkey::Dimention::operator==(const Dimention& rhs) const
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

const bool NanMonkey::Dimention::operator!=(const Dimention& rhs) const
{
	return !(this->operator==(rhs));
}
